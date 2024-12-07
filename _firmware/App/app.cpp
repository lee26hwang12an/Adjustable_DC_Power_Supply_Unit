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

#define __BLUE      0x001FFF
#define __CYAN      0x22FFEE
#define __GREEN     0x00FF00
#define __YELLOW    0xFFAA00
#define __ORANGE    0xFF3300
#define __RED       0xFF0000
#define __PURPLE    0x6900FF


/*
=====================================================================
    INSTANCING
=====================================================================
*/

#define __LEDS_COUNT 16
extern TIM_HandleTypeDef htim1;
extern DMA_HandleTypeDef hdma_tim1_ch1;
WS2812B led = WS2812B(&htim1, TIM_CHANNEL_1, __LEDS_COUNT);

#define __SLAVE_ADDRESS     0x01
#define __ON_OFF_REG        0x0012
#define __VOLT_AMP_REG      0x0002
extern UART_HandleTypeDef huart1;
ModbusRTU modbusClient = ModbusRTU(&huart1);

extern TIM_HandleTypeDef htim2; // 1kHz timer to get miliseconds
#define __START_TICK_COUNTING() HAL_TIM_Base_Start_IT(&htim2)
float tick = 0.00f;

uint8_t valueChanged = 0;
uint8_t volt_MSB, volt_LSB, curr_MSB, curr_LSB;


/*
=====================================================================
    SETUP
=====================================================================
*/
void setup()
{
    HAL_Delay(1000);

    // --------------------------------------------------------- INIT
    led.init();
    modbusClient.init();

    // ------------------------------------------ LED START-UP EFFECT
    led.solidColor(0x000000, 0, __LEDS_COUNT - 1);
    led.render();
    HAL_Delay(500);
    for (uint8_t blinks = 0; blinks < 5; blinks++)
    {
        led.solidColor(0xFF0000, 0, __LEDS_COUNT / 2 - 1);
        led.solidColor(0x000000, __LEDS_COUNT / 2, __LEDS_COUNT);
        led.render();
        HAL_Delay(200);
        led.solidColor(0x000000, 0, __LEDS_COUNT / 2 - 1);
        led.solidColor(0x0000FF, __LEDS_COUNT / 2, __LEDS_COUNT);
        led.render();
        HAL_Delay(200);
    }
    led.solidColor(0x000000, 0, __LEDS_COUNT - 1);
    led.render();
    HAL_Delay(500);

    // --------------------------------------- START TIMERS CALLBACKS
    __START_TICK_COUNTING();
    led.startCallbackClock();
}


/*
=====================================================================
    MAIN LOOP
=====================================================================
*/
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
    else
    {
        led.startCallbackClock();
        return;
    }

    uint16_t volt = ((uint16_t)volt_MSB << 8) | ((uint16_t)volt_LSB << 0);
    uint16_t curr = ((uint16_t)curr_MSB << 8) | ((uint16_t)curr_LSB << 0);
    uint32_t ledVolt, ledAmps;

    if (volt <= 5 && curr <= 3)
    {
        modbusClient.request(
            __SLAVE_ADDRESS, MODBUS_RTU_READ_HOLDING_REGISTERS,
            __ON_OFF_REG, 1
        );
        uint8_t state = modbusClient.receiveBuffer[4];
        if (state == 0)
        {
            ledVolt = 0;
            ledAmps = 0;
            modbusClient.request(
                __SLAVE_ADDRESS, MODBUS_RTU_READ_HOLDING_REGISTERS,
                __VOLT_AMP_REG, 0x02);
            goto BUTTON_OFF;
        }
    }

    if (__inProximity(volt, 250, 250))
        ledVolt = __BLUE;
    else if (__inProximity(volt, 750, 250))
        ledVolt = __CYAN;
    else if (__inProximity(volt, 1250, 250))
        ledVolt = __GREEN;
    else if (__inProximity(volt, 1750, 250))
        ledVolt = __YELLOW;
    else if (__inProximity(volt, 2250, 250))
        ledVolt = __ORANGE;
    else if (__inProximity(volt, 2750, 250))
        ledVolt = __RED;
    else if (volt > 3000)
        ledVolt = __PURPLE;
    
    if (__inProximity(curr, 50, 50))
        ledAmps = __BLUE;
    else if (__inProximity(curr, 200, 100))
        ledAmps = __CYAN;
    else if (__inProximity(curr, 400, 100))
        ledAmps = __GREEN;
    else if (__inProximity(curr, 600, 100))
        ledAmps = __YELLOW;
    else if (__inProximity(curr, 800, 100))
        ledAmps = __ORANGE;
    else if (__inProximity(curr, 950, 50))
        ledAmps = __RED;
    else if (curr > 1000)
        ledAmps = __PURPLE;

    BUTTON_OFF:
    printf("%.2f\t%.2f\n", (float)volt / 100.0f, (float)curr / 100.0f);
    led.gradient2Colors(ledVolt, 0, ledAmps, __LEDS_COUNT - 1);
    tick = 0;
    while (led.transition(&tick, 1000) != WS2812B_TRANSITION_FINISHED);

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
    if (htim->Instance == TIM1)
    {
        callbackCounter++;
        if (callbackCounter < CALLED_TIMES_UNTIL_TRIGGERED)
            return;

        modbusClient.request(
            __SLAVE_ADDRESS, MODBUS_RTU_READ_HOLDING_REGISTERS,
            __VOLT_AMP_REG, 0x02);
        valueChanged = 1;
        callbackCounter = 0;

        __STM32flipGPIO(PC13);
    }
    if (htim->Instance == TIM2)
    {
        tick++;
    }
}
