#include <Wire.h>

int const COMMS_ADDR = 0x10;
int const CAL_ADDR = 0x20;
uint16_t sensor_out;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  Wire.begin(COMMS_ADDR);
  Wire.onReceive(receiveEvent);
  Wire1.setSDA(2);
  Wire1.setSCL(3);
  Wire1.begin(); 
}

void receiveEvent(int numBytes) {
  if (numBytes >= 2) {                // Ensure at least 2 bytes are available
    uint8_t msb = Wire.read();        // Most significant byte
    uint8_t lsb = Wire.read();        // Least significant byte
    sensor_out = (msb << 8) | lsb;    // Combine the two bytes into a uint16_t value
    Serial.print(millis());
    Serial.print(",");
    Serial.println(sensor_out);
  }
}


void loop() {
if (Serial.available()) {
      String data = Serial.readString();
      Serial.println(data);
      Wire1.beginTransmission(CAL_ADDR);
      if (data == "up\n") {
        Wire1.write(2);  // send value 2
        Serial.println("up sent");
      }
      if (data == "down\n") {
        Wire1.write(1);  // send value 1
        Serial.println("down sent");
      }
      int result = Wire1.endTransmission();  
      if (result != 0) {
        Serial.print("Error in I2C transmission: ");
        Serial.println(result);
      }
      }
}
  