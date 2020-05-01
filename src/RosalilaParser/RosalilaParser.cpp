#include "RosalilaParser/RosalilaParser.h"

void RosalilaParser::init()
{
}

Node *jsonToNode(nlohmann::json json_object)
{
  map<string, string> attributes;
  multimap<string, Node *> nodes;

  for (nlohmann::json::iterator it = json_object.begin(); it != json_object.end(); ++it)
  {
    if (it.value().is_object())
    {
      std::string key = it.key();
      nlohmann::json value = it.value();
      nodes.insert(std::pair<string, Node *>(key, jsonToNode(value)));
    }
    else if (it.value().is_array())
    {
      std::string key = it.key();
      nlohmann::json array = it.value();
      for (nlohmann::json::iterator array_element = array.begin(); array_element != array.end(); ++array_element)
      {
        nodes.insert(std::pair<string, Node *>(key, jsonToNode(array_element.value())));
      }
    }
    else
    {
      attributes[it.key()] = it.value();
    }
  }

  return new Node(attributes, nodes);
}

Node *RosalilaParser::getNodes(string file_name)
{
  rosalila()->utility->writeLogLine("Parsing: " + file_name);

  std::ifstream ifs(file_name);
  nlohmann::json json_file;
  if (ifs.is_open())
  {
    try
    {
      ifs >> json_file;
    }
    catch (nlohmann::json::parse_error &e)
    {
      rosalila()->utility->writeLogLine(std::string("Error parsing json: ") + e.what());
      json_file = {};
    }
  }
  ifs.close();

  return jsonToNode(json_file);
}
