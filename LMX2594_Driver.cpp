#include "LMX2594_Driver.h"


void LMX2594_Driver::PLL::VCO_Calibration::set_FCAL_LPFD_ADJ(uint8_t option) {
    uint8_t addr = 0x00;
    uint16_t r0 = readRegister(addr);
    Serial.print("set_FCAL_LPFD_ADJ: ");
    switch(option) {
        case 0: // Fpd >= 10 MHz
            r0 &= ~0x0060;
            r0 |= 0x0000;
            writeRegister(addr, r0);
            Serial.println("Fpd >= 10 MHz");
            break;
        case 1: // 10 MHz > Fpd >= 5 MHz
            r0 &= ~0x0060;
            r0 |= 0x0020;
            writeRegister(addr, r0);
            Serial.println("10 MHz > Fpd >= 5 MHz");
            break;
        case 2: // 5 MHz > Fpd >= 2.5 MHz
            r0 &= ~0x0060;
            r0 |= 0x0040;
            writeRegister(addr, r0);
            Serial.println("5 MHz > Fpd >= 2.5 MHz");
            break;
        case 3: // Fpd < 2.5 MHz
            r0 &= ~0x0060;
            r0 |= 0x0060;
            writeRegister(addr, r0);
            Serial.println("Fpd < 2.5 MHz");
            break;
        default:
            Serial.println("Invalid option");
            break;
    }
}

void LMX2594_Driver::PLL::VCO_Calibration::set_FCAL_HPFD_ADJ(uint8_t option) {
    uint8_t addr = 0x00;
    uint16_t r0 = readRegister(addr);
    Serial.print("set_FCAL_HPFD_ADJ: ");
    switch(option) {
        case 0: // Fpd <= 100 MHz
            r0 &= ~0x0180;
            r0 |= 0x0000;
            writeRegister(addr, r0);
            Serial.println("Fpd <= 100 MHz");
            break;
        case 1: // 100 MHz < Fpd <= 150 MHz
            r0 &= ~0x0180;
            r0 |= 0x0080;
            writeRegister(addr, r0);
            Serial.println("100 MHz < Fpd <= 150 MHz");
            break;
        case 2: // 150 MHz < Fpd <= 200 MHz
            r0 &= ~0x0180;
            r0 |= 0x0100;
            writeRegister(addr, r0);
            Serial.println("150 MHz < Fpd <= 200 MHz");
            break;
        case 3: // Fpd > 200 MHz
            r0 &= ~0x0180;
            r0 |= 0x0180;
            writeRegister(addr, r0);
            Serial.println("Fpd > 200 MHz");
            break;
        default:
            Serial.println("Invalid option");
            break;
    }
}

void LMX2594_Driver::PLL::VCO_Calibration::set_CAL_CLK_DIV(uint8_t option) {
    uint8_t addr = 0x01;
    uint16_t r1 = readRegister(addr);
    Serial.print("set_CAL_CLK_DIV: ");
    switch(option) {
        case 0: // Divide by 1. Use for Fosc <= 200 MHz
            r1 &= ~0x0003;
            r1 |= 0x0000;
            writeRegister(addr, r1);
            Serial.println("Divide by 1. Use for Fosc <= 200 MHz");
            break;
        case 1: // Divide by 2. Use for Fosc <= 400 MHz
            r1 &= ~0x0003;
            r1 |= 0x0001;
            writeRegister(addr, r1);
            Serial.println("Divide by 2. Use for Fosc <= 400 MHz");
            break;
        case 2: // Divide by 4. Use for Fosc <= 800 MHz
            r1 &= ~0x0003;
            r1 |= 0x0002;
            writeRegister(addr, r1);
            Serial.println("Divide by 4. Use for Fosc <= 800 MHz");
            break;
        case 3: // Divide by 8. All Fosc
            r1 &= ~0x0003;
            r1 |= 0x0003;
            writeRegister(addr, r1);
            Serial.println("Divide by 8. All Fosc");
            break;
        default:
            Serial.println("Invalid option");
            break;
    }
}

