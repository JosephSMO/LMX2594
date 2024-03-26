#include "spi_communications.h"

SPIClass SPI_2(SPI2_MOSI_PIN, SPI2_MISO_PIN, SPI2_SCK_PIN); // Create an SPI object for the second SPI port

void static debugWrite(uint32_t regValue) {
    // Extract the register number (first byte)
    uint8_t regNumber = (regValue >> 16) & 0xFF;
    // Extract the data (last two bytes)
    uint16_t data = regValue & 0xFFFF;

    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Wrote Register R%u as 0x%04X", regNumber, data);

    Serial.println(buffer);
}

void static debugRead(uint8_t address, uint16_t dataRead) {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Read from Register R%u: 0x%04X", address, dataRead);

    Serial.println(buffer);
}

void spiSetup() {
    pinMode(SPI2_CS_PIN, OUTPUT);
    digitalWrite(SPI2_CS_PIN, HIGH);

    SPI_2.beginTransaction(SPISettings(SPI_SPEED, MSBFIRST, SPI_MODE0));

    SPI_2.begin();
}

void writeRegister(uint8_t address, uint16_t value) {
    if (address > 0x7F) {  // Address is larger than 7 bits
        Serial.println("Error: Address exceeds 7 bits");
        return;
    }

    uint32_t regValue = ((uint32_t)address << 16) | value;

    digitalWrite(SPI2_CS_PIN, LOW);

    SPI_2.transfer((regValue >> 16) & 0xFF); // Most significant byte (MSB is 0 for write, followed by address)
    SPI_2.transfer((regValue >> 8) & 0xFF);  // Middle byte of the value
    SPI_2.transfer(regValue & 0xFF);         // Least significant byte of the value

    digitalWrite(SPI2_CS_PIN, HIGH);

    debugWrite(regValue);  // Call debug function to print the written value
}

uint16_t readRegister(uint8_t address) {
    if (address > 0x7F) {  // Address is larger than 7 bits
        Serial.println("Error: Address exceeds 7 bits");
        return 0;
    }

    uint32_t regValue = (1 << 23) | ((uint32_t)address << 16);  // Set MSB to 1 for read, followed by the 7-bit address

    digitalWrite(SPI2_CS_PIN, LOW);

    SPI_2.transfer((regValue >> 16) & 0xFF); // Most significant byte (includes R/W bit and address)
    uint8_t response1 = SPI_2.transfer(0x00); // Receive first byte
    uint8_t response2 = SPI_2.transfer(0x00); // Receive second byte

    digitalWrite(SPI2_CS_PIN, HIGH);

    uint16_t dataRead = ((uint16_t)response1 << 8) | response2;

    debugRead(address, dataRead);

    return dataRead;
}
