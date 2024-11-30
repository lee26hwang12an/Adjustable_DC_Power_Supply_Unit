#ifndef _STM32ABSTRACT_H_
#define _STM32ABSTRACT_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include "main.h"

#define __PI 3.14159265359f
#define __2PI 6.28318530718f
#define __SQRT3 1.732050808f

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;

} STM32GPIO_t;

#define __STM32setGPIO(gpio) HAL_GPIO_WritePin(gpio.port, gpio.pin, GPIO_PIN_SET)
#define __STM32resetGPIO(gpio) HAL_GPIO_WritePin(gpio.port, gpio.pin, GPIO_PIN_RESET)
#define __STM32flipGPIO(gpio) HAL_GPIO_TogglePin(gpio.port, gpio.pin)
#define __STM32getGPIO(gpio) HAL_GPIO_ReadPin(gpio.port, gpio.pin)

#define NOT_SET (STM32GPIO_t){.port=GPIOH, .pin=0xFF}
#define PA0 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_0}
#define PA1 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_1}
#define PA2 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_2}
#define PA3 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_3}
#define PA4 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_4}
#define PA5 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_5}
#define PA6 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_6}
#define PA7 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_7}
#define PA8 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_8}
#define PA9 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_9}
#define PA10 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_10}
#define PA11 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_11}
#define PA12 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_12}
#define PA13 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_13}
#define PA14 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_14}
#define PA15 (STM32GPIO_t){.port=GPIOA, .pin=GPIO_PIN_15}
#define PB0 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_0}
#define PB1 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_1}
#define PB2 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_2}
#define PB3 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_3}
#define PB4 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_4}
#define PB5 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_5}
#define PB6 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_6}
#define PB7 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_7}
#define PB8 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_8}
#define PB9 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_9}
#define PB10 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_10}
#define PB11 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_11}
#define PB12 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_12}
#define PB13 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_13}
#define PB14 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_14}
#define PB15 (STM32GPIO_t){.port=GPIOB, .pin=GPIO_PIN_15}
#define PC0 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_0}
#define PC1 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_1}
#define PC2 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_2}
#define PC3 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_3}
#define PC4 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_4}
#define PC5 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_5}
#define PC6 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_6}
#define PC7 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_7}
#define PC8 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_8}
#define PC9 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_9}
#define PC10 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_10}
#define PC11 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_11}
#define PC12 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_12}
#define PC13 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_13}
#define PC14 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_14}
#define PC15 (STM32GPIO_t){.port=GPIOC, .pin=GPIO_PIN_15}
#define PD0 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_0}
#define PD1 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_1}
#define PD2 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_2}
#define PD3 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_3}
#define PD4 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_4}
#define PD5 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_5}
#define PD6 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_6}
#define PD7 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_7}
#define PD8 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_8}
#define PD9 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_9}
#define PD10 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_10}
#define PD11 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_11}
#define PD12 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_12}
#define PD13 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_13}
#define PD14 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_14}
#define PD15 (STM32GPIO_t){.port=GPIOD, .pin=GPIO_PIN_15}
#define PE0 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_0}
#define PE1 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_1}
#define PE2 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_2}
#define PE3 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_3}
#define PE4 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_4}
#define PE5 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_5}
#define PE6 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_6}
#define PE7 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_7}
#define PE8 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_8}
#define PE9 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_9}
#define PE10 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_10}
#define PE11 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_11}
#define PE12 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_12}
#define PE13 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_13}
#define PE14 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_14}
#define PE15 (STM32GPIO_t){.port=GPIOE, .pin=GPIO_PIN_15}
#define PF0 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_0}
#define PF1 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_1}
#define PF2 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_2}
#define PF3 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_3}
#define PF4 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_4}
#define PF5 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_5}
#define PF6 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_6}
#define PF7 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_7}
#define PF8 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_8}
#define PF9 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_9}
#define PF10 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_10}
#define PF11 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_11}
#define PF12 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_12}
#define PF13 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_13}
#define PF14 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_14}
#define PF15 (STM32GPIO_t){.port=GPIOF, .pin=GPIO_PIN_15}
#define PG0 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_0}
#define PG1 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_1}
#define PG2 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_2}
#define PG3 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_3}
#define PG4 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_4}
#define PG5 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_5}
#define PG6 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_6}
#define PG7 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_7}
#define PG8 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_8}
#define PG9 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_9}
#define PG10 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_10}
#define PG11 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_11}
#define PG12 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_12}
#define PG13 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_13}
#define PG14 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_14}
#define PG15 (STM32GPIO_t){.port=GPIOG, .pin=GPIO_PIN_15}
#define PH0 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_0}
#define PH1 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_1}
#define PH2 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_2}
#define PH3 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_3}
#define PH4 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_4}
#define PH5 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_5}
#define PH6 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_6}
#define PH7 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_7}
#define PH8 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_8}
#define PH9 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_9}
#define PH10 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_10}
#define PH11 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_11}
#define PH12 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_12}
#define PH13 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_13}
#define PH14 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_14}
#define PH15 (STM32GPIO_t){.port=GPIOH, .pin=GPIO_PIN_15}
#define PI0 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_0}
#define PI1 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_1}
#define PI2 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_2}
#define PI3 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_3}
#define PI4 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_4}
#define PI5 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_5}
#define PI6 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_6}
#define PI7 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_7}
#define PI8 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_8}
#define PI9 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_9}
#define PI10 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_10}
#define PI11 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_11}
#define PI12 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_12}
#define PI13 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_13}
#define PI14 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_14}
#define PI15 (STM32GPIO_t){.port=GPIOI, .pin=GPIO_PIN_15}



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _STM32ABSTRACT_H_ */
