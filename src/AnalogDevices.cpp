#include "Analogdevices.hpp"

Analogdevices::Analogdevices()
{
    enabled = true;
    temperature = 0;
    intensity = 0;
}

Analogdevices::~Analogdevices()
{

}


Data Analogdevices::read(Data data)
{
    if (!enabled)
    {
        return data;
    }

    data.HealthData.main_battery_temperature = temperature; 
    data.PhotocellData.brightness = intensity;

    return data;
}

Data Analogdevices::poll(Data data)
{
    int Photocell_raw = analogRead(PHOTOCELL_PIN); 
    int Thermistor_raw = analogRead(THERMISTOR_PIN); 
    temperature = calculate_temperature(Thermistor_raw, THERMISTOR_BETA);
    intensity = calculate_intensity(Photocell_raw, );

}

Data Analogdevices::void enable()
{

}

Data Analogdevices::void disable()
{

}

Data Analogdevices::void init()
{
    pinMode(PHOTOCELL_PIN, INPUT); 
    pinMode(THERMISTOR_PIN, INPUT);
}


float Analogdevices::calculate_temperature(int raw, float beta) 
{
    float k = 1.0 / ((1.0 / THERMISTOR_T0) + (1.0 / beta) * (log((float)ANALOG_MAX / (float)raw) - 1.0));
    return k - 273.15;
}

float Analogdevices::calculate_intensity() 
{

}
