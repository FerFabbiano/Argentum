#include <iostream>
#include <sstream>
#include <cassert>
#include "server/GameServer.h"
#include <syslog.h>

int main() {
  try {
    char mapPath[] = "client/assets/map/pindonga3.json";
    char port[] = "7777";
    GameServer game(port, mapPath);
    game.start();
  } catch(const std::exception& e) {
    syslog(LOG_CRIT, "[Crit] Error!: %s", e.what());
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  } catch(...) {
    syslog(LOG_CRIT, "[Crit] Unknown Error!");
    return EXIT_FAILURE;
  }
  return 0;
}
