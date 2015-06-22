#include "RosalilaInputs.h"
#include <sstream>

void RosalilaInputs::actualizarBuffer(std::map<std::string,std::string>*strings,
                             std::map<std::string,std::string>*strings_contrario,
                             std::map<std::string,int>*enteros,
                             std::map<std::string,int>*enteros_contrario
                             )
{
    std::string resultado="";
    if(!inteligencia_artificial)
    {
        for(int i=0;i<(int)cruz.size();i++)
            if(cruz[i].estaPresionado())
                resultado+=cruz[i].getMapeo();
        if(resultado=="24" || resultado=="42")
            resultado="1";
        if(resultado=="26" || resultado=="62")
            resultado="3";
        if(resultado=="84" || resultado=="48")
            resultado="7";
        if(resultado=="68" || resultado=="86")
            resultado="9";
        if(tecla_arriba)
        {
            tecla_arriba=false;
            for(int i=0;i<(int)botones.size();i++)
                if(botones[i].estaPresionado())
                    resultado+=botones[i].getMapeo();
        }
        bool flag=false;
        for(int i=0;i<(int)botones.size();i++)
            if(botones[i].estaPresionado())
                flag=true;
        if(!flag)
            tecla_arriba=true;
    }
    else
    {
        resultado=ia->getRosalilaInputs(strings,strings_contrario,enteros,enteros_contrario);
    }
    if(resultado=="")
        resultado="5";

    if(std::string(strings->operator[]("orientation"))==std::string("i"))
    {
        for(int i=0;i<(int)resultado.size();i++)
        {
            if(resultado[i]=='4')resultado[i]='6';
            else if(resultado[i]=='6')resultado[i]='4';
            else if(resultado[i]=='3')resultado[i]='1';
            else if(resultado[i]=='1')resultado[i]='3';
            else if(resultado[i]=='7')resultado[i]='9';
            else if(resultado[i]=='9')resultado[i]='7';
        }
    }
    buffer_inputs.insert(buffer_inputs.begin(),resultado);
    buffer_inputs.pop_back();

    if(resultado!=printable_buffer_inputs[0])
    {
        printable_buffer_inputs.insert(printable_buffer_inputs.begin(),resultado);
        printable_buffer_inputs.pop_back();
    }
}

void RosalilaInputs::actualizarBuffer()
{
    std::string resultado="";
    for(int i=0;i<(int)cruz.size();i++)
    {
        if(cruz[i].estaPresionado())
        {
            resultado+=cruz[i].getMapeo();
        }
    }

    if(resultado=="24" || resultado=="42")
        resultado="1";
    if(resultado=="26" || resultado=="62")
        resultado="3";
    if(resultado=="84" || resultado=="48")
        resultado="7";
    if(resultado=="68" || resultado=="86")
        resultado="9";
    if(tecla_arriba)
    {
        tecla_arriba=false;
        for(int i=0;i<(int)botones.size();i++)
            if(botones[i].estaPresionado())
                resultado+=botones[i].getMapeo();
    }
    bool flag=false;
    for(int i=0;i<(int)botones.size();i++)
        if(botones[i].estaPresionado())
            flag=true;
    if(!flag)
        tecla_arriba=true;
    if(resultado=="")
        resultado="5";

    buffer_inputs.insert(buffer_inputs.begin(),resultado);
    buffer_inputs.pop_back();
}

vector<std::string> RosalilaInputs::getBufferRosalilaInputs()
{
    return buffer_inputs;
}

vector<std::string> RosalilaInputs::getPrintableBufferRosalilaInputs()
{
    return printable_buffer_inputs;
}

//std::string stringw_to_stdstring(irr::core::stringw sw)
//{
//    std::stringstream ss;
//        ss << sw.c_str();
//        return ss.str();
//}