void LMX2594_Driver::PLL::VCO_Calibration::set_ACAL_CMP_DLY(uint8_t val) {    
    uint8_t addr = 0x04;
    uint16_t r4 = readRegister(addr);
    r4 &= ~0xFF00;
    r4 |= (val << 8);
    writeRegister(addr, r4);
    Serial.print("Set ACAL_CMP_DLY to: ");
    Serial.println(val);
}

void LMX2594_Driver::PLL::VCO_Assist::set_Start_VCO(uint8_t option) {
    uint8_t addr = 0x14;
    uint16_t r20 = readRegister(addr);
    Serial.print("set_Start_VCO: ");
    switch(option) {
        case 0: // Not used
            r20 &= ~0x0380;
            r20 |= 0x0000;
            writeRegister(addr, r20);
            Serial.println("Not used");
            break;
        case 1: // VCO1
            r20 &= ~0x0380;
            r20 |= 0x0080;
            writeRegister(addr, r20);
            Serial.println("VCO1");
            break;
        case 2: // VCO2
            r20 &= ~0x0380;
            r20 |= 0x0100;
            writeRegister(addr, r20);
            Serial.println("VCO2");
            break;
        case 3: // VCO3
            r20 &= ~0x0380;
            r20 |= 0x0180;
            writeRegister(addr, r20);
            Serial.println("VCO3");
            break;
        case 4: // VCO4
            r20 &= ~0x0380;
            r20 |= 0x0200;
            writeRegister(addr, r20);
            Serial.println("VCO4");
            break;
        case 5: // VCO5
            r20 &= ~0x0380;
            r20 |= 0x0280;
            writeRegister(addr, r20);
            Serial.println("VCO5");
            break;
        case 6: // VCO6
            r20 &= ~0x0380;
            r20 |= 0x0300;
            writeRegister(addr, r20);
            Serial.println("VCO6");
            break;
        case 7: // VCO7
            r20 &= ~0x0380;
            r20 |= 0x0380;
            writeRegister(addr, r20);
            Serial.println("VCO7");
            break;
        default:
            Serial.println("Invalid option");
            break;
    }
}

// Implementations for MASH_and_Phase_Synchronization methods in PLL
void LMX2594_Driver::PLL::MASH_and_Phase_Synchronization::set_PFD_DLY_SEL(uint8_t val) {
    if (val > 0x3F) {
        Serial.println("Error: Value exceeds 6-bit limit");
        return; 
    }

    uint8_t addr = 0x25;
    uint16_t r37 = readRegister(addr);
    r37 &= ~0x3F00;
    r37 |= (val << 8);
    writeRegister(addr, r37);
    Serial.print("Set set_PFD_DLY_SEL to: ");
    Serial.println(val);
}

void LMX2594_Driver::PLL::MASH_and_Phase_Synchronization::set_MASH_ORDER(uint8_t option) {
    uint8_t addr = 0x2C;
    uint16_t r44 = readRegister(addr);
    Serial.print("set_MASH_ORDER: ");
    switch(option) {
        case 0: // Integer mode
            r44 &= ~0x0007;
            r44 |= 0x0000;
            writeRegister(addr, r44);
            Serial.println("Integer mode");
            break;
        case 1: // First Order Modulator
            r44 &= ~0x0007;
            r44 |= 0x0001;
            writeRegister(addr, r44);
            Serial.println("First Order Modulator");
            break;
        case 2: // Second Order Modulator
            r44 &= ~0x0007;
            r44 |= 0x0002;
            writeRegister(addr, r44);
            Serial.println("Second Order Modulator");
            break;
        case 3: // Third Order Modulator
            r44 &= ~0x0007;
            r44 |= 0x0003;
            writeRegister(addr, r44);
            Serial.println("Third Order Modulator");
            break;
        case 4: // Fourth Order Modulator
            r44 &= ~0x0007;
            r44 |= 0x0004;
            writeRegister(addr, r44);
            Serial.println("Fourth Order Modulator");
            break;
        default:
            Serial.println("Invalid option");
            break;
    }
}

