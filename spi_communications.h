#ifndef SPI_COMMUNICATIONS_H
#define SPI_COMMUNICATIONS_H

#include <Arduino.h>
#include <SPI.h>

#define SPI_SPEED 20000000

#define SPI2_MOSI_PIN PB15
#define SPI2_MISO_PIN PC2
#define SPI2_SCK_PIN PB13
#define SPI2_CS_PIN PB9

void spiSetup();
void writeRegister(uint8_t address, uint16_t value);
uint16_t readRegister(uint8_t address);


#endif // SPI_COMMUNICATIONS_H