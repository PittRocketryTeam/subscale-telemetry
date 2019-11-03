#include "IMU.hpp"
#include "board.hpp"

IMU::IMU()
{
    sensor = Adafruit_BNO055(55, IMU_ADDR);
}

IMU::~IMU()
{
    
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

/*std::vector<float> IMU::read_raw(Adafruit_BNO055::adafruit_vector_type_t t)
{
    std::vector<float> ret(IMU_DIMENIONS, 0);

    imu::Vector<3> v = sensor.getVector(t);

    ret[0] = v[0];
    ret[1] = v[1];
    ret[2] = v[2];

    return ret;
}*/

Data IMU::poll(Data data)
{
    sensor.getEvent(&event);

    data.imuData.euler_abs_orientation_x = event.orientation.x;
    data.imuData.euler_abs_orientation_y = event.orientation.y;
    data.imuData.euler_abs_orientation_z = event.orientation.z;
    
    return data;
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