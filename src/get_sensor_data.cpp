/*
Optical Heart Rate Detection (PBA Algorithm) using the MAX30105 Breakout
By: Nathan Seidle @ SparkFun Electronics
Date: October 2nd, 2016
https://github.com/sparkfun/MAX30105_Breakout

GSR example code adjusted to my needs basic example from
http://wiki.seeedstudio.com/Grove-GSR_Sensor/
*/

#include "get_sensor_data.h"
#include "MAX30105.h"
#include "heartRate.h"
#include "sensor.h"
#include <Wire.h>

const uint8_t amount_of_sensors = 3;
const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
long irValue;
uint16_t gsr_average;
float beatsPerMinute;
int avg_beat;

Sensor sensor_container[amount_of_sensors];
MAX30105 particleSensor;

//--------------------------------------- INIT MAX
void initMax() {
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    // while (1);
    // "Wtf does this empty while loop here?"~ Sjonnie.
	// "How did it even get here" ~ Me.
	// "Magic" ~ c++
  }

  Serial.println("Place your index finger on the sensor with steady pressure.");
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);
}

//--------------------------------------- GSR
uint16_t getGsrData() {
  const int GSR = A2;
  uint32_t sum = 0;
  uint16_t gsr_sensor_value;

  for (uint8_t i = 0; i < 10; i++) {
    gsr_sensor_value = analogRead(GSR);
    sum += gsr_sensor_value;
  }

  return gsr_average = map(sum * 0.1, 0, 4096, 0, 512);
}

//--------------------------------------- GET HR DATA
void getHeartRateData() {
  irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true) {
    long delta = millis() - lastBeat;
    lastBeat = millis();
    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20) {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE;
      avg_beat = 0;

      for (byte x = 0; x < RATE_SIZE; x++) {
        avg_beat += rates[x];
        avg_beat /= RATE_SIZE;
      }
    }
  }
}

uint16_t getIrSensorValue() {
	return (uint16_t)irValue;
}

uint16_t getBpm() {
	return (uint16_t)beatsPerMinute;
}

int getAvgBpm() {
	return avg_beat;
}

//--------------------------------------- DATA to CONTAINER
void sensor_to_container(uint8_t id, String name, uint16_t value_1, int value_2, uint16_t value_3) {

  if (value_1 != 0 || value_2 != 0 || value_3 != 0) {
    Sensor sensor;
    if (id == 2) {
		sensor = {id, name, value_1, value_2, value_3};
    }
	else if (id == 1) {
		sensor = {id, name, value_1, value_2};
    }
	else {
      sensor = {id, name, value_1};
    }
    sensor_container[id] = sensor;
    sensor_container[id].print(id);
  } 
  else {
    Serial.print("No valid sensor data.");
  }
}