#ifndef __DATADEF_H
#define __DATADEF_H

#include <string>
#include <vector>
#include <msgpack.hpp>

struct MainPlayerData {};

struct TileSetData {
  int columns;
  int firstgid;
  int tilecount;
  std::string image;
};

struct TileLayerData {
  int id;
  std::string name;
  std::vector<size_t> data;
};

typedef struct ParamData {
  std::string value;
  MSGPACK_DEFINE(value)
} ParamDataT;

typedef enum {
  MOVE,
  BUY,
  DEPOSIT_GOLD,
  DEPOSIT_ITEM,
  ATTACK,
  CLOSE_SERVER
} ActionTypeT;

typedef struct InstructionData {
  size_t playerId;
  ActionType_t action;
  std::vector<ParamData> params;
  //MSGPACK_DEFINE(playerId, params, action)
} IntructionDataT;

#endif
