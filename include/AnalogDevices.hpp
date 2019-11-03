#ifndef ANALOGDEVICES_HPP
#define ANALOGDEVICES_HPP

#include "Sensor.hpp"
#include "Data.hpp"

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
    #define THERMISTOR_T0 298.15 
    #define THERMISTOR_BETA 3380.0
    #define ANALOG_MAX 1023


private:
    float calculate_temperature(int, float); 
    float calculate_intensity(int); 
    
    float temperature; 
    float intensity; 
    bool enabled;

};


#endif