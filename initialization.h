#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#include <Arduino.h>
#include <stdint.h>
#include "tables.h" 
#include "spi_communications.h"
#include "LMX2594_Driver.h"

// Function prototype for initializing registers
void initLMX2594();

#endif // INITIALIZATION_H