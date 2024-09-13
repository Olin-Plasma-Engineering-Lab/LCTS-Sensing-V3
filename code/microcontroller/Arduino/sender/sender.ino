#include <Wire.h>
#include "Stepper.h"

int const COMMS_ADDR = 0x10;
int const CAL_ADDR = 0x20;
uint16_t force;
uint8_t FORCE_SENSOR = A0;
const int REVOLUTION_STEPS = 200;
uint16_t step = 200;

Stepper calibration(REVOLUTION_STEPS, 6, 7, 9, 8);

void setup()
{
  calibration.setSpeed(10);
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
    calibration.step(step);
  }
  else if (direction == 1)
  {
    calibration.step(-step);
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