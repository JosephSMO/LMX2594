#include "LMX2594_Interface.h"

static uint8_t Fpd;

static void getChannelDivisionValue(float out_freq, int* division, int* chdiv) {
    int i = 0;
    *division = -1; // Default values if no match is found
    *chdiv = -1;

    while (channelDivider[i].division != 0) {
        if (out_freq >= channelDivider[i].outMin && out_freq <= channelDivider[i].outMax) {
            *division = channelDivider[i].division;
            *chdiv = channelDivider[i].chdiv;
            return;
        }
        i++;
    }

    return;
}

static float get_Fvco(float out_freq, int divider) {
  return out_freq * divider;
}

static void approximate_fraction(float fractional_part, uint32_t max_denominator, uint32_t *best_d, uint32_t *best_e) {
    // Ensure fractional part is non-negative
    fractional_part = fabsf(fractional_part);

    if (fractional_part == 0.0f) {
        *best_d = 0;
        *best_e = 1;
        return;
    }

    int a;
    uint32_t d0 = 0, d1 = 1, d2;
    uint32_t e0 = 1, e1 = 0, e2;
    float x = fractional_part;

    while (e1 <= max_denominator) {
        a = (int)x; // Integer part of x
        // Check for potential overflow
        if ((UINT32_MAX - (uint32_t)a * d1) < d0 || (UINT32_MAX - (uint32_t)a * e1) < e0) {
            break;
        }
        d2 = d0 + (uint32_t)a * d1;
        e2 = e0 + (uint32_t)a * e1;

        if (e2 > max_denominator) {
            break;
        }

        // Update x
        x -= (float)a;
        if (x < 1e-6) { // Close enough to zero
            break;
        }
        x = 1.0f / x;

        // Update variables
        d0 = d1;
        d1 = d2;
        e0 = e1;
        e1 = e2;
    }

    // Convert best_d / best_e to a fraction with MAX_DEN as the denominator
    if (e1 != 0 && MAX_DEN != 0) {
        float scaling_factor = (float)MAX_DEN / e1;
        *best_d = (uint32_t)roundf(d1 * scaling_factor);
        *best_e = MAX_DEN;
    } else {
        *best_d = d1;
        *best_e = e1;
    }
}

void static getNDivider(float fvco, uint32_t *c, uint32_t *d, uint32_t *e) {
    *c = (int)(fvco / Fpd);
    float fractional_part = fvco / Fpd - *c;
    uint32_t max_denominator = 1000; // Adjust as needed
    approximate_fraction(fractional_part, max_denominator, d, e);
}

void static setMashOrderAndPfdDlySel(float fvco, int minimumN) {
    for (int i = 0; nDivider[i].pfdDlySel != 0; ++i) {
        if (minimumN >= nDivider[i].minimumN && fvco >= nDivider[i].fVCOMin && fvco <= nDivider[i].fVCOMax) {
            LMX2594_Driver::PLL::MASH_and_Phase_Synchronization::set_MASH_ORDER(nDivider[i].mashOrder);
            LMX2594_Driver::PLL::MASH_and_Phase_Synchronization::set_PFD_DLY_SEL(nDivider[i].pfdDlySel);
            return;
        }
    }
    Serial.println("No matching entry found in nDivider table");
}

void static get_FM_parameters(float freq, float bandwidth, uint32_t *upper_NUM, uint32_t *lower_NUM, uint32_t *upper_N, uint32_t *lower_N, int *upper_chdiv, int *lower_chdiv) {
    int chdiv, divider;
    uint32_t PLL_N, PLL_NUM, PLL_DEN;
    float fvco, upper_bound, lower_bound;

    upper_bound = freq + (bandwidth / 2);
    lower_bound = freq - (bandwidth / 2);

    getChannelDivisionValue(upper_bound, &divider, &chdiv);
    fvco = get_Fvco(upper_bound, divider);
    getNDivider(fvco, &PLL_N, &PLL_NUM, &PLL_DEN);
    *upper_N = PLL_N;
    *upper_NUM = PLL_NUM;
    *upper_chdiv = chdiv;

    getChannelDivisionValue(lower_bound, &divider, &chdiv);
    fvco = get_Fvco(lower_bound, divider);
    getNDivider(fvco, &PLL_N, &PLL_NUM, &PLL_DEN);
    *lower_N = PLL_N;
    *lower_NUM = PLL_NUM;
    *lower_chdiv = chdiv;
}

