#include "./inc/main.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

void readSensorConfig(Imu *srcImu)
{
  U8 reg;

  // cout << endl << "------------------------" << endl;
  cout << "Sensor config reading..." << endl;

  reg = srcImu->getRegisterValue(MPU6050_CONFIG);
  cout << "-CONFIG:" << endl;
  if(reg) {
    printf("Content :\t0x%2X\n", reg);
  } else {
    cout << "Something may have gone wrong or the register has not been setup yet ! :/" << endl;
    printf("Content:\t0x%2X\n", reg);
  }

  reg = srcImu->getRegisterValue(MPU6050_ACCEL_CONFIG);
  cout << "-ACCEL_CONFIG:" << endl;
  if(reg) {
    printf("Content :\t0x%2X\n", reg);
  } else {
    cout << "Something may have gone wrong or the register has not been setup yet ! :/" << endl;
    printf("Content:\t0x%2X\n", reg);
  }

  reg = srcImu->getRegisterValue(MPU6050_GYRO_CONFIG);
  cout << "-GYRO_CONFIG:" << endl;
  if(reg) {
    printf("Content :\t0x%2X\n", reg);
  } else {
    cout << "Something may have gone wrong or the register has not been setup yet ! :/" << endl;
    printf("Content:\t0x%2X\n", reg);
  }
}

void setSensorConfig(Imu *destImu)
{
  // cout << endl << "------------------------" << endl;
  cout << "Sensor config writing..." << endl;
  destImu->setRegisterValue(0x02,MPU6050_ACCEL_CONFIG);
}

int main(int argc, char const *argv[])
{
  int file;
  int adapter_nr = 1; /* probably dynamically determined */
  char filename[20];

  cout << "---------------- I2C Test ---------------" << endl;

  cout << "File opening..." << endl;
  
  snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
  file = open(filename, O_RDWR);
  if (file < 0) {
    perror("File opening failed. ");
    exit(1);
  }
  cout << "Yeeaaah ! It works ! :)" << endl;
  
  if(close(file)) {
    cout << "A problem occured while closing the file " << filename << endl;
    perror(NULL);
    exit(1);
  }

  cout << endl << "---------------- IMU Test ---------------" << endl;

  I2C myI2c(filename);
  Imu myImu1(0x68,&myI2c);
  Imu myImu2(0x69,&myI2c);

  cout << "IMU 1:" < endl;
  readSensorConfig(&myImu1);
  cout << "IMU 2:" < endl;
  readSensorConfig(&myImu2);
  // setSensorConfig(&myImu);
  // readSensorConfig(&myImu);


  cout << endl << "------------ Shutting program ------------" << endl;

  return 0;
}