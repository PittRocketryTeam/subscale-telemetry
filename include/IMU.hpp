#ifndef __IMU_HPP__
#define __IMU_HPP__

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Data.hpp"
#include "Sensor.hpp"

#define IMU_DIMENIONS 3

class IMU : public Sensor
{
    private:
        Adafruit_BNO055 sensor;
        sensors_event_t event;

    public:

        IMU();
        ~IMU();

        bool init();
        Data read(Data);
        //Data read_raw(Adafruit_BNO055::adafruit_vector_type_t);
        Data poll(Data);

        void enable();
        void disable();
};

#endif
// __IMU_HPP__
