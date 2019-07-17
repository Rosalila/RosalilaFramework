#include "Rosalila.h"

int main()
{
  rosalila()->init("../assets/config.json");
  Image* image = rosalila()->graphics->getImage("../assets/image.png");

  Node* example_root_node = rosalila()->parser->getNodes("../assets/example.json");
  
  std::string a = example_root_node->attributes["a"];
  std::string b = example_root_node->attributes["b"];
  Node* tag = example_root_node->getNodeByName("Tag");
  std::string subtag = tag->attributes["Subtag"];
  vector<Node*> array = example_root_node->getNodesByName("Array");
  std::string array_string = "";
  for(auto array_element : array)
  {
    array_string += array_element->attributes["value"] += ",";
  }

  while(true)
  {
    rosalila()->graphics->drawRectangle(0,0,rosalila()->graphics->screen_width,rosalila()->graphics->screen_height,0,0,0,0,255);
    rosalila()->graphics->drawText("a: " + a, 0, -100, true, true);
    rosalila()->graphics->drawText("b: " + b, 0, -50, true, true);
    rosalila()->graphics->drawText("Subtag: " + subtag, 0, 0, true, true);
    rosalila()->graphics->drawText("Array: " + array_string, 0, 50, true, true);
    rosalila()->update();
  }
  return 0;
}