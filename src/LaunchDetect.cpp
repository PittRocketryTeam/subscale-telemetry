#include "LaunchDetect.hpp"

/* PUT YOUR CODE HERE */
void LaunchDetect::daniel(Data data)
{
    // wait for statisticaly significant sample size
    if (daniel_dataCount > 100)
    {
        daniel_updateAccelStat(data);
        daniel_updateAltStat(data);

        bool altDetect = (daniel_altCUSUM > daniel_altThresh);
        bool accelDetect = (daniel_accelCUSUM > daniel_accelThresh);

        launchDetect[DANIEL] = (altDetect && accelDetect);
    }
    else
    {
        daniel_updateAccelStat(data);
        daniel_updateAltStat(data);
        ++daniel_dataCount;
    }   
    
}

void LaunchDetect::daniel_updateAccelStat(Data data)
{
    //TODO update to prevent division by zero
    float newMean = daniel_meanAccel + (data.imuData.acceleration_z - daniel_meanAccel) / daniel_dataCount;
    daniel_varAccel += (data.imuData.acceleration_z - daniel_meanAccel) * (data.imuData.acceleration_z - newMean);
    daniel_meanAccel = newMean;
    daniel_stdAccel = sqrt(daniel_varAccel);

    daniel_accelMag = daniel_magMult * daniel_stdAccel;
    daniel_accelThresh = daniel_thresMult * daniel_stdAccel;

    float temp = daniel_accelCUSUM + (data.imuData.acceleration_z - daniel_meanAccel - daniel_accelMag);
    if (0 > temp)
    {
        daniel_accelCUSUM = 0;
    }
    else
    {
        daniel_accelCUSUM = temp;
    }
    
}

void LaunchDetect::daniel_updateAltStat(Data data)
{
    //TODO update to prevent division by zero
    float newMean = daniel_meanAlt + (data.altimeterData.altitude - daniel_meanAlt) / daniel_dataCount;
    daniel_varAlt += (data.altimeterData.altitude - daniel_meanAccel) * (data.altimeterData.altitude - newMean);
    daniel_meanAlt = newMean;
    daniel_stdAlt = sqrt(daniel_varAlt);

    float temp = daniel_altCUSUM + (data.altimeterData.altitude - daniel_meanAlt - daniel_altMag);
    if (0 > temp)
    {
        daniel_altCUSUM = 0;
    }
    else
    {
        daniel_altCUSUM = temp;
    }
}



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
    if (!launchDetect[DANIEL]) daniel(data);

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