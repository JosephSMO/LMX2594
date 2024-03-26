#ifndef TABLES_H
#define TABLES_H

#include <Arduino.h>
#include <stdint.h>
#include <limits.h>

// Bootup register struct
typedef struct {
  uint8_t registerAddr;
  uint16_t value;
} RegisterMap;

// Channel divider table
typedef struct {
    int division;
    float outMin;
    float outMax;
    int chdiv;
    int seg0;
    int seg1;
    int seg2;
    int seg3;
    int limitation;
} ChannelDividerTable;

typedef struct {
    int mashOrder;
    float fVCOMin;
    float fVCOMax;
    int minimumN;
    int pfdDlySel;
} MinimumNDividerRestrictionsTable;

extern const RegisterMap bootupRegisters[];
extern const ChannelDividerTable channelDivider[];
extern const MinimumNDividerRestrictionsTable nDivider[];
extern const int totalRegisters;

#endif // TABLES_H