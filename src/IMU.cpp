#include "IMU.hpp"
#include "board.hpp"

IMU::IMU(bool v = false)
{
    sensor = Adafruit_BNO055(55, IMU_ADDR);
    verbose = v;
    ax = 0.0f;
    ay = 0.0f;
    az = 0.0f;
    ox = 0.0f;
    oy = 0.0f;
    oz = 0.0f;
    //last_data = new Data;
}

IMU::~IMU()
{
    //delete last_data;
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

    enable();

    return false;
}

Data IMU::read(Data data)
{
    data.imuData.euler_abs_orientation_x = ox;
    data.imuData.euler_abs_orientation_y = oy;
    data.imuData.euler_abs_orientation_z = oz;

    data.imuData.acceleration_x = ax;
    data.imuData.acceleration_y = ay;
    data.imuData.acceleration_z = az;

    return data;
}

Data IMU::poll(Data data)
{
    sensor.getEvent(&event);

    //ox = event.orientation.x;
    //oy = event.orientation.y;
    //oz = event.orientation.z;
    //ox = oy = oz = 69.0f;
    o = sensor.getVector(Adafruit_BNO055::VECTOR_EULER);
    ox = (float)o.x();
    oy = (float)o.y();
    oz = (float)o.z();

    a = sensor.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    ax = (float)a.x();
    ay = (float)a.y();
    az = (float)a.z();


    //ax = event.acceleration.x;
    //ay = event.acceleration.y;
    //az = event.acceleration.z;
    
    //last_data = data;

    return read(data);
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
