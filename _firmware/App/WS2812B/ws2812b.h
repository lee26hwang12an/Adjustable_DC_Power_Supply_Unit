// #ifndef _WS2812B_H_
// #define _WS2812B_H_

// #ifdef __cplusplus
// extern "C" {
// #endif /* __cplusplus */


// #include "main.h"
// #include "stm32Abstract.h"


// typedef enum
// {
//     WS2812B_DEFAULT_LEDS_COUNT = 60,
//     WS2812B_RESET_CODE_PADDING = 40,
//     WS2812B_DMA_INCREMENT_16BIT = 2,
//     WS2812B_DMA_INCREMENT_8BIT = 4,
//     WS2812B_DMA_INCREMENT_32BIT = 1,
//     WS2812B_UPDATE_FINISHED = 1,
//     WS2812B_UPDATE_ONGOING = 0,
// } WS2812B_CONST;

// class WS2812B
// {
// public:
//     /*
//     @param *PWMgenerator Pointer to STM32 pointer responsible for generating DMA PWM.
//     @param channel Channel number of PWMgenerator.
//     @param numLed Amount of LEDs.
//     */
//     WS2812B(TIM_HandleTypeDef *PWMgenerator, uint32_t channel, uint16_t numLed);

// public:
//     volatile uint8_t UPDATE_STATE;

// // private:
//     TIM_HandleTypeDef *_PWMgenerator;
//     uint16_t _ledsCount;
//     uint32_t _channel;
//     uint32_t _BIT_1_HIGH, _BIT_0_HIGH;
//     uint32_t *_colorData;
//     uint32_t *_buffer;
//     uint8_t _bufferDataMultiplier;

// public:
//     /*
//     Initialize LED strip.
//     @param DMAincrement Data increment step configured for DMA, defaults to 16-bit step.

//     - WS2812B_DMA_INCREMENT_8BIT if DMA is configured to increment by Byte

//     - WS2812B_DMA_INCREMENT_16BIT if DMA is configured to increment by Half Word

//     - WS2812B_DMA_INCREMENT_32BIT if DMA is configured to increment by Word
//     */
//     void init(uint8_t DMAincrement = WS2812B_DMA_INCREMENT_16BIT);
//     /*
//     Paint LEDs with an RGB solid color.
//     @param color RGB value of the color.
//     @param start Starting LED.
//     @param end Ending LED.
//     */
//     void solidColor(uint32_t color, uint16_t start, uint16_t end);
//     /*
//     Push all color data to the LED strip.
//     */
//     void render();

// private:
//     /* Extract color RED from given RGB. */
//     uint8_t extractRed(uint32_t RGB);
//     /* Extract color GREEN from given RGB. */
//     uint8_t extractGreen(uint32_t RGB);
//     /* Extract color BLUE from given RGB. */
//     uint8_t extractBlue(uint32_t RGB);
//     /* Combine Red Green Blue values to make RGB color data. */
//     uint32_t combineRGB(uint8_t red, uint8_t green, uint8_t blue);
//     /* Convert RGB to GRB color order. */
//     uint32_t toGRB(uint32_t RGB);
//     /* Calculate and push color data to the buffer to be sent. */
//     void updateBuffer();
//     /* Set all buffer values to 0. */
//     void clearBuffer();
// };


// #ifdef __cplusplus
// }
// #endif /* __cplusplus */

// #endif /* _WS2812B_H_ */