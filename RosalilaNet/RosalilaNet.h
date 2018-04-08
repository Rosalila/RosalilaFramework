#ifndef ROSALILA_NET
#define ROSALILA_NET

#include <SDL2/SDL_net.h>

#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include "../RosalilaUtility/RosalilaUtility.h"

#ifdef WINDOWS
#include <windows.h>
#endif

class RosalilaNet
{
  public:
    std::int32_t server_port;
    std::string server_ip;
    IPaddress serverIP;
    UDPpacket *packet;
    UDPsocket server_socket;
    int packet_size;

    RosalilaNet();
    UDPpacket* receivee();
    void init();
    ~RosalilaNet();
    bool send(string message);
    string internalReceive();
    string receive();
    std::pair<string, string> receive2PlayerBuffers();
    void update();
};

#endif
