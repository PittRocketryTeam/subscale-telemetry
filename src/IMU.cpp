#include "IMU.hpp"

#include "board.hpp"

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

    int i;
    for (i = 0; i < 10; ++i)
    {
        if (sensor.begin())
        {
            break;
        }
        if (VERBOSE)
        {
            Serial.println("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        }
        delay(100);
    }

    sensor.setExtCrystalUse(true);

    if (VERBOSE)
    {
        Serial.println("BNO055 Initialized successfully!");
    }

    return false;
}

Data IMU::read(Data data)
{
    /*std::vector<float> ret(IMU_DIMENIONS, 0);

    sensors_event_t event;
    sensor.getEvent(&event);

    ret[0] = event.orientation.x;
    ret[1] = event.orientation.y;
    ret[2] = event.orientation.z;

    *poll_vector_ptr = ret;

    return ret;*/

    data.imuData.euler_abs_orientation_x = event.orientation.x;
    data.imuData.euler_abs_orientation_y = event.orientation.y;
    data.imuData.euler_abs_orientation_z = event.orientation.z;

    return data;
}

Data IMU::poll(Data data)
{
    sensor.getEvent(&event);

    data.imuData.euler_abs_orientation_x = event.orientation.x;
    data.imuData.euler_abs_orientation_y = event.orientation.y;
    data.imuData.euler_abs_orientation_z = event.orientation.z;
    
    return *last_data;
}

void IMU::enable()
{
    if (VERBOSE)
    {
        Serial.println("IMU Enabled");
    }

    sensor.enterNormalMode();
}

void IMU::disable()
{
    if (VERBOSE)
    {
        Serial.println("IMU Disabled");
    }

    sensor.enterSuspendMode();
}
