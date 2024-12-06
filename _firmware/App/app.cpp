#include "app.h"
#include "stm32Abstract.h"
#include "ws2812b.h"
#include "modbusRTU.h"
#include <stdio.h>


/*
=====================================================================
    MISCELLANEOUS
=====================================================================
*/
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


/*
=====================================================================
    INSTANCING
=====================================================================
*/

extern TIM_HandleTypeDef htim1;
extern DMA_HandleTypeDef hdma_tim1_ch1;
WS2812B led = WS2812B(&htim1, TIM_CHANNEL_1, 60);

extern UART_HandleTypeDef huart1;
ModbusRTU modbusClient = ModbusRTU(&huart1);

uint8_t valueChanged = 0;
uint8_t volt_MSB, volt_LSB, curr_MSB, curr_LSB;
uint32_t transitionTick = 0;


/*
=====================================================================
    SETUP
=====================================================================
*/
void setup()
{
    HAL_Delay(1000);

    led.init();
    led.startCallbackClock();

    modbusClient.init();
    modbusClient.request(0x01, 0x03, 0x00, 0x02);

    // led.gradient2Colors(0xFF0000, 0, 0x0000FF, 59);
    // led.render();
    // HAL_Delay(500);

    // led.gradient2Colors(0xFF0000, 0, 0x00ffFF, 59);
    led.solidColor(0xFF0000, 0, 59);
    led.render();
    // HAL_Delay(2000);
    // led.gradient2Colors(0xFF0000, 0, 0x0000FF, 59);
    // led.solidColor(0x00FFFF, 0, 59);
}


/*
=====================================================================
    MAIN LOOP
=====================================================================
*/
float tick = 0.00f;
void loop()
{
    if (!valueChanged)
        return;

    led.stopCallbackClock();

    if (modbusClient.receiveBuffer[3] != volt_MSB ||
        modbusClient.receiveBuffer[4] != volt_LSB ||
        modbusClient.receiveBuffer[5] != curr_MSB ||
        modbusClient.receiveBuffer[6] != curr_LSB)
    {
        volt_MSB = modbusClient.receiveBuffer[3];
        volt_LSB = modbusClient.receiveBuffer[4];
        curr_MSB = modbusClient.receiveBuffer[5];
        curr_LSB = modbusClient.receiveBuffer[6];
    }


    uint16_t volt = ((uint16_t)volt_MSB << 8) | ((uint16_t)volt_LSB << 0);
    uint16_t curr = ((uint16_t)curr_MSB << 8) | ((uint16_t)curr_LSB << 0);
    uint32_t ledColor;

    if (__inProximity(volt, 250, 250))
        ledColor = 0x0000FF;
    else if (__inProximity(volt, 750, 250))
        ledColor = 0x00FFFF;
    else if (__inProximity(volt, 1250, 250))
        ledColor = 0xFFFF00;
    else if (__inProximity(volt, 1750, 250))
        ledColor = 0xFF6600;
    else if (__inProximity(volt, 2250, 250))
        ledColor = 0xFF1F00;
    else if (__inProximity(volt, 2750, 250))
        ledColor = 0xFF0000;
    else if (volt > 3000)
        ledColor = 0x1100FF;

    led.solidColor(ledColor, 0, 59);
    tick = 0;
    while (led.transition(&tick, 1000) != WS2812B_TRANSITION_FINISHED);
    // led.render();

    valueChanged = 0;
    led.startCallbackClock();
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

#define CALLED_TIMES_UNTIL_TRIGGERED (3125 * 2) // 2-second callback
uint16_t callbackCounter = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    tick = tick + 0.00032f;
    callbackCounter++;
    if (callbackCounter < CALLED_TIMES_UNTIL_TRIGGERED)
        return;

    modbusClient.request(0x01, MODBUS_RTU_READ_HOLDING_REGISTERS, 0x0002, 0x02);
    valueChanged = 1;
    callbackCounter = 0;

    __STM32flipGPIO(PC13);
}
