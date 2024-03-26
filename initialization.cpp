#include "initialization.h"

// Define the total number of registers

void initLMX2594() {
    // Initialize random number generator
    randomSeed(analogRead(0));

    // Initialize SPI
    spiSetup();

    // Reset registers to default values
    writeRegister(0x00, 0x0002);  
    writeRegister(0x00, 0x0000); 

    // Boot up initial register values for 100 MHz signal with output disabled and FCAL_EN disabled
    for (int i = 0; i < totalRegisters; i++) {
        writeRegister(bootupRegisters[i].registerAddr, bootupRegisters[i].value);
    }

    // Toggle FCAL_EN to lock VCO 
    LMX2594_Driver::PLL::Signal_Generation::toggle_FCAL_EN();

    Serial.println("Bootup Complete");
}

