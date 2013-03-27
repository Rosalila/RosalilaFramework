#ifndef INPUT_H
#define INPUT_H

#include "RosalilaInputs/Boton.h"
#include <RosalilaAI/RosalilaAI.h>

class RosalilaInputs
{
protected:
    std::vector<std::string> buffer_inputs;
    int jugador;

public:
Receiver* receiver;
bool tecla_arriba;
RosalilaAI *ia;
bool inteligencia_artificial;
vector<Boton> botones;
vector<Boton> cruz;
    RosalilaInputs(){}
    void loadFromXML(int jugador,Receiver* receiver);
    void cargarRosalilaAIXML(int jugador,std::string archivo,std::string archivo_default);
    TiXmlDocument* getXML(TiXmlDocument *doc);
    void actualizarBuffer();
    void actualizarBuffer(std::map<std::string,std::string>*strings,
                          std::map<std::string,std::string>*strings_contrario,
                          std::map<std::string,int>*enteros,
                          std::map<std::string,int>*enteros_contrario
                          );
    std::vector<std::string> getBufferRosalilaInputss();
    void endEventProcess();
    void startEventProcess();
};

#endif
