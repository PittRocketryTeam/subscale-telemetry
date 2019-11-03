#include "AnalogDevices.hpp"
#include "board.hpp"

AnalogDevices::AnalogDevices()
{

}

AnalogDevices::~AnalogDevices()
{

}


Data AnalogDevices::read(Data data)
{
    if (!enabled)
    {
        return data
    }

    data.healthData.main_battery_temperature = temperature; 
    data.photocellData.brightness = intensity;

    return data;
}

Data AnalogDevices::poll(Data data)
{
    int Photocell_raw = analogRead(PHOTOCELL_PIN); 
    int Thermistor_raw = analogRead(THERMISTOR_PIN); 
    temperature = calculate_temperature(Thermistor_raw, THERMISTOR_BETA);
    intensity = calculate_intensity(Photocell_raw, );

}

Data AnalogDevices::void enable()
{

}

Data AnalogDevices::void disable()
{

}

Data AnalogDevices::void init()
{
    pinMode(PHOTOCELL_PIN, INPUT); 
    pinMode(THERMISTOR_PIN, INPUT);
}


float AnalogDevices::calculate_temperature(int raw, float beta) 
{
    float k = 1.0 / ((1.0 / THERMISTOR_T0) + (1.0 / beta) * (log((float)ANALOG_MAX / (float)raw) - 1.0));
    return k - 273.15;
}

float AnalogDevices::calculate_intensity() 
{

}
