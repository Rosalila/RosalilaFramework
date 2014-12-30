#ifndef ESTADO_H
#define ESTADO_H

#include "Transicion.h"
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;
#include "Estado.h"

class Estado
{
public:
    std::vector<Transicion*>transiciones;
    Estado(vector<Transicion*>transiciones);
    Transicion* getNextTransicion(std::map<std::string,std::string>*strings,
                                  std::map<std::string,std::string>*strings_contrario,
                                  std::map<std::string,int>*enteros,
                                  std::map<std::string,int>*enteros_contrario
                                  );
};

#endif
