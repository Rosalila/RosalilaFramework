#ifndef INPUT_H
#define INPUT_H

#include "../system.h"
#include "../RosalilaInputs/Boton.h"
#include "../RosalilaAI/RosalilaAI.h"
class RosalilaAI;
class RosalilaInputs
{
protected:
    std::vector<std::string> buffer_inputs;
    std::vector<std::string> printable_buffer_inputs;
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
    std::vector<std::string> getBufferRosalilaInputs();
    std::vector<std::string> getPrintableBufferRosalilaInputs();
    void endEventProcess();
    void startEventProcess();
    void limpiarBuffer();
    void editInput(int player,int joystick_number,string input,string map);
    void editKeyboardInput(int player,string input,string map);
    string getJoystickInput(string map, int num_joystick);
    string getKeyboardInput(string map);
};

#endif