void LMX2594_Driver::PLL::MASH_and_Phase_Synchronization::toggle_MASH_RESET_N(bool enable) {
    uint8_t addr = 0x2C;
    uint16_t r44 = readRegister(addr);
    if(enable) { // Enable MASH RESET 
        r44 |= 0x0010;
        writeRegister(addr, r44);
        Serial.println("Enabled MASH RESET");
    }
    else {      // Disable MASH RESET 
        r44 &= ~0x0010;
        writeRegister(addr, r44);
        Serial.println("Disabled MASH RESET");
    }
}

void LMX2594_Driver::PLL::MASH_and_Phase_Synchronization::toggle_MASH_SEED_EN(bool enable) {
    uint8_t addr = 0x25;
    uint16_t r37 = readRegister(addr);
    if(enable) { // Enable MASH SEED
        r37 |= 0x8000;
        writeRegister(addr, r37);
        Serial.println("Enabled MASH SEED");
    }
    else {      // Disable MASH RESET 
        r37 &= ~0x8000;
        writeRegister(addr, r37);
        Serial.println("Disabled MASH RESET");
    }
}

uint32_t LMX2594_Driver::PLL::MASH_and_Phase_Synchronization::get_MASH_SEED() {
    uint8_t addrR40 = 0x28;
    uint8_t addrR41 = 0x29;

    uint16_t r40 = readRegister(addrR40);
    uint16_t r41 = readRegister(addrR41);

    uint32_t val = (r40 << 16) | r41;
    Serial.print("Read MASH SEED as: ");
    Serial.println(val);

    return val;
}

void LMX2594_Driver::PLL::MASH_and_Phase_Synchronization::set_MASH_SEED(uint32_t val) {
    uint8_t addrR40 = 0x28;
    uint8_t addrR41 = 0x29;

    uint16_t upper16 = (val >> 16) & 0xFFFF;
    uint16_t lower16 = val & 0xFFFF;

    writeRegister(addrR40, upper16);
    writeRegister(addrR41, lower16);
    Serial.print("Set MASH SEED to: ");
    Serial.println(val);
}

void LMX2594_Driver::PLL::MASH_and_Phase_Synchronization::toggle_VCO_PHASE_SYNC(bool enable) {
    uint8_t addr = 0x00;
    uint16_t r0 = readRegister(addr);
    if(enable) { // Enable VCO PHASE SYNC
        r0 |= 0x4000;
        writeRegister(addr, r0);
        Serial.println("Enabled VCO PHASE SYNC");
    }
    else {      // Disable VCO PHASE SYNC
        r0 &= ~0x4000;
        writeRegister(addr, r0);
        Serial.println("Disabled VCO PHASE SYNC");
    }
}

void LMX2594_Driver::PLL::Signal_Generation::set_Doubler(bool enable) {
    uint8_t addr = 0x09;
    uint16_t r9 = readRegister(addr);
    if(enable) { // Enable Doubler
        r9 |= 0x1000;
        writeRegister(addr, r9);
        Serial.println("Enabled Doubler");
    }
    else {      // Disable Doubler
        r9 &= ~0x1000;
        writeRegister(addr, r9);
        Serial.println("Disabled Doubler");
    }
}

void LMX2594_Driver::PLL::Signal_Generation::set_PreR(uint16_t val) {
    if (val > 0xFFF) {
        Serial.println("Error: Value exceeds 12-bit limit");
        return; 
    }

    uint8_t addr = 0x0C;
    uint16_t r12 = readRegister(addr);
    r12 &= ~0x0FFF;
    r12 |= val;
    writeRegister(addr, r12);
    Serial.print("Set PreR to: ");
    Serial.println(val);
}

