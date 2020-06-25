#include "ServerProxy.h"
#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>

ServerProxy::ServerProxy(std::string& host, std::string& port) :
  running(true),
  serverProxyWrite(*this, writeBQ),
  serverProxyRead(*this){
    std::cout << "Connected to: " << host << ":" << port << std::endl;
    socket.connect(host.c_str(), port.c_str());
}

ServerProxy::~ServerProxy(){
  socket.close();
}

void ServerProxy::authentificate(std::string& alias) {
  std::cout << "Player " << alias << " authentificated" << std::endl;
}

void ServerProxy::init() {
  MapParser m;
  m.loadMap("client/assets/map/gameMap.json");
  map = m.getMapData();

  serverProxyWrite.start();
  serverProxyRead.start();

  ParamData nick = {"Fer"};
  InstructionData instruction = {AUTHENTICATE, {nick}};
  writeBQ.push(instruction);

  mainPlayer.rootd.pclass = WARRIOR;
  mainPlayer.rootd.prace = GNOME;
}

void ServerProxy::update() {
  std::unique_ptr<Response> r;

  if (!running) return;
  bool success = responseQ.try_front_pop(r);

  if (!success) return;
  r->run(*this);
}

void ServerProxy::move(int xDir, int yDir){
  if (xDir == 0 && yDir == 0){
    InstructionData instruction = {STOP_MOVEMENT, {}};
    writeBQ.push(instruction);
  } else {
    ParamData x = {std::to_string(xDir)};
    ParamData y = {std::to_string(yDir)};
    InstructionData instruction = {MOVE, {x, y}};
    writeBQ.push(instruction);
  }
}

void ServerProxy::attack(int xPos, int yPos) {
  ParamData x = {std::to_string(xPos)};
  ParamData y = {std::to_string(yPos)};
  ParamData width = {std::to_string(mainPlayer.position.w)};
  ParamData height = {std::to_string(mainPlayer.position.h)};
  InstructionData instruction = {ATTACK, {x, y, width, height}};
  writeBQ.push(instruction);
}

MainPlayerData ServerProxy::getMainPlayerData() const {
  return mainPlayer;
}

void ServerProxy::setGameModelData(PlayerGameModelData &gameModelData){
  mainPlayer = gameModelData.playerData;
  /*mainPlayer.equipment.head = HOOD;
  mainPlayer.equipment.body = PLATE_ARMOR;
  mainPlayer.equipment.leftHand = TURTLE_SHIELD;*/
  npcs = gameModelData.npcs;
  otherPlayers = gameModelData.otherPlayers;
  //map = gameModelData.map;
}

MapData ServerProxy::getMapData() const {
  return map;
}

std::vector<EnemyData> ServerProxy::getNPCData() const {
  return npcs;
}

std::vector<OtherPlayersData> ServerProxy::getOtherPlayersData() const {
  return otherPlayers;
}

bool ServerProxy::isAuthenticated() const {
  return authentificated;
}

void ServerProxy::close(){
  running = false;
  InstructionData instruction = {CLOSE_SERVER, {}};
  writeBQ.push(instruction);
}
