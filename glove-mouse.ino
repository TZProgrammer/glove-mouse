/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Motion detection.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <MPU6050.h>

MPU6050 mpu;

float ShiftedAccX, ShiftedAccY, ShiftedAccZ;
float AccX = 0, AccY = 0, AccZ = 0;
float AccErrorX, AccErrorY, AccErrorZ;
float elapsedTime, currentTime, previousTime;
int c = 0;

void setup() 
{
  Serial.begin(115200);

  Serial.println("Initialize MPU6050");

  
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  
  mpu.setAccelPowerOnDelay(MPU6050_DELAY_3MS);

  mpu.setIntFreeFallEnabled(false);  
  mpu.setIntZeroMotionEnabled(false);
  mpu.setIntMotionEnabled(false);
  
  mpu.setDHPFMode(MPU6050_DHPF_5HZ);

  mpu.setMotionDetectionThreshold(2);
  mpu.setMotionDetectionDuration(5);

  mpu.setZeroMotionDetectionThreshold(4);
  mpu.setZeroMotionDetectionDuration(2);  

  calculate_IMU_error();
  mpu.setAccelOffsetX(0);
  mpu.setAccelOffsetY(0);
  mpu.setAccelOffsetZ(0);
  
  checkOffsets(); 
}

void checkOffsets()
{
  Serial.print(" * Accelerometer offsets:     ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ()); 
  
  Serial.println();
}

void loop()
{
  Vector rawAccel = mpu.readRawAccel();
  AccX = rawAccel.XAxis - AccErrorX;
  AccY = rawAccel.YAxis - AccErrorY;
  AccZ = rawAccel.ZAxis - AccErrorZ;

  
  Serial.print("AccErrorX: ");
  Serial.println(AccX);
  Serial.print("AccErrorY: ");
  Serial.println(AccY);
  Serial.print("AccErrorZ: ");
  Serial.println(AccZ);

  Serial.println();

  delay(50);
}
void calculate_IMU_error() {
  // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
  // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
  // Read accelerometer values 300 times
  
  AccErrorX = 0;
  AccErrorY = 0;
  AccErrorZ = 0;
  c = 0;
  while (c < 300) {
    Vector rawAccel = mpu.readRawAccel();
    ShiftedAccX = rawAccel.XAxis;
    ShiftedAccY = rawAccel.YAxis;
    ShiftedAccZ = rawAccel.ZAxis;
    // Sum all readings
    AccErrorX = AccErrorX + ShiftedAccX;
    AccErrorY = AccErrorY + ShiftedAccY;
    AccErrorZ = AccErrorZ + ShiftedAccZ;
    c++;
  }
  
  //Divide the sum by 300 to get the error value
  AccErrorX = AccErrorX / 300;
  AccErrorY = AccErrorY / 300;
  AccErrorZ = AccErrorZ / 300;
  c = 0;
  
  // Print the error values on the Serial Monitor
  Serial.print("AccErrorX: ");
  Serial.println(AccErrorX);
  Serial.print("AccErrorY: ");
  Serial.println(AccErrorY);
  Serial.print("AccErrorZ: ");
  Serial.println(AccErrorZ);
}
