#include <Wire.h>
#include "Servo.h"

int const COMMS_ADDR = 0x10;
int const CAL_ADDR = 0x20;
uint16_t force;
uint8_t FORCE_SENSOR = A0;
uint8_t SERVO_PIN = 10;

Servo calibration;

void setup()
{
  calibration.attach(SERVO_PIN);
  pinMode(FORCE_SENSOR, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.begin(115200);
  Wire.begin();
  Wire1.setSDA(2);
  Wire1.setSCL(3);
  Wire1.begin(CAL_ADDR);
  Wire1.onReceive(receiveEvent);
}

void receiveEvent(int numBytes)
{
  byte direction = Wire1.read();
  Serial.println("Received");
  if (direction == 2)
  {
    calibration.write(45);
    delay(1000);

    calibration.write(90);
  }
  else if (direction == 1)
  {
    calibration.write(135);
    delay(1000);

    calibration.write(90);
  }
  Serial.println(direction);
}

void loop()
{
  delay(50);
  force = analogRead(FORCE_SENSOR);

  // Split the 16-bit force value into two 8-bit values
  uint8_t msb = (force >> 8) & 0xFF;
  uint8_t lsb = force & 0xFF;

  Wire.beginTransmission(COMMS_ADDR);
  Wire.write(msb); // Send the most significant byte first
  Wire.write(lsb); // Send the least significant byte
  int result = Wire.endTransmission();

  // Debugging (if need be)

  if (result != 0)
  {
    Serial.print("Error in I2C transmission: ");
    Serial.println(result);
  }

  Serial.println(force);
}

// #include "Servo.h"
// #include <Wire.h>

// int const COMMS_ADDR = 0x10;
// int const CAL_ADDR = 0x20;
// uint16_t force;
// uint8_t FORCE_SENSOR = A0;
// const int REVOLUTION_STEPS = 200;
// uint16_t step = 200;
// uint8_t SERVO_PIN = 10;

// Servo calibration;

// void setup()
// {  
//   pinMode(SERVO_PIN, INPUT);
//   calibration.attach(SERVO_PIN);
//   pinMode(FORCE_SENSOR, INPUT);
//   pinMode(LED_BUILTIN, OUTPUT);
//   digitalWrite(LED_BUILTIN, HIGH);
//   Serial.begin(115200);
//   Wire.begin();
//   Wire1.setSDA(3);
//   Wire1.setSCL(2);
//   Wire1.begin(CAL_ADDR);
//   Wire1.onReceive(receiveEvent);
// }

// void receiveEvent(int numBytes)
// {
//   byte direction = Wire1.read();
//   Serial.println("Received");
//   if (direction == 2)
//   {
//     calibration.write(45);
//     delay(1000);

//     calibration.write(90);
//   }
//   else if (direction == 1)
//   {
//     calibration.write(135);
//     delay(1000);

//     calibration.write(90);
//   }
//   Serial.println(direction);
// }

// void loop()
// {
//   delay(50);
//   force = analogRead(FORCE_SENSOR);

//   // Split the 16-bit force value into two 8-bit values
//   uint8_t msb = (force >> 8) & 0xFF;
//   uint8_t lsb = force & 0xFF;

//   Wire.beginTransmission(COMMS_ADDR);
//   Wire.write(msb); // Send the most significant byte first
//   Wire.write(lsb); // Send the least significant byte
//   int result = Wire.endTransmission();

//   // Debugging (if need be)

//   if (result != 0)
//   {
//     Serial.print("Error in I2C transmission: ");
//     Serial.println(result);
//   }

//   Serial.println(force);
// }