void LMX2594_Driver::PLL::Signal_Generation::set_Multiplier(uint8_t option) {
    uint8_t addr = 0x0A;
    uint16_t r10 = readRegister(addr);
    Serial.print("set_Multiplier: ");
    switch(option) {
        case 1: // Bypass
            r10 &= ~0x0F80;
            r10 |= 0x0080;
            writeRegister(addr, r10);
            Serial.println("Integer mode");
            break;
        case 3: // 3X
            r10 &= ~0x0F80;
            r10 |= 0x0180;
            writeRegister(addr, r10);
            Serial.println("3X");
            break;
        case 4: // 4X
            r10 &= ~0x0F80;
            r10 |= 0x0200;
            writeRegister(addr, r10);
            Serial.println("4X");
            break;
        case 5: // 5X
            r10 &= ~0x0F80;
            r10 |= 0x0280;
            writeRegister(addr, r10);
            Serial.println("5X");
            break;
        case 6: // 6X
            r10 &= ~0x0F80;
            r10 |= 0x0300;
            writeRegister(addr, r10);
            Serial.println("6X");
            break;
        case 7: // 7X
            r10 &= ~0x0F80;
            r10 |= 0x0380;
            writeRegister(addr, r10);
            Serial.println("7X");
            break;
        default:
            Serial.println("Invalid option");
            break;
    }
}

void LMX2594_Driver::PLL::Signal_Generation::set_R(uint8_t val) {
    uint8_t addr = 0x0B;
    uint16_t r11 = readRegister(addr);
    r11 &= ~0x0FF0;
    r11 |= (val << 4);
    writeRegister(addr, r11);
    Serial.print("Set R to: ");
    Serial.println(val);
}

void LMX2594_Driver::PLL::Signal_Generation::set_Effective_Charge_Pump_Gain(uint8_t option) {
    uint8_t addr = 0x0E;
    uint16_t r14 = readRegister(addr);
    Serial.print("set_Effective_Charge_Pump_Gain: ");
    switch(option) {
        case 0: // 0 mA
            r14 &= ~0x0070;
            r14 |= 0x0000;
            writeRegister(addr, r14);
            Serial.println("0 mA");
            break;
        case 1: // 6 mA
            r14 &= ~0x0070;
            r14 |= 0x0010;
            writeRegister(addr, r14);
            Serial.println("6 mA");
            break;
        case 3: // 12 mA
            r14 &= ~0x0070;
            r14 |= 0x0030;
            writeRegister(addr, r14);
            Serial.println("12 mA");
            break;
        case 4: // 3 mA
            r14 &= ~0x0070;
            r14 |= 0x0040;
            writeRegister(addr, r14);
            Serial.println("3 mA");
            break;
        case 5: // 9 mA
            r14 &= ~0x0070;
            r14 |= 0x0050;
            writeRegister(addr, r14);
            Serial.println("9 mA");
            break;
        case 7: // 15 mA
            r14 &= ~0x0070;
            r14 |= 0x0070;
            writeRegister(addr, r14);
            Serial.println("15 mA");
            break;
        default:
            Serial.println("Invalid option");
            break;
    }
}

void LMX2594_Driver::PLL::Signal_Generation::set_PLL_NUM(uint32_t val) {
    uint8_t addrR42 = 0x2A; // top    [31:16]
    uint8_t addrR43 = 0x2B; // bottom [15:0]
    uint16_t upper16 = (val >> 16) & 0xFFFF;
    uint16_t lower16 = val & 0xFFFF;

    writeRegister(addrR42, upper16);
    writeRegister(addrR43, lower16);
    Serial.print("Set PLL NUM to: ");
    Serial.println(val);
}

void LMX2594_Driver::PLL::Signal_Generation::set_PLL_DEN(uint32_t val) {
    uint8_t addrR38 = 0x26; // top    [31:16]
    uint8_t addrR39 = 0x27; // bottom [15:0]
    uint16_t upper16 = (val >> 16) & 0xFFFF;
    uint16_t lower16 = val & 0xFFFF;

    writeRegister(addrR38, upper16);
    writeRegister(addrR39, lower16);
    Serial.print("Set PLL DEN to: ");
    Serial.println(val);
}

