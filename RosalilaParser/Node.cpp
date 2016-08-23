#include "Node.h"

Node::Node(map<string,string>attributes,map<string,Node*>nodes)
{
    this->attributes=attributes;
    this->nodes=nodes;
}

bool Node::hasAttribute(string name)
{
    return this->attributes.count(name);
}
