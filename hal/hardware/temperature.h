#ifndef _HAL_TEMPERATURE_H
#define _HAL_TEMPERATURE_H

#include <stdint.h>

typedef struct
{
    float value;
}TEMPERATURE_t;

typedef struct
{
}TEMPERATURE_CONFIG_t;

TEMPERATURE_t* TEMPERATURE_Init( TEMPERATURE_CONFIG_t );

void TEMPERATURE_Update( TEMPERATURE_t* );

float TEMPERATURE_GetValue( TEMPERATURE_t* );

#endif