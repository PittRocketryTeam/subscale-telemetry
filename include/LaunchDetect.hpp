#ifndef LAUNCHDETECT_HPP
#define LAUNCHDETECT_HPP

#include "Sensor.hpp"
#include "board.hpp"
#include <math.h>

/* ADD A DEFINE STATMENT WITH YOUR NAME AND A NUMBER 1 LARGER THAN THE PERSON BEFORE YOU */
#define PATRICK 0
#define DANIEL 1
// #define FIRSTNAME 1  

class LaunchDetect : public Sensor
{
public:
    LaunchDetect();
    ~LaunchDetect();
    
    bool init();
    Data poll(Data);
    Data read(Data);

    void enable();
    void disable();

    /* ADD YOUR FUNCTIONS HERE */
    void daniel(Data);

    // example
    void patrick(Data);

private:
    int launchDetect[PEOPLE];

    //daniel
    void daniel_updateAccelStat(Data data);
    void daniel_updateAltStat(Data data);
    float daniel_meanAccel, daniel_varAccel, daniel_stdAccel;
    float daniel_meanAlt, daniel_varAlt, daniel_stdAlt;
    float daniel_altCUSUM, daniel_accelCUSUM;
    int daniel_dataCount;
    float daniel_altMag, daniel_accelMag;
    float daniel_accelThresh, daniel_altThresh;
    const float daniel_magMult = .5;
    const float daniel_thresMult = 2;
};

#endif /* LAUNCHDETECT_HPP */