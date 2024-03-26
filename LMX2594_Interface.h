// LMX2594_Interface.h
#ifndef LMX2594_INTERFACE_H
#define LMX2594_INTERFACE_H

#include <Arduino.h>
#include <stdlib.h>
#include <math.h>
#include "LMX2594_Driver.h"
#include "tables.h"


class LMX2594_Interface {
public:
    static void set_Fpd(uint8_t option);
    static void set_carrier(float freq);
    static void FM_Signal(float freq, float bandwidth, float duration);
};

#endif // LMX2594_DRIVER_H