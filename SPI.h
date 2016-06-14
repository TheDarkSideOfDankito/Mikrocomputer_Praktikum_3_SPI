//
// Created by ganymed on 10/06/16.
//

#ifndef INC_SPI_H
#define INC_SPI_H

#include <avr/io.h>
#include <USBAPI.h>


void initSPI();

uint16_t receiveValueOfChannel(uint8_t channel);

void _selectSlave();
void _deselectSlave();


#endif //INC_SPI_H
