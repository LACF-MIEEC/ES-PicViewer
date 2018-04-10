#include "debugES.h"


void debugMsg(std::string message){

#ifdef PRINT_DEBUGS
    std::cout << message << std::endl;
#else
    std::cout << "Debug messages are not active" << std::endl;
#endif
}

