#ifndef _WS2812B_H_
#define _WS2812B_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include "main.h"
#include "stm32Abstract.h"


typedef enum
{
    WS2812B_DEFAULT_LEDS_COUNT = 60,
    WS2812B_DMA_INCREMENT_16BIT = 2,
    WS2812B_DMA_INCREMENT_8BIT = 4,
    WS2812B_DMA_INCREMENT_32BIT = 1,
};

class WS2812B
{
public:
    WS2812B(TIM_HandleTypeDef *PWMgenerator, uint32_t channel, uint16_t numLed);

public:

// private:
    TIM_HandleTypeDef *_PWMgenerator;
    uint16_t _ledsCount;
    uint32_t _channel;
    uint32_t _BIT_1_HIGH, _BIT_0_HIGH;
    uint32_t *_colorData;
    uint32_t *_buffer;
    uint8_t _bufferDataMultiplier;

public:
    void init(uint8_t DMAincrement = WS2812B_DMA_INCREMENT_16BIT);
    void solidColor(uint32_t color, uint16_t start, uint16_t end);
    void render();

private:
    uint8_t extractRed(uint32_t RGB);
    uint8_t extractGreen(uint32_t RGB);
    uint8_t extractBlue(uint32_t RGB);
    uint32_t combineRGB(uint8_t red, uint8_t green, uint8_t blue);
    uint32_t toGRB(uint32_t RGB);
    void updateBuffer();
};


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _WS2812B_H_ */