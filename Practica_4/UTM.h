//
// Created by stefan on 09/10/2023.
//

#ifndef PRACTICA_1B_UTM_H
#define PRACTICA_1B_UTM_H

#include "iostream"

class UTM {
private:
    float latitud=0;
    float longitud=0;
public:
    //Constructores y destructores
    UTM()=default;
    UTM(float latitud, float longitud);
    virtual ~UTM();
    //Getters y Setters
    float getLatitud() const;
    void setLatitud(float latitud);
    float getLongitud() const;
    void setLongitud(float longitud);



};

#endif //PRACTICA_1B_UTM_H
