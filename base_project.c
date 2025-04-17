#include <stdio.h>
#include "pico/stdlib.h"
#include "hal/hardware/gpio/gpio.h"
#include "hal/hardware/timer/timer.h"
#include "hal/display/driver1306.h"

uint g_counter;
uint g_timer = 10;

const GPIO_CONFIG_t rst_bt_cfg = {
    .pin = 5,
    .direction = 0,
    .logic = 1,
    .mode = 1,
    .cb_enabled = true,
    .events = GPIO_IRQ_EDGE_FALL,
};

const GPIO_CONFIG_t cnt_bt_cfg = {
    .pin = 6,
    .direction = 0,
    .logic = 1,
    .mode = 1,
    .cb_enabled = true,
    .events = GPIO_IRQ_EDGE_FALL,
};

const D1306_CONFIG_t oled_cfg = {
    .external_vcc = false,
    .width = 128,
    .height = 64,
    .i2c_cfg.address = 0x3C,
    .i2c_cfg.frequency = 400*1000,
    .i2c_cfg.i2c_id = 1,
    .i2c_cfg.pin_sda = 14,
    .i2c_cfg.pin_sdl = 15,
};

D1306_t* oled;
GPIO_t* bt_rst;
GPIO_t* bt_cnt;

void reset_handler()
{
    g_timer = 10;
    g_counter = 0;
}

void cnt_handler()
{
    if( g_timer )
    { 
        g_counter++; 
    }
}

void gpio_irq_dispatcher( uint gpio, uint32_t events ) 
{
    switch (gpio) 
    {
        case 5:
            reset_handler();
            break;
        case 6:
            cnt_handler();
            break;
        default:
        break;
    }
}

int main()
{
    stdio_init_all();

    oled = D1306_Init( oled_cfg );
    bt_rst = GPIO_Init( rst_bt_cfg );
    bt_cnt = GPIO_Init( cnt_bt_cfg );

    gpio_set_irq_callback( gpio_irq_dispatcher );

    irq_set_enabled(IO_IRQ_BANK0, true);

    char my_str_timer[3];
    char my_str_btn[10];

    while (true) 
    {
        sprintf( my_str_timer , "%i" , g_timer );
        sprintf( my_str_btn , "Botao %i" , g_counter );

        D1306_Clear( oled );
        D1306_DrawString( oled , 0 , 0 , 1 , my_str_timer );
        D1306_DrawString( oled , 0 , 20 , 1 , my_str_btn );

        D1306_Show( oled );
        sleep_ms(1000);
        if( g_timer ){ g_timer--; }
    }
}
