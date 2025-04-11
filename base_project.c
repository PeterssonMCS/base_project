#include <stdio.h>
#include "pico/stdlib.h"
#include "hal_def.h"

int main()
{
    stdio_init_all();

    while (true) 
    {
        sleep_ms(1000);
    }
}
