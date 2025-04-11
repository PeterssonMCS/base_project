#include "temperature.h"
#include <stdlib.h>
#include <hardware/adc.h>

TEMPERATURE_t* TEMPERATURE_Init( TEMPERATURE_CONFIG_t cfg )
{
    TEMPERATURE_t* temperature;

    temperature = (TEMPERATURE_t*)malloc( sizeof ( TEMPERATURE_t ) );
    
    assert( temperature != NULL );

    adc_init();
    adc_set_temp_sensor_enabled( true );
    adc_select_input( 4 );

    return temperature;
}

void TEMPERATURE_Update( TEMPERATURE_t* temperature )
{
    assert( temperature != NULL );
    uint16_t raw = adc_read();
    float voltage = raw * 3.3 / 4095.0;

    temperature->value = 27.0f - (voltage - 0.706f) / 0.001721f;
}

float TEMPERATURE_GetValue( TEMPERATURE_t* temperature )
{
    assert( temperature != NULL );
    return temperature->value;
}