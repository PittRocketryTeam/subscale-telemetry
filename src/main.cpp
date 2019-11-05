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

Metro log_flush;

int mode;
int lastmode;
int swtch = 0;
void ready();
void armed();
int led = 0;

void setup()
{
    Serial.begin(9600);
    delay(1000);

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
    led = mode;

    if (lastmode != mode)
    {
        digitalWrite(13, 1);
        delay(100);
        digitalWrite(13, 0);
        delay(100);
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
        digitalWrite(13, 1);
        logger.flush();
        digitalWrite(13, 0);
    }
}

void ready()
{
    if (swtch)
    {
        //logger.close();
        swtch = 0;
    }
}

void armed()
{
    if (swtch)
    {
        digitalWrite(13, 1);
        delay(100);
        digitalWrite(13, 0);
        delay(100);
        digitalWrite(13, 1);
        delay(100);
        digitalWrite(13, 0);
        delay(100);
        digitalWrite(13, 1);
        delay(100);
        digitalWrite(13, 0);
        delay(100);
        //logger.reopen();
        swtch = 0;
    }
    state = gyro.poll(state);
    state = alt.poll(state);
    state = ad.poll(state);

    logger.log();
}
