#include "IMU.hpp"

IMU::IMU(bool v = false)
{
    sensor = Adafruit_BNO055(55, I2C_ADDR);
    verbose = v;
    last_data = new Data;
}

IMU::~IMU()
{
    delete last_data;
}

bool IMU::init()
{

    while(!sensor.begin())
    {
        if (verbose)
        {
            Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        }
        delay(100);
    }

    sensor.setExtCrystalUse(true);

    if (verbose)
    {
        Serial.println("BNO055 Initialized successfully!");
    }

    return false;
}

Data IMU::read(Data d)
{

    sensors_event_t event;
    sensor.getEvent(&event);

    d.imuData.euler_abs_orientation_x = event.orientation.x;
    d.imuData.euler_abs_orientation_y = event.orientation.y;
    d.imuData.euler_abs_orientation_z = event.orientation.z;

    *last_data = d;

    return *last_data;
}

// Data IMU::read_raw()
// {
//     std::vector<float> ret(IMU_DIMENIONS, 0);
//
//     imu::Vector<3> v = sensor.getVector(t);
//
//     ret[0] = v[0];
//     ret[1] = v[1];
//     ret[2] = v[2];
//
//     return ret;
// }

Data IMU::poll(Data d)
{
    d.imuData.euler_abs_orientation_x = last_data->imuData.euler_abs_orientation_x;
    d.imuData.euler_abs_orientation_y = last_data->imuData.euler_abs_orientation_y;
    d.imuData.euler_abs_orientation_y = last_data->imuData.euler_abs_orientation_y;

    return d;
}

void IMU::enable()
{
    if (verbose)
        Serial.println("IMU Enabled");

    sensor.enterNormalMode();
}

void IMU::disable()
{
    if (verbose)
        Serial.println("IMU Disabled");

    sensor.enterSuspendMode();
}