void LMX2594_Driver::PLL::Signal_Generation::set_PLL_N(uint32_t val) {
    if (val > 0x7FFFF) {
        Serial.println("Error: Value exceeds 19-bit limit");
        return;
    }

    uint8_t addrR34 = 0x22; 
    uint8_t addrR36 = 0x24; 
    uint16_t lower16 = val & 0xFFFF;      
    uint16_t upper3 = (val >> 16) & 0x07; 

    uint16_t r34 = readRegister(addrR34);
    r34 &= ~0x0007;    // Clear the bits [2:0] that correspond to [18:16] in PLL_N
    r34 |= upper3;     // Set the new value in R34
    
    writeRegister(addrR34, r34);
    writeRegister(addrR36, lower16);

    Serial.print("Set PLL_N to: ");
    Serial.println(val);
}

void LMX2594_Driver::PLL::Signal_Generation::toggle_FCAL_EN() {
    uint8_t addr = 0x00;
    uint16_t r0 = readRegister(addr);
    Serial.println("toggling FCAL_EN");
    r0 &= ~0x0008;
    writeRegister(addr, r0);
    delayMicroseconds(40);
    r0 |= 0x0008;
    writeRegister(addr, r0);
}

void LMX2594_Driver::PLL::Signal_Generation::set_Channel_Divider(uint8_t option) {
    uint8_t addr = 0x4B;
    uint16_t r75 = readRegister(addr);
    Serial.print("set_Channel_Divider: ");
    switch(option) {
        case 0: // 2
            r75 &= ~0x07C0;
            r75 |= 0x0000;
            writeRegister(addr, r75);
            Serial.println("2");
            break;
        case 1: // 4
            r75 &= ~0x07C0;
            r75 |= 0x0040;
            writeRegister(addr, r75);
            Serial.println("4");
            break;
        case 2: // 6
            r75 &= ~0x07C0;
            r75 |= 0x0080;
            writeRegister(addr, r75);
            Serial.println("6");
            break;
        case 3: // 8
            r75 &= ~0x07C0;
            r75 |= 0x00C0;
            writeRegister(addr, r75);
            Serial.println("8");
            break;
        case 4: // 12
            r75 &= ~0x07C0;
            r75 |= 0x0100;
            writeRegister(addr, r75);
            Serial.println("12");
            break;
        case 5: // 16
            r75 &= ~0x07C0;
            r75 |= 0x0140;
            writeRegister(addr, r75);
            Serial.println("16");
            break;
        case 6: // 24
            r75 &= ~0x07C0;
            r75 |= 0x0180;
            writeRegister(addr, r75);
            Serial.println("24");
            break;
        case 7: // 32
            r75 &= ~0x07C0;
            r75 |= 0x01C0;
            writeRegister(addr, r75);
            Serial.println("32");
            break;
        case 8: // 48
            r75 &= ~0x07C0;
            r75 |= 0x0200;
            writeRegister(addr, r75);
            Serial.println("48");
            break;
        case 9: // 64
            r75 &= ~0x07C0;
            r75 |= 0x0240;
            writeRegister(addr, r75);
            Serial.println("64");
            break;
        case 10: // 72
            r75 &= ~0x07C0;
            r75 |= 0x0280;
            writeRegister(addr, r75);
            Serial.println("72");
            break;
        case 11: // 96
            r75 &= ~0x07C0;
            r75 |= 0x02C0;
            writeRegister(addr, r75);
            Serial.println("96");
            break;
        case 12: // 128
            r75 &= ~0x07C0;
            r75 |= 0x0300;
            writeRegister(addr, r75);
            Serial.println("128");
            break;
        case 13: // 192
            r75 &= ~0x07C0;
            r75 |= 0x0340;
            writeRegister(addr, r75);
            Serial.println("192");
            break;
        case 14: // 256
            r75 &= ~0x07C0;
            r75 |= 0x0380;
            writeRegister(addr, r75);
            Serial.println("256");
            break;
        case 15: // 384
            r75 &= ~0x07C0;
            r75 |= 0x03C0;
            writeRegister(addr, r75);
            Serial.println("384");
            break;
        case 16: // 512
            r75 &= ~0x07C0;
            r75 |= 0x0400;
            writeRegister(addr, r75);
            Serial.println("512");
            break;
        case 17: // 768
            r75 &= ~0x07C0;
            r75 |= 0x0440;
            writeRegister(addr, r75);
            Serial.println("768");
            break;
        default:
            Serial.println("Invalid option");
            break;
    }

    if(option) {
        LMX2594_Driver::PLL::Signal_Generation::toggle_SEG1_EN(true);
    }
    else {
        LMX2594_Driver::PLL::Signal_Generation::toggle_SEG1_EN(false);
    }

}

