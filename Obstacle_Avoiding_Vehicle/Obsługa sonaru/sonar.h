#ifndef sonar_h
#define sonar_h

#include "MKL46Z4.h"   /* Device header */

void SONAR_initialize(void);
uint32_t Distance_from_probes(void);
static uint32_t result = 0;


#endif
