#include "GameServer.h"
#include "ClientAcceptor.h"

#include <utility>
#include <iostream>

GameServer::GameServer() : isClose(false), activePlayers(0) {}

GameServer::~GameServer(){}

void GameServer::init(){
/* Cargar todo lo que el servidor necesite 
     Cargar Mapa en memoria.
     Cargar Archivo con datos indexables del jugador.
     Cargar Definiciones.
*/
}

void GameServer::start(){
  ClientAcceptor acceptor(instructionQueue, activePlayers);
  acceptor.start();
  
  while (!isClose){
    InstructionData instruction;
    instructionQueue.try_front_pop(instruction);
    
    if (game.handleInstruction(instruction)){
      std::vector<size_t> playersId = activePlayers.getActivePlayers();
      
      for (auto& it :playersId){  
        PlayerGameModelData modelData = {};

        game.generatePlayerModel(it, modelData);
        activePlayers.updateModel(it, modelData);
      }
    }
  }
}

void GameServer::close(){
  isClose = true;
  // cerrar socket
}
