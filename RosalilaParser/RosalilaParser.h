#ifndef ROSALILA_PARSER_H
#define ROSALILA_PARSER_H

#include "Node.h"
#include "TinyXml/tinyxml.h"
#include "../Rosalila.h"
#include "../RosalilaUtility/RosalilaUtility.h"

class RosalilaParser
{
public:
    void init();
    map<string,string> getAttributes(TiXmlNode *node);
    multimap<string,Node*> getNodes(TiXmlNode *node);
    Node* getNodes(string file_name);
};

#endif
