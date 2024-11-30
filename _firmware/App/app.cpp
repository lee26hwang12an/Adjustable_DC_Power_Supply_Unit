#include "app.h"
#include "stm32Abstract.h"
#include "ws2812b.h"
#include <stdio.h>


extern TIM_HandleTypeDef htim1;
extern DMA_HandleTypeDef hdma_tim1_ch1;
extern UART_HandleTypeDef huart1;
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
    // -------------- Change huart_x to your appropriate Hardware UART/USART
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}

WS2812B led = WS2812B(&htim1, TIM_CHANNEL_1, 4);


/*
=====================================================================
    SETUP
=====================================================================
*/
void setup()
{
    HAL_Delay(1000);

    led.init();

    led.solidColor(0x00FFFF, 0, 1);
    led.solidColor(0xFF00FF, 2, 3);
    led.render();

    HAL_Delay(1000);
    led.solidColor(0x00FF00, 1, 2);
    led.render();
}


/*
=====================================================================
    MAIN LOOP
=====================================================================
*/
void loop()
{
    // led.send();
}


/*
=====================================================================
    CALLBACKS
=====================================================================
*/
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
}