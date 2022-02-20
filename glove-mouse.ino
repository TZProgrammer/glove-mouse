#include <MPU6050.h>

MPU6050 mpu;

float ShiftedAccX, ShiftedAccY, ShiftedAccZ;
float AccX = 0, AccY = 0, AccZ = 0, totalAcceleration = 0;
float AccErrorX, AccErrorY, AccErrorZ;
float currentTime, previousTime;
int elapsedTime = 0, i = 0;

const int indexButtonPin = A1;
const int middleButtonPin = A2;
  
int indexButtonState = 0;
int middleButtonState = 0;

int c = 0;

void setup() 
{
  Serial.begin(115200);

  pinMode(indexButtonPin, OUTPUT);
  pinMode(middleButtonPin, OUTPUT);

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_16G))
  {
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
}


void loop()
{
  Vector rawAccel = mpu.readRawAccel();
  totalAcceleration = (rawAccel.XAxis - AccErrorX)*(rawAccel.XAxis - AccErrorX)+(rawAccel.YAxis - AccErrorY)*(rawAccel.YAxis - AccErrorY);
  if(totalAcceleration < 1000 || totalAcceleration > 200000){
    calculate_IMU_error();
    totalAcceleration = 2000;
  }
  
  if(Serial.available() > 0){

    delay(10);
    i=0;
    serialFlush();
    
    indexButtonState = digitalRead(indexButtonPin);
    middleButtonState = digitalRead(middleButtonPin);
  
    AccX = rawAccel.XAxis - AccErrorX;
    AccY = rawAccel.YAxis - AccErrorY;
    AccZ = rawAccel.ZAxis - AccErrorZ;
    

    Serial.print(AccX);
    Serial.print(" ");
    Serial.print(AccY);
    Serial.print(" ");
    Serial.print(AccZ);
    Serial.print(" ");
    Serial.print(indexButtonState);
    Serial.print(" ");
    Serial.print(middleButtonState);
    Serial.print(" ");
    Serial.print(totalAcceleration);
    Serial.print('\n');
    Serial.flush();
  }

  delay(20);
}
void calculate_IMU_error() {
  // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
  // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
  // Read accelerometer values 300 times
  
  AccErrorX = 0;
  AccErrorY = 0;
  AccErrorZ = 0;
  c = 0;
  while (c < 50) {
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
  AccErrorX = AccErrorX / 50;
  AccErrorY = AccErrorY / 50;
  AccErrorZ = AccErrorZ / 50;
  c = 0;
}

void serialFlush(){
  while(Serial.available() != 0 && i <10) {
    Serial.println("aaa");
    char t = Serial.read();
    i++;
  }
}
