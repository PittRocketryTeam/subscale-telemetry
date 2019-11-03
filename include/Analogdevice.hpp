#ifndef ANALOGDEVICES_HPP
#define ANALOGDEVICES_HPP
#include "Sensor.hpp"

class Analogdevices : Sensor
{
public: 
    Analogdevices();
    ~Analogdevices(); 

    void init()
    Data read(Data data); 
    Data poll(Data data);
    void enable();
    void disable();
    float calculate_temperature(); 
    float calculate_intensity(); 
    #define THERMISTOR_T0 298.15 
    #define THERMISTOR_BETA 3380.0
    #define ANALOG_MAX 1023


private:
    float temperature; 
    float intensity; 
    bool enabled;

};


#endif