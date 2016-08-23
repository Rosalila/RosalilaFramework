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

multimap<string,Node*> RosalilaParser::getNodes(TiXmlNode *node)
{
    multimap<string,Node*> nodes;
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
            nodes.insert(pair<string,Node*>(node_iterator->ToElement()->Value(),new_node));
        }
    }
    return nodes;
}

Node* RosalilaParser::getNodes(string file_name)
{
    std::string main_path=file_name;
    TiXmlDocument document(main_path.c_str());
    document.LoadFile();

    TiXmlNode *root_node=document.FirstChild();

    if(root_node)
    {
        return new Node(getAttributes(root_node)
                                  ,getNodes(root_node->FirstChild())
                                 );
    }

    return NULL;
}
