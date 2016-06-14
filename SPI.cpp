//
// Created by ganymed on 10/06/16.
//

#include "SPI.h"



void initSPI() {
    // set SS, MOSI and SCK to output
    DDRB |= (1 << DDB2) | (1 << DDB3) | (1 << DDB5);

    _deselectSlave();

    // MCP3208 wants a Clock of 2 MHz -> set a Prescaler of 8
    SPCR |= (1 << SPR1) | (1 << SPR0);
    SPSR |= (1 << SPI2X);

    // MSB first
    SPCR &= ~(1 << DORD);

    // in idle state low
    SPCR &= ~(1 << CPOL);

    // transmit at rising edge
    SPCR &= ~(1 << CPHA);

    // Master Mode
    SPCR |= (1 << MSTR);

    // enable
    SPCR |= (1 << SPE);
}

void _selectSlave() {
    // inverted CS -> set PB2 to LOW to select slave
    PORTB &= ~(1 << PORTB2);
}

void _deselectSlave() {
    // set SS High (no Slave Selected)
    PORTB |= (1 << PORTB2);
}


uint8_t sendByte(uint16_t data) {
    SPDR = data;

    // Wait for transmission complete
    while(! (SPSR & (1 << SPIF)) );

    return SPDR; // return retrieved data
}


uint16_t receiveValueOfChannel(uint8_t channel) { // a channel from 0 - 7
    uint8_t firstByte = 0b00000110; // first 5 Bits should be zero; Start Bit = 1; SGL = 1; D2 = 0 or 1 depending on selected channel (see manual p. 19)
    uint8_t secondByte = 0b00111111; // D1; D0; the rest can be anything ("don't care"), i've just chosen 1; for D1 and D0 to select channel, see manual p.19
    uint8_t thirdByte = 0b11111111; // same here, don't care, is just needed to receive last byte on D_IN

    // set D2
    if(channel > 3) {
        firstByte += 1;
    }

    // set D1 and D0
    secondByte = (channel << 6) + secondByte; // D1 and D0 are most significant bits

    // now send bytes and received converted analog value on second and third byte
    _selectSlave();

    sendByte(firstByte);

    uint8_t highOrderByte = sendByte(secondByte);

    uint8_t lowOrderByte = sendByte(thirdByte);

    _deselectSlave();


    uint16_t result = highOrderByte & 0b00001111; // delete upper 4 Bits, they are 'don't care' bits

    result = (result << 8) | lowOrderByte;

    return result;
}
