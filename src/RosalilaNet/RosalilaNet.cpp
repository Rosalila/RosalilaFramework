#include "RosalilaNet/RosalilaNet.h"

/*
RosalilaNet::RosalilaNet()
{
}

void RosalilaNet::init()
{
  Node *config_node = rosalila()->parser->getNodes(CONFIG_FILE_PATH);
  Node *network_node = config_node->getNodeByName("Network");
  std::string server_ip_str = network_node->attributes["server_ip"];
  int server_port = atoi(network_node->attributes["server_port"].c_str());
  this->packet_size = atoi(network_node->attributes["packet_size"].c_str());

  if (SDLNet_Init() == -1)
  {
    rosalila()->utility->writeLogLine("Error initializing SDLNet: " + std::string(SDLNet_GetError()));
  }
  else
  {
    rosalila()->utility->writeLogLine("SDLNet initialized");
  }

  udp_socket = SDLNet_UDP_Open(0);

  if (udp_socket == nullptr)
  {
    rosalila()->utility->writeLogLine("SDLNet_UDP_Open failed: " + std::string(SDLNet_GetError()));
  }
  else
  {
    rosalila()->utility->writeLogLine("UDP port open successfully");
  }

  if (SDLNet_ResolveHost(&server_ip, (char *)server_ip_str.c_str(), server_port) == -1)
  {
    rosalila()->utility->writeLogLine("SDLNet_ResolveHost failed: " + std::string(SDLNet_GetError()));
  }
  else
  {
    rosalila()->utility->writeLogLine("Host resolved successfully");
  }

  packet_server = SDLNet_AllocPacket(packet_size);
  packet_server->address.host = server_ip.host;
  packet_server->address.port = server_ip.port;

  packet_peer = NULL;

  on_create_room = NULL;
  on_connect = NULL;
}

RosalilaNet::~RosalilaNet()
{
  SDLNet_FreePacket(packet_server);
  SDLNet_FreePacket(packet_peer);
  SDLNet_Quit();
}

bool RosalilaNet::sendToPacket(UDPpacket *packet, std::string message)
{
  if ((int)message.size() + 1 > packet_size)
    return false;

  memcpy(packet->data, message.c_str(), message.length() + 1);
  packet->len = message.length() + 1;

  if (SDLNet_UDP_Send(udp_socket, -1, packet) == 0)
  {
    rosalila()->utility->writeLogLine("SDLNet_UDP_Send failed: " + std::string(SDLNet_GetError()));
    return false;
  }

  return true;
}

bool RosalilaNet::send(string message)
{
  if (packet_peer)
    return sendToPacket(packet_peer, message);
  else
    return sendToPacket(packet_server, message);
}

std::string RosalilaNet::receiveFromPacket(UDPpacket *packet, IPaddress ip_address)
{
  int numrecv = SDLNet_UDP_Recv(udp_socket, packet);
  if (numrecv == 1)
  {
    if (packet->address.host == ip_address.host && packet->address.port == ip_address.port)
      return (char *)packet->data;
  }

  if (numrecv == -1)
    rosalila()->utility->writeLogLine("SDLNet_UDP_Recv failed");
  
  return "";
}

std::vector<string> RosalilaNet::receive()
{
  std::vector<string> result;
  
  while (true)
  {
    string received = "";
    if (packet_peer)
      received = receiveFromPacket(packet_peer, peer_ip);
    else
      received = receiveFromPacket(packet_server, server_ip);

    if (received != "")
      result.push_back(received);
    else
      break;
  }

  return result;
}

void RosalilaNet::onConnectionComplete(std::vector<std::string> received_messages)
{
  if (received_messages.size() > 0)
  {
    rosalila()->utility->writeLogLine("Received message from matchmaking server");
    for (auto received_message : received_messages)
    {
      rosalila()->utility->writeLogLine("Message received: " + received_message);

      stringstream stringstream_message(received_message);
      string token;
      vector<std::string> tokens;
      while (getline(stringstream_message, token, ' '))
      {
        tokens.push_back(token);
      }
      if (tokens.size() == 3 && tokens[0] == "connected")
      {
        rosalila()->utility->writeLogLine("Connection found!");
        int peer_host = atoi(tokens[1].c_str());
        int peer_port = atoi(tokens[2].c_str());

        packet_peer = SDLNet_AllocPacket(packet_size);
        packet_peer->address.host = peer_ip.host = peer_host;
        packet_peer->address.port = peer_ip.port = peer_port;

        rosalila()->utility->writeLogLine("Peer host: " + rosalila()->utility->toString(packet_peer->address.host));
        rosalila()->utility->writeLogLine("Peer port: " + rosalila()->utility->toString(packet_peer->address.port));
      }
    }
  }
}

void RosalilaNet::update()
{
  if (on_create_room)
  {
    std::vector<std::string> received_messages = this->receive();
    if (received_messages.size() > 0)
    {
      on_create_room(0, received_messages[0]);
      on_create_room = NULL;
    }
  }
  else if (on_player2_join)
  {
    std::vector<std::string> received_messages = this->receive();
    if (received_messages.size() > 0)
    {
      onConnectionComplete(received_messages);
      on_player2_join(0);
      on_player2_join = NULL;
    }
  }

  if (on_connect)
  {
    std::vector<std::string> received_messages = this->receive();
    if (received_messages.size() > 0)
    {
      onConnectionComplete(received_messages);
      on_connect(0);
      on_connect = NULL;
    }
  }
}

void RosalilaNet::createRoom(const std::function<void(int response_code, std::string &room_key)> &on_create_room,
                             const std::function<void(int response_code)> &on_player2_join)
{
  this->on_create_room = on_create_room;
  this->on_player2_join = on_player2_join;
  this->send("create_room");
}

void RosalilaNet::joinRoom(std::string room_key, const std::function<void(int response_code)> &callback)
{
  this->on_connect = callback;
  this->send("join " + room_key);
}

void RosalilaNet::disconnectFromPeer()
{
  if (packet_peer)
  {
    SDLNet_FreePacket(packet_peer);
    packet_peer = NULL;
  }
}

*/