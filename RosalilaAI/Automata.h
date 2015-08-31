#ifndef AUTOMATA2_H
#define AUTOMATA2_H


#include "Estado.h"
#include "../TinyXml/tinyxml.h"
#include "../RosalilaUtility/RosalilaUtility.h"
#include <vector>
using namespace std;

class Automata
{
    std::map<std::string,Estado*> estados;
    std::string estado_actual;
    int wait;
public:
Transicion *transicion_a_recompenzar;
    Automata(string archivo,string archivo_default);
    Estado* getEstadoInicial();
    std::string getNextRosalilaInputs(std::map<std::string,std::string>*strings,
                         std::map<std::string,std::string>*strings_contrario,
                         std::map<std::string,int>*enteros,
                         std::map<std::string,int>*enteros_contrario
                         );
    void loadFromXML(string archivo,string archivo_default);
};

#endif