void LMX2594_Interface::set_Fpd(uint8_t option) {
    Serial.print("set_Fpd: ");
    switch(option) {
        case 50: // 50 MHz
            LMX2594_Driver::PLL::VCO_Calibration::set_FCAL_LPFD_ADJ(0);
            LMX2594_Driver::PLL::VCO_Calibration::set_FCAL_HPFD_ADJ(0);
            LMX2594_Driver::PLL::Signal_Generation::set_Doubler(true);
            LMX2594_Driver::PLL::Signal_Generation::set_PreR(1);
            LMX2594_Driver::PLL::Signal_Generation::set_Multiplier(1);
            LMX2594_Driver::PLL::Signal_Generation::set_R(4);
            Fpd = 50;
            Serial.println("Fpd set to 50 MHz");
            break;
        case 200: // 200 MHz
            LMX2594_Driver::PLL::VCO_Calibration::set_FCAL_LPFD_ADJ(0);
            LMX2594_Driver::PLL::VCO_Calibration::set_FCAL_HPFD_ADJ(2);
            LMX2594_Driver::PLL::Signal_Generation::set_Doubler(true);
            LMX2594_Driver::PLL::Signal_Generation::set_PreR(1);
            LMX2594_Driver::PLL::Signal_Generation::set_Multiplier(1);
            LMX2594_Driver::PLL::Signal_Generation::set_R(1);
            Fpd = 200;
            Serial.println("Fpd set to 200 MHz");
            break;
        default:
            Serial.println("Invalid option, select 50 MHz or 200 MHz");
            break;
    }
}

void LMX2594_Interface::set_carrier(float freq) {
    int chdiv, divider;
    uint32_t PLL_N, PLL_NUM, PLL_DEN;
    float fvco;

    getChannelDivisionValue(freq, &divider, &chdiv);
    fvco = get_Fvco(freq, divider);
    getNDivider(fvco, &PLL_N, &PLL_NUM, &PLL_DEN);

    setMashOrderAndPfdDlySel(fvco, PLL_N);
    LMX2594_Driver::PLL::Signal_Generation::set_Channel_Divider(chdiv);
    LMX2594_Driver::PLL::Signal_Generation::set_PLL_NUM(PLL_NUM);
    LMX2594_Driver::PLL::Signal_Generation::set_PLL_DEN(PLL_DEN);
    LMX2594_Driver::PLL::Signal_Generation::set_PLL_N(PLL_N);
    LMX2594_Driver::PLL::Signal_Generation::toggle_FCAL_EN();
    Serial.print("Setting frequency to: ");
    Serial.println(freq, 6);
}

void LMX2594_Interface::FM_Signal(float center_freq, float bandwidth, float stop_time) {
    int chdiv, divider;
    uint32_t PLL_N, PLL_NUM, PLL_DEN;
    float fvco;
    uint32_t upper_N, upper_NUM, lower_N, lower_NUM;
    int upper_chdiv, lower_chdiv;
    float bandwidth_kHz, bandwidth_SS_kHz, rand_freq;
    bandwidth_kHz = bandwidth / 1000;
    bandwidth_SS_kHz = bandwidth_kHz / 2;
    get_FM_parameters(center_freq, bandwidth_kHz, &upper_NUM, &lower_NUM, &upper_N, &lower_N, &upper_chdiv, &lower_chdiv);

    while(millis() < stop_time) {
        uint32_t randomNumber;
        float offset;

        if((upper_chdiv != lower_chdiv) || (upper_N != lower_N)) {  // roughly 200 micros
            randomNumber = random(32768);
            offset = (randomNumber / 32768.0) * (2 * bandwidth_SS_kHz) - bandwidth_SS_kHz;
            rand_freq = center_freq + offset;
            set_carrier(rand_freq);
        }
        else {                                                      // roughly 80 micros
            randomNumber = lower_NUM + random(upper_NUM - lower_NUM + 1);
            LMX2594_Driver::PLL::Signal_Generation::set_PLL_NUM(PLL_NUM);
            LMX2594_Driver::PLL::Signal_Generation::toggle_FCAL_EN();
            Serial.print("Updating frequency");
        }
    }
}


