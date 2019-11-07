#include "LaunchDetect.hpp"

/* PUT YOUR CODE HERE */

void LaunchDetect::patrick(Data data)
{
    /**
     * Some useful data points
     * 
     * ORIENTATION
     * data.imuData.euler_abs_orientation_x
     * data.imuData.euler_abs_orientation_y
     * data.imuData.euler_abs_orientation_z
     * 
     * LINEAR ACCELERATION (includes gravity)
     * data.imuData.acceleration_x
     * data.imuData.acceleration_y
     * data.imuData.acceleration_z
     * 
     * ALTITUDE
     * data.altimiterData.altitude
     * 
     * */
    launchDetect[PATRICK] = 0;
}

/* CALL YOUR FUNCTION HERE */

Data LaunchDetect::poll(Data data)
{
    if (!launchDetect[PATRICK]) patrick(data);

    /* DON'T EDIT PAST HERE */
    return read(data);
}

/* DON'T EDIT PAST HERE */

LaunchDetect::LaunchDetect()
{

}

LaunchDetect::~LaunchDetect()
{

}

bool LaunchDetect::init()
{
    memset(launchDetect, 0, PEOPLE * sizeof(int));
}

Data LaunchDetect::read(Data data)
{
    int i;
    for (i = 0; i < PEOPLE; i++)
    {
        data.launchDetect[i] = launchDetect[i];
    }

    return data;
}

void LaunchDetect::enable()
{

}

void LaunchDetect::disable()
{
    
}