void LMX2594_Driver::PLL::Signal_Generation::toggle_SEG1_EN(bool enable) {
    uint8_t addr = 0x1F;
    uint16_t r31 = readRegister(addr);
    if(enable) { // Enable driver buffer for CHDIV > 2
        r31 |= 0x4000;
        writeRegister(addr, r31);
        Serial.println("SEG1 enabled, use for CHDIV > 2");
    }
    else {      // Disable (use for CHDIV = 2)
        r31 &= ~0x4000;
        writeRegister(addr, r31);
        Serial.println("SEG1 disabled, use for CHDIV = 2");
    }
}

void LMX2594_Driver::PLL::Signal_Generation::set_OUTA_MUX(uint8_t option) {
    uint8_t addr = 0x2D;
    uint16_t r45 = readRegister(addr);
    Serial.print("set_OUTA_MUX: ");
    switch(option) {
        case 0: // Channel Divider
            r45 &= ~0x1800;
            r45 |= 0x0000;
            writeRegister(addr, r45);
            Serial.println("Channel Divider");
            break;
        case 1: // VCO
            r45 &= ~0x1800;
            r45 |= 0x0800;
            writeRegister(addr, r45);
            Serial.println("VCO");
            break;
        default:
            Serial.println("Invalid option");
            break;
    }
}

void LMX2594_Driver::PLL::Signal_Generation::set_OUTB_MUX(uint8_t option) {
    uint8_t addr = 0x2E;
    uint16_t r46 = readRegister(addr);
    Serial.print("set_OUTB_MUX: ");
    switch(option) {
        case 0: // Channel Divider
            r46 &= ~0x0003;
            r46 |= 0x0000;
            writeRegister(addr, r46);
            Serial.println("Channel Divider");
            break;
        case 1: // VCO
            r46 &= ~0x0003;
            r46 |= 0x0001;
            writeRegister(addr, r46);
            Serial.println("VCO");
            break;
        default:
            Serial.println("Invalid option");
            break;
    }
}

void LMX2594_Driver::PLL::Signal_Generation::set_OUTA_POWER(uint8_t val) {
    if (val > 0x3F) {
        Serial.println("Error: Value exceeds 6-bit limit");
        return; 
    }

    uint8_t addr = 0x2C;
    uint16_t r44 = readRegister(addr);
    r44 &= ~0x3F00;
    r44 |= (val << 8);
    writeRegister(addr, r44);
    Serial.print("Set set_OUTA_POWER to: ");
    Serial.println(val);
}

void LMX2594_Driver::PLL::Signal_Generation::set_OUTB_POWER(uint8_t val) {
    if (val > 0x3F) {
        Serial.println("Error: Value exceeds 6-bit limit");
        return; 
    }

    uint8_t addr = 0x2D;
    uint16_t r45 = readRegister(addr);
    r45 &= ~0x3F00;
    r45 |= (val << 8);
    writeRegister(addr, r45);
    Serial.print("Set set_OUTB_POWER to: ");
    Serial.println(val);
}

void LMX2594_Driver::PLL::Signal_Generation::toggle_OUTA_PD(bool enable) {
    uint8_t addr = 0x2C;
    uint16_t r44 = readRegister(addr);
    if(enable) { // Disabled port A
        r44 |= 0x0040;
        writeRegister(addr, r44);
        Serial.println("Disabled port A");
    }
    else {      // Enabled port A
        r44 &= ~0x0040;
        writeRegister(addr, r44);
        Serial.println("Enabled port A");
    }
}

