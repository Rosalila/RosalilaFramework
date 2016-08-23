#ifndef ROSALILA_PARSER_H
#define ROSALILA_PARSER_H

#include "Node.h"
#include "../Rosalila.h"
#include "../RosalilaUtility/RosalilaUtility.h"

class RosalilaParser
{
public:
    void init();
    map<string,string> getAttributes(TiXmlNode *node);
    map<string,Node*> getNodes(TiXmlNode *node);
    map<string,Node*> getNodes(string file_name);
};

#endif
