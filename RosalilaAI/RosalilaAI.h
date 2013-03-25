#ifndef RosalilaAI_H
#define RosalilaAI_H

#include "RosalilaAI/Automata.h"
#include <cstdlib>
#include <iostream>
using namespace std;

class RosalilaAI
{
    Automata *automata;
public:
    Transicion *transicion_a_recompenzar;
    RosalilaAI(char* archivo,char* archivo_default);
    std::string getRosalilaInputs(std::map<std::string,std::string>*strings,
                     std::map<std::string,std::string>*strings_contrario,
                     std::map<std::string,int>*enteros,
                     std::map<std::string,int>*enteros_contrario
                     );
    void darRecompensa();
    void quitarRecompensa();
};

#endif
