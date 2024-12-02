#include "app.h"
#include "stm32Abstract.h"
#include "ws2812b.h"
#include "modbusRTU.h"
#include <stdio.h>


extern TIM_HandleTypeDef htim1;
extern DMA_HandleTypeDef hdma_tim1_ch1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
    // -------------- Change huart_x to your appropriate Hardware UART/USART
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
#ifdef __cplusplus
}
#endif /* __cplusplus */


WS2812B led = WS2812B(&htim1, TIM_CHANNEL_1, 10);
ModbusRTU modbusClient = ModbusRTU(&huart1);


/*
=====================================================================
    SETUP
=====================================================================
*/
void setup()
{
    HAL_Delay(1000);

    led.init();
    modbusClient.init();

    modbusClient.request(0x01, 0x03, 0x00, 0x02);
}


/*
=====================================================================
    MAIN LOOP
=====================================================================
*/
void loop()
{
    // led.solidColor(0xFF0000, 0, 29);
    // // led.solidColor(0x000000, 2, 2);
    // led.solidColor(0x000000, 30, 59);
    // led.render();
    // HAL_Delay(200);
    // led.solidColor(0x000000, 0, 29);
    // // led.solidColor(0x000000, 2, 2);
    // led.solidColor(0x0000FF, 30, 59);
    // led.render();
    // HAL_Delay(200);

    modbusClient.request(0x01, MODBUS_RTU_READ_HOLDING_REGISTERS, 0x0002, 0x02);
    HAL_Delay(1000);
    for (uint8_t i = 0; i < 9; i++)
        printf("%x ", modbusClient.receiveBuffer[i]);
    printf("\n");
    HAL_Delay(1000);
}


/*
=====================================================================
    CALLBACKS
=====================================================================
*/
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
    HAL_TIM_PWM_Stop_DMA(&htim1, TIM_CHANNEL_1);
    led.UPDATE_STATE = WS2812B_UPDATE_FINISHED;
}