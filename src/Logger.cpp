#include "Logger.hpp"
#include "board.hpp"

Logger::Logger() {}

Logger::~Logger() {}

bool Logger::init()
{
    generateFilename(filename);  // Generate unique log filename
    Serial.print("filename = ");
    Serial.println(filename);
    return SD.begin(BUILTIN_SDCARD);    // Make sure SD card begins
}

void Logger::addSensor(Sensor* sensor)
{
    sensors->push_back(sensor);
}

void Logger::addSensors(Sensor** sens)
{
    
}

bool Logger::log()
{
    Serial.print("Logging data");
    Data data = readDataFromSensors();  // Read data from sensors              
    return writeToMemory(data);         // Write data to micro SD
}

void Logger::generateFilename(char filename[])
{
    // sprintf(filename, "%d_%d-%d-%d_%d-%d-%d.log", weekday(), month(), day(), year(), hour(), minute(), second());
    sprintf(filename, "loggylog.log");

}

Data Logger::readDataFromSensors()
{
    Data data;
    for (Sensor* s : sensors)
        data = s->read(data);   // Read data from sensors

    data.timestamp = now();     // Add timestamp
    return data;                        
}

bool Logger::writeToMemory(Data data)
{
    File microSD = SD.open(filename, FILE_WRITE); 

    if (!microSD) 
        return false;
        
    // TODO: Serialize data for logging

    for (uint64_t i = 0; i < sizeof(data); i++){
        Serial.print("writen to board: ");
        Serial.print(&data);
    }
        //Serial.print("writen to board: %c\n", &data);
    size_t bytes_written = microSD.write(&data, sizeof(data));     
    microSD.close();                                                        
        
    return (bytes_written == sizeof(data));   
}