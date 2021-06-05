//#define DEBUG
#define JOYSTICK

#include <Wire.h>

#ifdef JOYSTICK
#include "Joystick.h"
#endif

#define I2C_ADDR    8

#define SENSOR_COUNT    14
#define BUTTON_COUNT    7

#define INTER0          0
#define INTER1          1
#define INTER2          2
#define INTER3          3
#define INTER4          4
#define INTER5          5
#define INTER6          6
#define HEATER          7
#define MIXTURE         8
#define THROTTLE        9
#define PITCH           10
#define ROLL            11
#define PROPELLER       12
#define TRIM_PITCH       13

#define I2C_ADDR    8

int sensors[SENSOR_COUNT] = {
  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 512, 512, 0, 0,
};

#ifdef JOYSTICK
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  BUTTON_COUNT + 1, 0,     // Button Count, Hat Switch Count
  true,  true,  true,      // X, Y, and Z Axis
  false, true,  false,     // no Rx, Ry, and no Rz
  false, true,             // no rudder but throttle
  true,  true,  false);    // accelerator, brake, but no steering
#endif

#ifdef DEBUG
int i = 0;
#endif

void setup() {
  Wire.begin();        // join i2c bus (address optional for master)

#ifdef DEBUG
  Serial.begin(9600);  // start serial for output
#endif

#ifdef JOYSTICK
    // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(0, 1024);        // ROLL
  Joystick.setYAxisRange(0, 1260);        // PITCH
  Joystick.setRyAxisRange(0, 1024);       // TRIM_PITCH
  Joystick.setBrakeRange(0, 1024);        // HEATER
  Joystick.setZAxisRange(4, 960);        // MIXTURE
  Joystick.setThrottleRange(10, 980);     // THROTTLE
  Joystick.setRxAxisRange(12, 950);  // PROPELLER
#endif
}

void loop() {
  readSlave(I2C_ADDR, sensors, SENSOR_COUNT);

#ifdef DEBUG
  if (i++ >20) {
    i = 0;

    Serial.print("pitch: ");
    Serial.println(sensors[PITCH]);
    Serial.print("heater: ");
    Serial.println(sensors[HEATER]);
    Serial.print("mixture: ");
    Serial.println(sensors[MIXTURE]);
    Serial.print("throttle: ");
    Serial.println(sensors[THROTTLE]);
    Serial.print("propeller: ");
    Serial.println(sensors[PROPELLER]);
    Serial.print("roll: ");
    Serial.println(sensors[ROLL]);
    Serial.print("trim pitch: ");
    Serial.println(sensors[TRIM_PITCH]);
    Serial.print("inter0: ");
    Serial.println(sensors[INTER0]);
    Serial.print("inter1: ");
    Serial.println(sensors[INTER1]);
    Serial.print("inter2: ");
    Serial.println(sensors[INTER2]);
    Serial.print("inter3: ");
    Serial.println(sensors[INTER3]);
    Serial.print("inter4: ");
    Serial.println(sensors[INTER4]);
    Serial.print("inter5: ");
    Serial.println(sensors[INTER5]);
    Serial.print("inter6: ");
    Serial.println(sensors[INTER6]);
    Serial.println("------");
  }
#endif

#ifdef JOYSTICK
  //  Buttons
  for (int j=0; j<BUTTON_COUNT; j++) {
    if (sensors[j]) {
      Joystick.pressButton(j);
    } else {
      Joystick.releaseButton(j);
    }
  }
  if (sensors[HEATER]>50) {
    Joystick.pressButton(BUTTON_COUNT);
  } else {
    Joystick.releaseButton(BUTTON_COUNT);
  }

  Joystick.setXAxis(sensors[ROLL]);              // ROLL
  Joystick.setYAxis(sensors[PITCH]);             // PITCH
  Joystick.setRyAxis(sensors[TRIM_PITCH]);       // TRIM_PITCH
  Joystick.setBrake(sensors[HEATER]);            // HEATER
  Joystick.setZAxis(sensors[MIXTURE]);           // MIXTURE
  Joystick.setThrottle(sensors[THROTTLE]);       // THROTTLE
  Joystick.setRxAxis(sensors[PROPELLER]);   // PROPELLER
#endif

  delay(50);
}


void readSlave(int addr, int* sensors, int n) {
  char* data = (char*)sensors;
  
  Wire.requestFrom(addr, n*2);

  for(int index=0; index<n*2 && Wire.available(); index++) {
    data[index] = Wire.read();
  }
}
