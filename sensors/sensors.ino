#include <Arduino.h>
#include <Wire.h>



#define SENSOR_COUNT    14

#define PIN_INTER       2
#define PIN_DIR         10

#define PIN_INTER0      3
#define PIN_INTER1      4
#define PIN_INTER2      5
#define PIN_INTER3      6
#define PIN_INTER4      7
#define PIN_INTER5      8
#define PIN_INTER6      9

#define PIN_HEATER      A0
#define PIN_MIXTURE     A3
#define PIN_THROTTLE    A1
#define PIN_PROPELLER   A2
#define PIN_ROLL        A7
#define PIN_TRIM_PITCH  A6

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

int i = 0;


void counter() {
  if (digitalRead(PIN_DIR)) {
    sensors[PITCH]++;
  } else {
    sensors[PITCH]--;
  }
}

void requestEvent() {
  Wire.write((char*)sensors, SENSOR_COUNT*2);
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
  
  pinMode(PIN_INTER, INPUT_PULLUP);
  pinMode(PIN_DIR, INPUT);

  pinMode(PIN_INTER0, INPUT);
  pinMode(PIN_INTER1, INPUT);
  pinMode(PIN_INTER2, INPUT);
  pinMode(PIN_INTER3, INPUT);
  pinMode(PIN_INTER4, INPUT);
  pinMode(PIN_INTER5, INPUT);
  pinMode(PIN_INTER6, INPUT);

  attachInterrupt(digitalPinToInterrupt(PIN_INTER), counter, RISING);

  Wire.begin(I2C_ADDR);                // join i2c bus with address #8
  Wire.onRequest(requestEvent);    // register event
}



void loop() {
  delay(100);

  sensors[INTER0] = digitalRead(PIN_INTER0);
  sensors[INTER1] = digitalRead(PIN_INTER1);
  sensors[INTER2] = digitalRead(PIN_INTER2);
  sensors[INTER3] = digitalRead(PIN_INTER3);
  sensors[INTER4] = digitalRead(PIN_INTER4);
  sensors[INTER5] = digitalRead(PIN_INTER5);
  sensors[INTER6] = digitalRead(PIN_INTER6);

  sensors[HEATER] = analogRead(PIN_HEATER);
  sensors[MIXTURE] = analogRead(PIN_MIXTURE);
  sensors[THROTTLE] = analogRead(PIN_THROTTLE);
  sensors[PROPELLER] = analogRead(PIN_PROPELLER);
  sensors[ROLL] = analogRead(PIN_ROLL);
  sensors[TRIM_PITCH] = analogRead(PIN_TRIM_PITCH);

#ifdef DEBUG
  if (i++ > 15) { 
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
    Serial.println("");
  }
#endif
}
