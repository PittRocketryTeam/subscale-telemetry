#include <Arduino.h>
#include "Data.hpp"
#include "Altimeter.hpp"
#include "IMU.hpp"
#include "Logger.hpp"
#include "Metro.h"
#include "AnalogDevices.hpp"

//#define NO_CATCHUP

IMU gyro(true);
Altimeter alt;
Logger logger;
AnalogDevices ad;

Data state;

Metro log_write;
Metro log_flush;

int mode;
int lastmode;
int swtch = 0;
void ready();
void armed();


void setup()
{
    Serial.begin(9600);
    delay(1000);

    log_write.setInterval(250);
    log_flush.setInterval(5000);

    gyro.init();
    alt.init();
    alt.setBaselinePressure();
    logger.init();
    ad.init();

    logger.addSensor(&gyro);
    logger.addSensor(&alt);
    logger.addSensor(&ad);

    pinMode(13, OUTPUT);
    pinMode(33, INPUT_PULLUP);
}

void loop()
{
    lastmode = mode;
    mode = digitalRead(33);
    if (lastmode != mode)
    {
        swtch = 1;
    }

    if (mode == 1)
    {
        ready();
    }
    else if (mode == 0)
    {
        armed();
    }

    if (log_flush.check())
    {
        logger.flush();
    }
}

void ready()
{
    if (swtch)
    {
        //logger.close();
        swtch = 0;
    }

    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    delay(500);
}

void armed()
{
    if (swtch)
    {
        //logger.reopen();
        swtch = 0;
    }
    state = gyro.poll(state);
    state = alt.poll(state);
    state = ad.poll(state);

    if (log_write.check())
    {
        digitalWrite(13, HIGH);
        logger.log();
        digitalWrite(13, LOW);
    }
}
