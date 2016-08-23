#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <map>

using namespace std;

class Node
{
public:
    map<string,string>attributes;
    multimap<string,Node*>nodes;
    Node(map<string,string>attributes,multimap<string,Node*>nodes);
    bool hasAttribute(string name);
    Node*getNodeByName(string name);
};

#endif
