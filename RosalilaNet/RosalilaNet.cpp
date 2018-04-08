#include "RosalilaNet.h"

RosalilaNet::RosalilaNet()
{

}

void RosalilaNet::init()
{
    Node* config_node = rosalila()->parser->getNodes(assets_directory+"config.xml");    
    Node* network_node = config_node->getNodeByName("Network");
    this->server_ip = network_node->attributes["server_ip"];
    this->server_port = atoi(network_node->attributes["server_port"].c_str());
    this->packet_size = atoi(network_node->attributes["packet_size"].c_str());



    if (SDLNet_Init() == -1)
    {
        std::cout << "\tSDLNet_Init failed : " << SDLNet_GetError() << std::endl;
    }
    else
    {
        std::cout << "SDL net inited" << std::endl;
    }

    server_socket = SDLNet_UDP_Open(0);

    if (server_socket == nullptr)
    {
        std::cout << "\tSDLNet_UDP_Open failed : " << SDLNet_GetError() << std::endl;
    }
    else
    {
        std::cout << "Conectedd" << std::endl;
    }

    if (SDLNet_ResolveHost(&serverIP, (char *)server_ip.c_str(), server_port) == -1)
    {
        std::cout << "\tSDLNet_ResolveHost failed : " << SDLNet_GetError() << std::endl;
    }
    else
    {
        std::cout << "Resolvedd" << std::endl;
    }

    packet = SDLNet_AllocPacket(packet_size);
    packet->address.host = serverIP.host;
    packet->address.port = serverIP.port;
}

RosalilaNet::~RosalilaNet()
{
    SDLNet_FreePacket(packet);
    SDLNet_Quit();
}

bool RosalilaNet::send(string message)
{
    if ((int)message.size() + 1 > packet_size)
    {
        return false;
    }

    memcpy(packet->data, message.c_str(), message.length() + 1);
    packet->len = message.length() + 1;

    if (SDLNet_UDP_Send(server_socket, -1, packet) == 0)
    {
        std::cout << "SDLNet_UDP_Send failed : " << SDLNet_GetError() << std::endl;
        return false;
    }
    return true;
}

UDPpacket* receiver_packett = NULL;
UDPpacket* RosalilaNet::receivee()
{
    if(receiver_packett)
        SDLNet_FreePacket(receiver_packett);
    receiver_packett = SDLNet_AllocPacket(packet_size);
    packet->address.host = serverIP.host;
    packet->address.port = serverIP.port;


  int numrecv=SDLNet_UDP_Recv(server_socket, receiver_packett);
  if(numrecv == 1)
  {
    return receiver_packett;
  }
  if(numrecv == -1)
  {
    std::cout << "Errorr : "<< std::endl;
  }
  return NULL;
}


string RosalilaNet::internalReceive()
{
    int numrecv = SDLNet_UDP_Recv(server_socket, packet);
    if (numrecv == 1)
    {
        if (packet->address.host == serverIP.host && packet->address.port == serverIP.port)
        {
            return (char *)packet->data;
        }
        else
        {
            return "";
        }
    }
    if (numrecv == -1)
    {
        std::cout << "Errorr : " << std::endl;
    }
    return "";
    /*
    */
}


string RosalilaNet::receive()
{
    string result = "";
    string received = "";
    do
    {
      received = internalReceive();
      result += received;
    } while(received!="");
    return result;
}

std::pair<string, string> RosalilaNet::receive2PlayerBuffers()
{
    pair<string, string> result;

    istringstream raw_data(receive());

    getline(raw_data, result.first, '|');
    getline(raw_data, result.second, '/');

    return result;
}

void RosalilaNet::update()
{
    /*
    string received_message = this->receive();
    if (received_message != "")
    {
        cout << "Received: " << received_message << endl;
    }
    */
}
