#include "Node.h"

Node::Node(map<string,string>attributes,multimap<string,Node*>nodes)
{
    this->attributes=attributes;
    this->nodes=nodes;
}

Node::~Node()
{
    for(multimap<string,Node*>::iterator i = nodes.begin(); i!=nodes.end(); i++)
    {
        delete (*i).second;
    }
}

bool Node::hasAttribute(string name)
{
    return this->attributes.count(name);
}

Node* Node::getNodeByName(string name)
{
    for(map<string,Node*>::iterator nodes_iterator=nodes.begin();
        nodes_iterator!=nodes.end();
        nodes_iterator++)
    {
        if(name==nodes_iterator->first)
            return nodes_iterator->second;
    }
    return NULL;
}

vector<Node*> Node::getNodesByName(string name)
{
    vector<Node*> nodes_return;
    for(map<string,Node*>::iterator nodes_iterator=nodes.begin();
        nodes_iterator!=nodes.end();
        nodes_iterator++)
    {
        if(name==nodes_iterator->first)
            nodes_return.push_back(nodes_iterator->second);
    }
    return nodes_return;
}
