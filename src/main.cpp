#include <Arduino.h>
#include "Data.hpp"
#include "Altimeter.hpp"
#include "IMU.hpp"
#include "Logger.hpp"
#include "Metro.h"

IMU gyro;
Altimeter alt;
Logger logger;

Data state;

Metro do_log;

void setup()
{
    do_log.setInterval(100);
    gyro.init();
    alt.init();
    logger.init();

    logger.addSensor(&gyro);
    logger.addSensor(&alt);
}

void loop()
{

    //gyro.poll(state);
    alt.poll(state);

    if (do_log.check())
    {
        logger.log();
        do_log.reset();
    }
}