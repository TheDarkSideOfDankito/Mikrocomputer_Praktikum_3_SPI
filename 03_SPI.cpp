
// Pin Setup:
// MOSI (Arduino 11) -> D_IN
// MISO (Arduino 12) -> D_OUT
// SCK (Arduino 13) -> CLK
// SS (Arduino 10) -> CS/SHDN

// First Temperature Sensor is connect to Channel 0 (Pin 1 of MCP3208)
// Second Temperature Sensor is connect to Channel 1 (Pin 2 of MCP3208)
// But this can be changed by preprocessor definitions FIRST_SENSOR_CHANNEL and SECOND_SENSOR_CHANNEL



#include "SPI.h"
#include "Arduino.h"


#define FIRST_SENSOR_CHANNEL 0 // a value from 0 to 7
#define SECOND_SENSOR_CHANNEL 1 // dito

#define DELAY_BETWEEN_TWO_READS_MS 500


void doSetup();

void doLoop();


int main() {
    doSetup();

    while(1) {
        doLoop();
    }
}


void doSetup() {
    init();
    Serial.begin(9600);

    initSPI();
}

void doLoop() {
    uint16_t firstSensorValue = receiveValueOfChannel(FIRST_SENSOR_CHANNEL);

    uint16_t secondSensorValue = receiveValueOfChannel(SECOND_SENSOR_CHANNEL);

    Serial.println();
    Serial.print("1st Sensor: ");
    Serial.println(firstSensorValue, 10);
    Serial.print("2nd Sensor: ");
    Serial.println(secondSensorValue, 10);

    _delay_ms(DELAY_BETWEEN_TWO_READS_MS);
}