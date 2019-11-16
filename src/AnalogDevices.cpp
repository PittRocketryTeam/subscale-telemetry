#include "AnalogDevices.hpp"
#include "board.hpp"

AnalogDevices::AnalogDevices()
{
    enabled = true;
    temperature = 0;
    intensity = 0;
}

AnalogDevices::~AnalogDevices()
{

}


Data AnalogDevices::read(Data data)
{
    if (!enabled)
    {
        return data;
    }

    data.healthData.main_battery_temperature = temperature; 
    data.photocellData.brightness = intensity;

    return data;
}

Data AnalogDevices::poll(Data data)
{
    int photocell_raw = analogRead(PHOTOCELL_PIN); 
    int thermistor_raw = analogRead(THERMISTOR_PIN); 
    //Serial.print(photocell_raw);
    //Serial.print(" ,");
    //Serial.println(thermistor_raw);
    //temperature = calculate_temperature(thermistor_raw, THERMISTOR_BETA);
    temperature = (float)thermistor_raw;
    intensity = calculate_intensity(photocell_raw);

    return read(data);    
}

void AnalogDevices::enable()
{
    enabled = true;
}

void AnalogDevices::disable()
{
    enabled = false;
}

bool AnalogDevices::init()
{
    pinMode(PHOTOCELL_PIN, INPUT); 
    pinMode(THERMISTOR_PIN, INPUT);

    return true;
}


float AnalogDevices::calculate_temperature(int raw, float beta) 
{
    float k = 1.0 / ((1.0 / THERMISTOR_T0) + (1.0 / beta) * (log((float)ANALOG_MAX / (float)raw) - 1.0));
    return k - 273.15;
}

float AnalogDevices::calculate_intensity(int raw) 
{
    return (float)raw;
}
