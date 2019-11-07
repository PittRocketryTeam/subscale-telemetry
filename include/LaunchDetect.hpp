#ifndef LAUNCHDETECT_HPP
#define LAUNCHDETECT_HPP

#include "Sensor.hpp"
#include "board.hpp"

/* ADD A DEFINE STATMENT WITH YOUR NAME AND A NUMBER 1 LARGER THAN THE PERSON BEFORE YOU */
#define PATRICK 0
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

    // example
    void patrick(Data);

private:
    int launchDetect[PEOPLE];
};

#endif /* LAUNCHDETECT_HPP */