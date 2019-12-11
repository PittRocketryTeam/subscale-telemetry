#include <Arduino.h>
#include "Data.hpp"
#include "Altimeter.hpp"
#include "IMU.hpp"
#include "Logger.hpp"
#include "Metro.h"
#include "AnalogDevices.hpp"
//#include "LaunchDetect.hpp"

//#define NO_CATCHUP

IMU gyro(true);
Altimeter alt;
Logger logger;
AnalogDevices ad;
//LaunchDetect launchDetect;

Data state;

Metro log_flush;

int mode;
int lastmode;
int swtch = 0;

void ready();
void armed();

void setup()
{
    pinMode(13, OUTPUT);
    pinMode(ENABLE, INPUT_PULLUP);

    digitalWrite(13, HIGH);

    //delay(1000);

    Serial.begin(9600);
    delay(1000);

    log_flush.setInterval(5000);

    gyro.init();
    alt.init();
    alt.setBaselinePressure();
    logger.init();
    ad.init();
    //launchDetect.init();

    logger.addSensor(&gyro);
    logger.addSensor(&alt);
    logger.addSensor(&ad);
    //logger.addSensor(&launchDetect);

    digitalWrite(13, LOW);
}

void loop()
{
    lastmode = mode;
    mode = digitalRead(ENABLE);

    if (lastmode != mode)
    {
        digitalWrite(13, 1);
        delay(100);
        digitalWrite(13, 0);
        delay(100);
        swtch = 1;
    }

    if (mode == 0)
    {
        ready();
    }
    else if (mode == 1)
    {
        //Serial.println("armed");
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
        swtch = 0;
    }

    state = gyro.poll(state);
    state = alt.poll(state);
    state = ad.poll(state);

    logger.log();
}
