#include <stdio.h>
#include "pico/stdlib.h"
#include <hal/joystick/joystick.h>

int main()
{
    stdio_init_all();

    JOYSTICK_CONFIG_t cfg = {
        .x.pin = 27,
        .y.pin = 26,
        .z = {.pin = 22, .direction = 0, .logic = 1, .mode = 1}
    };

    JOYSTICK_t* joystick = JOYSTICK_Init( cfg );

    while (true) 
    {
        JOYSTICK_Update( joystick );
        JOYSTICK_ShowValue( joystick );
        sleep_ms(1000);
    }
}