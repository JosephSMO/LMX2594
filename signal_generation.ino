#include "LMX2594_Driver.h"
#include "LMX2594_Interface.h"
#include "initialization.h"

void setup() {
    Serial.begin(9600);
    delay(1000);

    initLMX2594();
    delay(1000);
    LMX2594_Driver::PLL::Signal_Generation::toggle_OUTA_PD(false);

    LMX2594_Driver::PLL::Signal_Generation::set_OUTA_MUX(0);
    LMX2594_Interface::set_Fpd(200);
    LMX2594_Driver::PLL::VCO_Calibration::set_CAL_CLK_DIV(0);
    LMX2594_Interface::set_carrier(50);
    LMX2594_Interface::FM_Signal(50, 20, 10000 + millis());
    
}

void loop() {
    // Other loop code...
}

// 38
// 1717986944
// 4294967295