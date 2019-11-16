#ifndef ANALOGDEVICES_HPP
#define ANALOGDEVICES_HPP

#include "Sensor.hpp"
#include "Data.hpp"
#include <Arduino.h>

class AnalogDevices : public Sensor
{
public: 
    AnalogDevices();
    ~AnalogDevices(); 

    bool init();
    Data read(Data data); 
    Data poll(Data data);
    void enable();
    void disable();
    #define THERMISTOR_T0 279.0 
    #define THERMISTOR_BETA 1350.0
    #define ANALOG_MAX 1023


private:
    float calculate_temperature(int, float); 
    float calculate_intensity(int); 
    
    float temperature; 
    float intensity; 
    bool enabled;

};


#endif