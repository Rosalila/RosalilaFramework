#include "Node.h"

Node::Node(map<string,string>attributes,multimap<string,Node*>nodes)
{
    this->attributes=attributes;
    this->nodes=nodes;
}

bool Node::hasAttribute(string name)
{
    return this->attributes.count(name);
}

Node* Node::getNodeByName(string name)
{
    for(map<string,Node*>::iterator hitbox_iterator=nodes.begin();
        hitbox_iterator!=nodes.end();
        hitbox_iterator++)
    {
        if(name==hitbox_iterator->first)
            return hitbox_iterator->second;
    }
    return NULL;
}
