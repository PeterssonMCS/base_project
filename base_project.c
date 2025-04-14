#include <stdio.h>
#include "pico/stdlib.h"
#include "hal/button/button.h"
#include "hal/hardware/timer/timer.h"
#include "hal/display/driver1306.h"

typedef enum
{
    PAUSED,
    RUNNING
}TIMER_STATE_t;

D1306_t* oled;
BUTTON_t* bt_rst;
BUTTON_t* bt_cnt;
TIMER_t* tmr_cnt;

int my_timer;
int my_counter;
TIMER_STATE_t my_timer_state = RUNNING;

void reset_timer()
{
    my_timer = 10;
}

void reset_counter()
{
    my_counter = 0;
}

bool periodic_callback( struct repeating_timer* timer )
{
    switch( my_timer_state )
    {
        case RUNNING:
            if( !(--my_timer) ) // If zero pause
            {
                my_timer_state = PAUSED;
            }
        break;
        case PAUSED: // Do nothing
        break;
    }
}

int main()
{
    stdio_init_all();

    BUTTON_CONFIG_t rst_cfg = {
        .gpio_cfg.pin = 5,
        .gpio_cfg.direction = 0,
        .gpio_cfg.logic = 1,
        .gpio_cfg.mode = 1,
    };

    BUTTON_CONFIG_t cnt_cfg = {
        .gpio_cfg.pin = 6,
        .gpio_cfg.direction = 0,
        .gpio_cfg.logic = 1,
        .gpio_cfg.mode = 1,
    };

    TIMER_CONFIG_t tmr_cfg = {
        .type = TIMER_PERIODIC,
        .timeout = 1000,
        .periodic_callback = periodic_callback,
        .alarm_callback = NULL
    };
    
    D1306_CONFIG_t oled_cfg = {
        .external_vcc = false,
        .width = 128,
        .height = 64,
        .i2c_cfg.address = 0x3C,
        .i2c_cfg.frequency = 400*1000,
        .i2c_cfg.i2c_id = 1,
        .i2c_cfg.pin_sda = 14,
        .i2c_cfg.pin_sdl = 15,
    };

    reset_timer();
    reset_counter();

    oled = D1306_Init( oled_cfg );
    bt_rst = BUTTON_Init( rst_cfg );
    bt_cnt = BUTTON_Init( cnt_cfg );
    tmr_cnt = TIMER_Init( tmr_cfg );
    
    char my_str_timer[3];
    char my_str_btn[10];

    while (true) 
    {
        BUTTON_Update( bt_rst );
        BUTTON_Update( bt_cnt );
        
        if( !BUTTON_GetState( bt_cnt ) && my_timer ){ my_counter++; }
        if( !BUTTON_GetState( bt_rst ) )
        {   
            reset_timer(); 
            reset_counter();
            my_timer_state = RUNNING;
        }

        sprintf( my_str_timer , "%i" , my_timer );
        sprintf( my_str_btn , "Botao %i" , my_counter );

        D1306_Clear( oled );
        D1306_DrawString( oled , 0 , 0 , 1 , my_str_timer );
        D1306_DrawString( oled , 0 , 20 , 1 , my_str_btn );

        D1306_Show( oled );
        sleep_ms( 100 );
    }
}