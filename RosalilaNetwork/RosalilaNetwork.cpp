//#include "RosalilaNetwork/RosalilaNetwork.h"
//
//RosalilaNetwork::RosalilaNetwork(RosalilaGraphics *painter)
//{
//    this->painter=painter;
//}
//
//string RosalilaNetwork::runTcpClientSendScore(unsigned short port, string address, string stage_name, string username, int score)
//{
////    // Ask for the server address
////    sf::IpAddress server = address.c_str();
////
////    // Create a socket for communicating with the server
////    sf::TcpSocket socket;
////
////    // Connect to the server
////    if (socket.connect(server, port) != sf::Socket::Done)
////        return "Error: could not connect to server.";
////    std::cout << "Connected to server " << server << std::endl;
////
////    // Receive a message from the server
////    char in[128];
////    std::size_t received;
////    if (socket.receive(in, sizeof(in), received) != sf::Socket::Done)
////        return "Error: no message received from server";
////    std::cout << "Message received from the server: \"" << in << "\"" << std::endl;
////
////    // Send an answer to the server
////    //char* out = new char[username.length() + 1 + score.length() + 1];
////	char out[128]="";
////	strcat(out,stage_name.c_str());
////	strcat(out,"-");
////	strcat(out,username.c_str());
////	strcat(out,"-");
////	strcat(out,toString(score).c_str());
////
////    if (socket.send(out, sizeof(out)) != sf::Socket::Done)
////        return "Error: could not send message to the server.";
////    std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;
////
////    char exit_message[128];
////    std::size_t received_exit_message;
////    if (socket.receive(exit_message, sizeof(exit_message), received_exit_message) != sf::Socket::Done)
////        return "Error: no exit_message received from server";
////    std::cout << "Message received from the server: \"" << exit_message << "\"" << std::endl;
////
////	return exit_message;
//    return "Error: no network implemented";
//}