void LMX2594_Driver::PLL::Signal_Generation::toggle_OUTB_PD(bool enable) {
    uint8_t addr = 0x2C;
    uint16_t r44 = readRegister(addr);
    if(enable) { // Disabled port B
        r44 |= 0x0080;
        writeRegister(addr, r44);
        Serial.println("Disabled port B");
    }
    else {      // Enabled port B
        r44 &= ~0x0080;
        writeRegister(addr, r44);
        Serial.println("Enabled port B");
    }
}

void LMX2594_Driver::CONTROLS::toggle_powerdown(bool enable) {
    uint8_t addr = 0x00;
    uint16_t r0 = readRegister(addr);
    if(enable) { // Powers down LMX2594
        r0 |= 0x0001;
        writeRegister(addr, r0);
        Serial.println("Powering down LMX2594");
    }
    else {      // Powers up LMX2594
        r0 &= ~0x0001;
        writeRegister(addr, r0);
        Serial.println("Powering up LMX2594");
    }
}

void LMX2594_Driver::CONTROLS::toggle_reset() {
    uint8_t addr = 0x00;
    uint16_t r0 = readRegister(addr);
    Serial.println("toggle_reset:");
    r0 |= 0x0002;
    writeRegister(addr, r0);
    r0 &= ~0x0002;
    writeRegister(addr, r0);
}

void LMX2594_Driver::CONTROLS::set_MUXOUT_LD(bool lockDetect) {
    uint8_t addr = 0x00;
    uint16_t r0 = readRegister(addr);
    if(lockDetect) { // Set MUXOUT to lock detect
        r0 |= 0x0003;
        writeRegister(addr, r0);
        Serial.println("Set MUXOUT to lock detect");
    }
    else {      // Set MUXOUT to readback
        r0 &= ~0x0003;
        writeRegister(addr, r0);
        Serial.println("Set MUXOUT to readback");
    }
}

void LMX2594_Driver::RAMP::set_RAMP_THRESH(uint64_t val) {
    if (val > 0x1FFFFFFFF) {
      Serial.println("Error: Value exceeds 32-bit limit");
    }

    uint16_t r78, r79, r80;
    uint8_t addr78, addr79, addr80;
    addr78 = 0x4E;
    addr79 = 0x4F;
    addr80 = 0x50;
    r79 = (val >> 16) & 0xFFFF; // Get bits [31:16]
    r80 = val & 0xFFFF;         // Get bits [15:0]
    r78 = readRegister(addr78);     // Read the current state of register R78

    // Set or clear the 11th bit of R78 based on bit 32 of val
    if (val & 0x100000000) {  // Check if bit 32 is set
        r78 |= (1 << 11);     // Set the 11th bit
    } else {
        r78 &= ~(1 << 11);    // Clear the 11th bit
    }

    writeRegister(addr80, r80);
    writeRegister(addr79, r79);
    writeRegister(addr78, r78);

    Serial.print("Set RAMP_THRESH to: ");
    Serial.println(val);
}

void LMX2594_Driver::RAMP::toggle_QUICK_RECAL_EN(bool enable) {
    uint8_t addr = 0x4E;
    uint16_t r78 = readRegister(addr);
    if(enable) { // Enable quick recalibration
        r78 |= 0x0200;
        writeRegister(addr, r78);
        Serial.println("Enabled quick recalibration");
    }
    else {      // Disable quick recalibration
        r78 &= ~0x0200;
        writeRegister(addr, r78);
        Serial.println("Disabled quick recalibration");
    }
}

void LMX2594_Driver::RAMP::set_VCO_CAPCTRL_STRT(uint8_t val) {
    uint8_t addr = 0x4E;
    uint16_t r78 = readRegister(addr);
    r78 &= ~0x00FE;
    r78 |= (val << 1);
    writeRegister(addr, r78);
    Serial.print("Set set_VCO_CAPCTRL_STRT to: ");
    Serial.println(val);
}





