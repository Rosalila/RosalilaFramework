#include "Rosalila.h"

int main()
{
  rosalila()->init("../assets/config.json");

  Image *image = rosalila()->graphics->getTexture("../assets/image.png");

  std::cout << "Type your room key or create to create a new room" << std::endl;
  std::string message;
  std::cin >> message;

  int player_number;
  bool wait = true;
  if (message == "create")
  {
    player_number = 1;
    rosalila()->net->createRoom([&](int response_code, std::string &room_key) { std::cout << room_key << std::endl; },
                                [&](int response_code) {
                                  std::cout << "Player 2 joined" << std::endl;
                                  wait = false;
                                });
  }
  else
  {
    player_number = 2;
    rosalila()->net->joinRoom(message, [&](int response_code) {
      std::cout << "connected" << std::endl;
      wait = false;
    });
  }

  while (wait)
  {
    rosalila()->update();
  }

  int player1_x = 0;
  int player1_y = 0;

  int player2_x = 500;
  int player2_y = 0;
  int player_1 = 0;
  bool mirror_image = false;

  while (true)
  {
    rosalila()->graphics->draw2DImage(image,
                                      image->getWidth(), image->getHeight(),
                                      player1_x, player1_y,
                                      1.0,
                                      0.0,
                                      mirror_image,
                                      Color(255, 0, 0, 255));

    rosalila()->graphics->draw2DImage(image,
                                      image->getWidth(), image->getHeight(),
                                      player2_x, player2_y,
                                      1.0,
                                      0.0,
                                      mirror_image,
                                      Color(0, 0, 255, 255));

    if (rosalila()->receiver->isDown(player_1, "left"))
    {
      rosalila()->net->send("left");
      if (player_number == 1)
        player1_x--;
      if (player_number == 2)
        player2_x--;
    }
    if (rosalila()->receiver->isDown(player_1, "right"))
    {
      rosalila()->net->send("right");
      if (player_number == 1)
        player1_x++;
      if (player_number == 2)
        player2_x++;
    }
    if (rosalila()->receiver->isDown(player_1, "up"))
    {
      rosalila()->net->send("up");
      if (player_number == 1)
        player1_y--;
      if (player_number == 2)
        player2_y--;
    }
    if (rosalila()->receiver->isDown(player_1, "down"))
    {
      rosalila()->net->send("down");
      if (player_number == 1)
        player1_y++;
      if (player_number == 2)
        player2_y++;
    }

    std::vector<std::string> received_messages = rosalila()->net->receive();
    for (auto received_message : received_messages)
    {
      if (received_message == "left")
      {
        if (player_number == 1)
          player2_x--;
        if (player_number == 2)
          player1_x--;
      }
      if (received_message == "right")
      {
        if (player_number == 1)
          player2_x++;
        if (player_number == 2)
          player1_x++;
      }
      if (received_message == "up")
      {
        if (player_number == 1)
          player2_y--;
        if (player_number == 2)
          player1_y--;
      }
      if (received_message == "down")
      {
        if (player_number == 1)
          player2_y++;
        if (player_number == 2)
          player1_y++;
      }
    }

    rosalila()->update();
  }
  return 0;
}