void RosalilaInputs::loadFromXML(int jugador,Receiver* receiver)
{
    this->jugador=jugador;
    this->receiver=receiver;
    this->inteligencia_artificial=false;
    string xml_path=assets_directory+"misc/inputs.xml";
    TiXmlDocument doc_t(xml_path.c_str());
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    std::vector<Boton> botones_temp;
    for(TiXmlNode* input=doc->FirstChild("Input");
            input!=NULL;
            input=input->NextSibling("Input"))
    {
        if(jugador==atoi(input->ToElement()->Attribute("player")))
        {
            //Key
            if(strcmp("keyboard",input->ToElement()->Attribute("type"))==0)
            {
                for(TiXmlNode* boton=input->FirstChild("button");
                        boton!=NULL;
                        boton=boton->NextSibling("button"))
                {
                    int key=0;
                    if(boton->ToElement()->Attribute("input")[0]=='Q' || boton->ToElement()->Attribute("input")[0]=='q')
                        key=SDLK_q;
                    if(boton->ToElement()->Attribute("input")[0]=='W' || boton->ToElement()->Attribute("input")[0]=='w')
                        key=SDLK_w;
                    if(boton->ToElement()->Attribute("input")[0]=='E' || boton->ToElement()->Attribute("input")[0]=='e')
                        key=SDLK_e;
                    if(boton->ToElement()->Attribute("input")[0]=='R' || boton->ToElement()->Attribute("input")[0]=='r')
                        key=SDLK_r;
                    if(boton->ToElement()->Attribute("input")[0]=='T' || boton->ToElement()->Attribute("input")[0]=='t')
                        key=SDLK_t;
                    if(boton->ToElement()->Attribute("input")[0]=='Y' || boton->ToElement()->Attribute("input")[0]=='y')
                        key=SDLK_y;
                    if(boton->ToElement()->Attribute("input")[0]=='U' || boton->ToElement()->Attribute("input")[0]=='u')
                        key=SDLK_u;
                    if(boton->ToElement()->Attribute("input")[0]=='I' || boton->ToElement()->Attribute("input")[0]=='i')
                        key=SDLK_i;
                    if(boton->ToElement()->Attribute("input")[0]=='O' || boton->ToElement()->Attribute("input")[0]=='o')
                        key=SDLK_o;
                    if(boton->ToElement()->Attribute("input")[0]=='P' || boton->ToElement()->Attribute("input")[0]=='p')
                        key=SDLK_p;
                    if(boton->ToElement()->Attribute("input")[0]=='A' || boton->ToElement()->Attribute("input")[0]=='a')
                        key=SDLK_a;
                    if(boton->ToElement()->Attribute("input")[0]=='S' || boton->ToElement()->Attribute("input")[0]=='s')
                        key=SDLK_s;
                    if(boton->ToElement()->Attribute("input")[0]=='D' || boton->ToElement()->Attribute("input")[0]=='d')
                        key=SDLK_d;
                    if(boton->ToElement()->Attribute("input")[0]=='F' || boton->ToElement()->Attribute("input")[0]=='f')
                        key=SDLK_f;
                    if(boton->ToElement()->Attribute("input")[0]=='G' || boton->ToElement()->Attribute("input")[0]=='g')
                        key=SDLK_g;
                    if(boton->ToElement()->Attribute("input")[0]=='H' || boton->ToElement()->Attribute("input")[0]=='h')
                        key=SDLK_h;
                    if(boton->ToElement()->Attribute("input")[0]=='J' || boton->ToElement()->Attribute("input")[0]=='j')
                        key=SDLK_j;
                    if(boton->ToElement()->Attribute("input")[0]=='K' || boton->ToElement()->Attribute("input")[0]=='k')
                        key=SDLK_k;
                    if(boton->ToElement()->Attribute("input")[0]=='L' || boton->ToElement()->Attribute("input")[0]=='l')
                        key=SDLK_l;
                    if(boton->ToElement()->Attribute("input")[0]=='Z' || boton->ToElement()->Attribute("input")[0]=='z')
                        key=SDLK_z;
                    if(boton->ToElement()->Attribute("input")[0]=='X' || boton->ToElement()->Attribute("input")[0]=='x')
                        key=SDLK_x;
                    if(boton->ToElement()->Attribute("input")[0]=='C' || boton->ToElement()->Attribute("input")[0]=='c')
                        key=SDLK_c;
                    if(boton->ToElement()->Attribute("input")[0]=='V' || boton->ToElement()->Attribute("input")[0]=='v')
                        key=SDLK_v;
                    if(boton->ToElement()->Attribute("input")[0]=='B' || boton->ToElement()->Attribute("input")[0]=='b')
                        key=SDLK_b;
                    if(boton->ToElement()->Attribute("input")[0]=='N' || boton->ToElement()->Attribute("input")[0]=='n')
                        key=SDLK_n;
                    if(boton->ToElement()->Attribute("input")[0]=='M' || boton->ToElement()->Attribute("input")[0]=='m')
                        key=SDLK_m;
                    botones_temp.push_back(Boton(receiver,key,std::string(boton->ToElement()->Attribute("map"))));
                }
            }
            //Joy
            if(strcmp("joystick",input->ToElement()->Attribute("type"))==0)
            {
                for(TiXmlNode* boton=input->FirstChild("button");
                        boton!=NULL;
                        boton=boton->NextSibling("button"))
                {
                    int int_boton;
                    if(strcmp(boton->ToElement()->Attribute("input"),"up")==0)
                        int_boton=-8;
                    else if(strcmp(boton->ToElement()->Attribute("input"),"down")==0)
                        int_boton=-2;
                    else if(strcmp(boton->ToElement()->Attribute("input"),"left")==0)
                        int_boton=-4;
                    else if(strcmp(boton->ToElement()->Attribute("input"),"right")==0)
                        int_boton=-6;
                    else
                        int_boton=boton->ToElement()->Attribute("input")[0]-48;
                    botones_temp.push_back(Boton(receiver,int_boton,input->ToElement()->Attribute("joystick_number")[0]-48,boton->ToElement()->Attribute("map")));
                }
            }
        }
    }

    tecla_arriba=true;
    for(int i=0;i<20;i++)
        buffer_inputs.push_back("5");
    for(int i=0;i<20;i++)
        printable_buffer_inputs.push_back("5");
    for(int i=0;i<(int)botones_temp.size();i++)
    {
        if(botones_temp[i].getMapeo()=="2" || botones_temp[i].getMapeo()=="4" || botones_temp[i].getMapeo()=="6" || botones_temp[i].getMapeo()=="8")
        {
            this->cruz.push_back(botones_temp[i]);
        }
        else
        {
            this->botones.push_back(botones_temp[i]);
        }
    }
}

