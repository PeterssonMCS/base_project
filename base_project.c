#include <stdio.h>
#include "pico/stdlib.h"
#include "hal/hardware/temperature.h"

int main() 
{
    stdio_init_all();
    
    TEMPERATURE_CONFIG_t cfg;

    TEMPERATURE_t* temp =  TEMPERATURE_Init( cfg );

    while (true) 
    {
        TEMPERATURE_Update( temp );
        printf("Internal Temperature: %.2f °C\n", TEMPERATURE_GetValue( temp ) );
        sleep_ms(1000);
    }

    return 0;
}