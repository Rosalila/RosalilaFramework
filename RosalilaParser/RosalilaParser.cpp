#include "RosalilaParser.h"

void RosalilaParser::init()
{

}

map<string,string> RosalilaParser::getAttributes(TiXmlNode *node)
{
    map<string,string> attributes;

    for(TiXmlAttribute* attribute = node->ToElement()->FirstAttribute();
        attribute!=NULL;
        attribute=attribute->Next())
    {
        attributes[attribute->Name()]=attribute->Value();
    }

    return attributes;
}

map<string,Node*> RosalilaParser::getNodes(TiXmlNode *node)
{
    map<string,Node*> nodes;
    if(node)
    for(TiXmlNode *node_iterator=node;
        node_iterator!=NULL;
        node_iterator=node_iterator->NextSibling())
    {
        if(node_iterator->ToElement())
        {
            Node* new_node = new Node(getAttributes(node_iterator)
                                      ,getNodes(node_iterator->FirstChild())
                                     );
            nodes[node_iterator->ToElement()->Value()]=new_node;
        }
    }
    return nodes;
}

map<string,Node*> RosalilaParser::getNodes(string file_name)
{
    map<string,Node*> nodes;

    std::string main_path=file_name;
    TiXmlDocument document(main_path.c_str());
    document.LoadFile();

    for(TiXmlNode *node_iterator=document.FirstChild();
        node_iterator!=NULL;
        node_iterator=node_iterator->NextSibling())
    {
        Node* new_node = new Node(getAttributes(node_iterator)
                                  ,getNodes(node_iterator->FirstChild())
                                 );
        nodes[node_iterator->ToElement()->Value()]=new_node;
    }

    return nodes;
}
