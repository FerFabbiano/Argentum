#ifndef SERVER_PROXY_H
#define SERVER_PROXY_H

#include "GameServer.h"
#include "Player.h"
#include "../common/BlockingQueue.h"
#include "../common/Thread.h"

class GameServer;
using InstructionDataBQ = BlockingQueue<InstructionData>;
using UpDateClientsBQ = FixedBlockingQueue<PlayerGameModelData>;

class ServerProxy : public Thread{
  private:
    InstructionDataBQ &instructionQueue;
    bool continuePlaying;
    ActivePlayers &activePlayers;
    UpDateClientsBQ clientBQ;
  public:
    explicit ServerProxy(InstructionDataBQ &instructionQueue, 
      ActivePlayers &activePlayers);
    ~ServerProxy();
    ServerProxy(const ServerProxy&) = delete;
    ServerProxy& operator=(const ServerProxy&) = delete;
    void run();
    void stopPlaying();
};

#endif
