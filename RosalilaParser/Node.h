#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Node
{
public:
    map<string,string>attributes;
    multimap<string,Node*>nodes;
    Node(map<string,string>attributes,multimap<string,Node*>nodes);
    ~Node();
    bool hasAttribute(string name);
    Node*getNodeByName(string name);
    vector<Node*> getNodesByName(string name);
};

#endif