void RosalilaInputs::cargarRosalilaAIXML(int jugador,std::string archivo,std::string archivo_default)
{
    this->jugador=jugador;
    this->inteligencia_artificial=true;
    tecla_arriba=true;
    for(int i=0;i<20;i++)
        buffer_inputs.push_back("5");
    for(int i=0;i<20;i++)
        printable_buffer_inputs.push_back("5");
    ia=new RosalilaAI(archivo,archivo_default);

    tecla_arriba=true;
    for(int i=0;i<20;i++)
        buffer_inputs.push_back("5");
    for(int i=0;i<20;i++)
        printable_buffer_inputs.push_back("5");
    for(int i=0;i<(int)botones.size();i++)
    {
        if(botones[i].getMapeo()=="2" || botones[i].getMapeo()=="4" || botones[i].getMapeo()=="6" || botones[i].getMapeo()=="8")
        {
            this->cruz.push_back(botones[i]);
        }
        else
        {
            this->botones.push_back(botones[i]);
        }
    }
}
TiXmlDocument* RosalilaInputs::getXML(TiXmlDocument *doc)
{
 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );
	doc->LinkEndChild( decl );

	TiXmlElement * root = new TiXmlElement( "Input" );
	doc->LinkEndChild( root );
	root->SetDoubleAttribute("player",jugador);
	root->SetAttribute("type", "keyboard");

	for(int i=0;i<(int)botones.size();i++)
	{
	    if(botones[i].usaJoystick())
            continue;
        TiXmlElement * cxn = new TiXmlElement( "button" );
        root->LinkEndChild( cxn );
        cxn->SetAttribute("input", (char*)botones[i].getRosalilaInputs().c_str());
        cxn->SetAttribute("map", (char*)botones[i].getMapeo().c_str());
	}
	for(int i=0;i<(int)cruz.size();i++)
	{
	    if(cruz[i].usaJoystick())
            continue;
        TiXmlElement * cxn = new TiXmlElement( "button" );
        root->LinkEndChild( cxn );
        if(cruz[i].getRosalilaInputs()[0]=='d')
            cxn->SetAttribute("input", "down");
        else if(cruz[i].getRosalilaInputs()[0]=='l')
            cxn->SetAttribute("input", "left");
        else if(cruz[i].getRosalilaInputs()[0]=='r')
            cxn->SetAttribute("input", "right");
        else if(cruz[i].getRosalilaInputs()[0]=='u')
            cxn->SetAttribute("input", "up");
        else
            cxn->SetAttribute("input", (char*)cruz[i].getRosalilaInputs().c_str());
        cxn->SetAttribute("map", (char*)cruz[i].getMapeo().c_str());
	}


    //Joystick
	root = new TiXmlElement( "Input" );
	doc->LinkEndChild( root );
	root->SetDoubleAttribute("player",jugador);
	root->SetAttribute("type", "joystick");

	for(int i=0;i<(int)botones.size();i++)
	{
	    if(!botones[i].usaJoystick())
            continue;
        root->SetDoubleAttribute("joystick_number",botones[i].getNumJoystick());
        TiXmlElement * cxn = new TiXmlElement( "button" );
        root->LinkEndChild( cxn );
        cxn->SetAttribute("input", (char*)botones[i].getRosalilaInputs().c_str());
        cxn->SetAttribute("map", (char*)botones[i].getMapeo().c_str());
	}
	for(int i=0;i<(int)cruz.size();i++)
	{
	    if(!cruz[i].usaJoystick())
            continue;
        TiXmlElement * cxn = new TiXmlElement( "button" );
        root->LinkEndChild( cxn );
        if(cruz[i].getRosalilaInputs()[0]=='d')
            cxn->SetAttribute("input", "down");
        else if(cruz[i].getRosalilaInputs()[0]=='l')
            cxn->SetAttribute("input", "left");
        else if(cruz[i].getRosalilaInputs()[0]=='r')
            cxn->SetAttribute("input", "right");
        else if(cruz[i].getRosalilaInputs()[0]=='u')
            cxn->SetAttribute("input", "up");
        else
            cxn->SetAttribute("input", (char*)cruz[i].getRosalilaInputs().c_str());
        cxn->SetAttribute("map", (char*)cruz[i].getMapeo().c_str());
	}

	return doc;
	//doc->SaveFile( "appsettings.xml" );
}

