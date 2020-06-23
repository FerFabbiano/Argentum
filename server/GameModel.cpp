#include "GameModel.h"

#include <iostream>
#include <string> // TODO - Lo pide el parser
#include <utility>
#include <vector>

GameModel::GameModel(char* mapPath, CronBQ& cronBQ) :
  cronBQ(cronBQ) {
  m.loadMap(mapPath);
  parseMapData();
}

void GameModel::parseMapData() {
  std::vector<struct ObjectLayerData>& obj = m.getObjectLayers();

  for (size_t i = 0; i < obj.size(); i++){
    ObjectLayerData& layer = obj[i];
    for (size_t j = 0; j < obj[i].objects.size(); j++){
      ObjectData& data = layer.objects[j];
      PositionData p({data.x, data.y, data.width, data.height});

      if (layer.name == MARGIN_LAYER){
        std::unique_ptr<Entity> margin(
          new Entity(p));
        margins.push_back(std::move(margin));
      }
    }
  }
}

GameModel::~GameModel(){}

bool GameModel::authenticate(
  std::string& nick,
  ResponseBQ& responseBQ,
  size_t& playerId) {
  // TODO: BUSCAR EN LOS ARCHIVOS. VER SI EXISTE Y OBTENER DATA//
  MainPlayerData playerData = {{WARRIOR, HUMAN}, {""}, {100, 100, 100, 100},
  {100, 100, 25, 48}, {0, 0}, 0, 0};

  if (nick == "Fer") playerId  = 1; // rand() % 100 + 1;

  // INSERTO EN EL MAPA DE COMUNICACIONES Y EN EL DE JUGADORES//
  clientsBQ.insert(std::pair<size_t, ResponseBQ&>(playerId, responseBQ));

  std::unique_ptr<Player> player(new Player(playerData, playerId));
  players.insert(std::pair<size_t,
    std::unique_ptr<Player>>(playerId, std::move(player)));

  return true;
}

void GameModel::move(size_t playerId, int x, int y) {
  players.at(playerId)->movement.xDir = x;
  players.at(playerId)->movement.yDir = y;
}

void GameModel::stopMovement(size_t playerId){
  players.at(playerId)->movement.xDir = 0;
  players.at(playerId)->movement.yDir = 0;
}

void GameModel::attack(size_t playerId, int xPos, int yPos){
  for (auto& it : players){
    if (players.at(it.first)->id == playerId) continue;

    if (!players.at(playerId)->checkInRange(*it.second, MAX_RANGE_ZONE))
      continue;

    players.at(playerId)->attack(*it.second, xPos, yPos);
  }
}

void GameModel::playerSetCoords(size_t playerId, int x, int y) {
  int auxXPos = players.at(playerId)->position.x;
  int auxYPos = players.at(playerId)->position.y;
  players.at(playerId)->position.x = x;
  players.at(playerId)->position.y = y;

  for (auto& it : players){
    if (players.at(it.first)->id == playerId) continue;
    bool collision = players.at(playerId)->checkCollision(*it.second);
    if (collision){
        players.at(playerId)->position.x = auxXPos;
        players.at(playerId)->position.y = auxYPos;
        return;
    }
  }

  for (auto &it : margins){
    bool collision = players.at(playerId)->checkCollision(*it);
    if (collision){
      players.at(playerId)->position.x = auxXPos;
      players.at(playerId)->position.y = auxYPos;
      return;
    }
  }
}

void GameModel::eraseClient(size_t playerID){
  players.erase(playerID);
  clientsBQ.erase(playerID);
}

void GameModel::propagate() {
  generateOtherPlayersGameData();

  std::unique_ptr<CronGameModelData> cronGameModelData(new CronGameModelData);
  //cronGameModelData->npcs = npcs;
  cronGameModelData->otherPlayers = otherPlayers;
  cronBQ.push(std::move(cronGameModelData));

  for (auto& it : players){
    PlayerGameModelData modelData = {};

    generatePlayerModel(it.first, modelData);

    std::unique_ptr<Response> response(new
      PlayerGameResponse(modelData));

    clientsBQ.at(it.first).push(std::move(response));
  }
}

void GameModel::generatePlayerModel(size_t id, PlayerGameModelData &modelData){
  modelData.npcs = npcs;
  //modelData.map = map;

  modelData.playerData.gold = players.at(id)->gold;
  modelData.playerData.points = players.at(id)->health;
  modelData.playerData.inventory = players.at(id)->inventory;
  modelData.playerData.level = players.at(id)->level;
  modelData.playerData.position = players.at(id)->position;
  modelData.playerData.rootd = players.at(id)->root;
  modelData.playerData.movement = players.at(id)->movement;

  modelData.otherPlayers = otherPlayers;
}

void GameModel::generateOtherPlayersGameData(){
  otherPlayers.clear();
  for (auto& it : players){
    OtherPlayersData otherPlayer;
    otherPlayer.id = players.at(it.first)->id;
    otherPlayer.position = players.at(it.first)->position;
    otherPlayer.movement = players.at(it.first)->movement;
    otherPlayer.rootd = players.at(it.first)->root;
    otherPlayers.push_back(std::move(otherPlayer));
  }
}

void GameModel::addNPCS(){
  struct EnemyData data;
  data.position.x = 100;
  data.position.y = 100;
  data.movement.xDir = 0;
  data.movement.yDir = 1;
  data.type = GOBLIN;
  npcs.emplace_back(data);

  data.position.x = 200;
  data.position.y = 100;
  data.type = SKELETON;
  npcs.emplace_back(data);

  data.position.x = 300;
  data.position.y = 100;
  data.type = SPIDER;
  npcs.emplace_back(data);
}