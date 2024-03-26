// LMX2594_Driver.h
#ifndef LMX2594_DRIVER_H
#define LMX2594_DRIVER_H

#include <Arduino.h>
#include "spi_communications.h"

#define FOSC 100
#define MAX_DEN 4294967295


class LMX2594_Driver {
public:
    class PLL {
    public:
        class VCO_Calibration {
        public:
            static void set_FCAL_LPFD_ADJ(uint8_t option);
            static void set_FCAL_HPFD_ADJ(uint8_t option);
            static void set_CAL_CLK_DIV(uint8_t option);
            static void set_ACAL_CMP_DLY(uint8_t val);
        };

        class VCO_Assist {
        public:
            static void set_Start_VCO(uint8_t option);
        };

        class MASH_and_Phase_Synchronization {
        public:
            static void set_PFD_DLY_SEL(uint8_t val);
            static void set_MASH_ORDER(uint8_t option);
            static void toggle_MASH_RESET_N(bool enable);
            static void toggle_MASH_SEED_EN(bool enable);
            static uint32_t get_MASH_SEED();
            static void set_MASH_SEED(uint32_t val);
            static void toggle_VCO_PHASE_SYNC(bool enable);
        };

        class Signal_Generation {
        public:
            static void set_Doubler(bool enable);
            static void set_PreR(uint16_t);
            static void set_Multiplier(uint8_t option);
            static void set_R(uint8_t val);
            static void set_Effective_Charge_Pump_Gain(uint8_t option);
            static void set_PLL_NUM(uint32_t val);
            static void set_PLL_DEN(uint32_t val);
            static void set_PLL_N(uint32_t val);
            static void toggle_FCAL_EN();
            static void set_Channel_Divider(uint8_t option);
            static void toggle_SEG1_EN(bool enable);
            static void set_OUTA_MUX(uint8_t option);
            static void set_OUTB_MUX(uint8_t option);
            static void set_OUTA_POWER(uint8_t val);
            static void set_OUTB_POWER(uint8_t val);
            static void toggle_OUTA_PD(bool enable);
            static void toggle_OUTB_PD(bool enable);
        };
    };

    class RAMP {
        static void set_RAMP_THRESH(uint64_t val);
        static void toggle_QUICK_RECAL_EN(bool enable);
        static void set_VCO_CAPCTRL_STRT(uint8_t val);
        static void set_RAMP_LIMIT_HIGH();
        static void set_RAMP_LIMIT_LOW();
        static void toggle_RAMP_BURST_EN();
        static void set_RAMP_BURST_COUNT();
        static void toggle_RAMP0_RST();
        static void set_RAMP_TRIGA();
        static void set_RAMP_TRIGB();
        static void set_RAMP_BURST_TRIG();
        static void set_RAMP0_INC();
        static void toggle_RAMP0_DLY();
        static void set_RAMP0_LEN();
        static void toggle_RAMP1_DLY();
        static void toggle_RAMP1_RST();
        static void toggle_RAMP0_NEXT();
        static void set_RAMP0_NEXT_TRIG();
        static void set_RAMP1_INC();
        static void set_RAMP1_LEN();
        static void set_RAMP_DLY_CNT();
        static void toggle_RAMP_MANUAL();
        static void toggle_RAMP1_NEXT();
        static void set_RAMP1_NEXT_TRIG();
        static void toggle_RAMP_TRIG_CAL();
        static void set_RAMP_SCALE_COUNT();
    };

    class CONTROLS {
    public:
        static void toggle_powerdown(bool enable);
        static void toggle_reset();
        static void set_MUXOUT_LD(bool lockDetect);
    };
};

#endif // LMX2594_DRIVER_H