void RosalilaInputs::limpiarBuffer()
{
    buffer_inputs.clear();
    for(int i=0;i<20;i++)
        buffer_inputs.push_back("5");
}

void RosalilaInputs::editInput(int player,int joystick_number,string input,string map)
{
    string player_str=toString(player);
    string joystick_number_str=toString(joystick_number);
    string xml_path=assets_directory+"misc/inputs.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    for(TiXmlNode* input_node=doc.FirstChild("Input");
            input_node!=NULL;
            input_node=input_node->NextSibling("Input"))
    {
        if(strcmp("joystick",input_node->ToElement()->Attribute("type"))==0
           && strcmp(player_str.c_str(),input_node->ToElement()->Attribute("player"))==0
           && strcmp(joystick_number_str.c_str(),input_node->ToElement()->Attribute("joystick_number"))==0
           )
        {
            for(TiXmlNode* boton=input_node->FirstChild("button");
                    boton!=NULL;
                    boton=boton->NextSibling("button"))
            {
                if(strcmp(boton->ToElement()->Attribute("map"),map.c_str())==0)
                {
                    boton->ToElement()->FirstAttribute()->SetValue(input.c_str());
                    for(TiXmlAttribute* button_attributes = boton->ToElement()->FirstAttribute();
                        button_attributes!=NULL;
                        button_attributes=button_attributes->Next()
                        )
                    {
                        if(strcmp(button_attributes->Name(),"input")==0)
                        {
                            button_attributes->SetValue(input.c_str());
                        }
                    }
                }
            }
        }
    }
    string path = assets_directory+"misc/inputs.xml";
    doc.SaveFile(path.c_str());
}

void RosalilaInputs::editKeyboardInput(int player,string input,string map)
{
    string player_str=toString(player);
    string xml_path=assets_directory+"misc/inputs.xml";
    TiXmlDocument doc(xml_path.c_str());
    doc.LoadFile();
    for(TiXmlNode* input_node=doc.FirstChild("Input");
            input_node!=NULL;
            input_node=input_node->NextSibling("Input"))
    {
        if(strcmp("keyboard",input_node->ToElement()->Attribute("type"))==0
           && strcmp(player_str.c_str(),input_node->ToElement()->Attribute("player"))==0
           )
        {
            for(TiXmlNode* boton=input_node->FirstChild("button");
                    boton!=NULL;
                    boton=boton->NextSibling("button"))
            {
                if(strcmp(boton->ToElement()->Attribute("map"),map.c_str())==0)
                {
                    boton->ToElement()->FirstAttribute()->SetValue(input.c_str());
                    for(TiXmlAttribute* button_attributes = boton->ToElement()->FirstAttribute();
                        button_attributes!=NULL;
                        button_attributes=button_attributes->Next()
                        )
                    {
                        if(strcmp(button_attributes->Name(),"input")==0)
                        {
                            button_attributes->SetValue(input.c_str());
                        }
                    }
                }
            }
        }
    }
    string path = assets_directory+"misc/inputs.xml";
    doc.SaveFile(path.c_str());
}

string RosalilaInputs::getJoystickInput(string map, int num_joystick)
{
    for(int i=0;i<(int)botones.size();i++)
    {
        if(botones[i].usaJoystick()
            && map == botones[i].getMapeo()
            && num_joystick == botones[i].getNumJoystick())
        {
            return botones[i].getRosalilaInputs();
        }
    }
    return "Error: no input.";
}

string RosalilaInputs::getKeyboardInput(string map)
{
    for(int i=0;i<(int)botones.size();i++)
    {
        if(!botones[i].usaJoystick()
            && map == botones[i].getMapeo())
        {
            return botones[i].getRosalilaInputs();
        }
    }

    for(int i=0;i<(int)cruz.size();i++)
    {
        if(!cruz[i].usaJoystick()
            && map == cruz[i].getMapeo())
        {
            return cruz[i].getRosalilaInputs();
        }
    }
    return "Error: no input.";
}
