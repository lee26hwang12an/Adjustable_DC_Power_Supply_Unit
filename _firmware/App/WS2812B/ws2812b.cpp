#include "ws2812b.h"
#include <stdlib.h>

/*
=====================================================================
    PRIVATE FUNCTIONS
=====================================================================
*/

/*
=====================================================================
    CONSTRUCTORS
=====================================================================
*/

WS2812B::WS2812B(TIM_HandleTypeDef *PWMgenerator, uint32_t channel, uint16_t numLed)
    : _PWMgenerator(PWMgenerator), _channel(channel), _ledsCount(numLed)
{
}

/*
=====================================================================
    METHODS
=====================================================================
*/

void WS2812B::init()
{
    _colorData = (uint32_t *)calloc(_ledsCount, sizeof(uint32_t));
    _buffer = (uint32_t *)calloc(_ledsCount * 24, sizeof(uint32_t));
}

void WS2812B::solidColor(uint32_t color, uint16_t start, uint16_t end)
{
    color = WS2812B::toGRB(color);
    for (uint16_t ledIndex = start; ledIndex <= end; ledIndex++)
        _colorData[ledIndex] = color;

    WS2812B::updateBuffer();
}

void WS2812B::render()
{
    HAL_TIM_PWM_Start_DMA(_PWMgenerator, _channel, (uint32_t *)_buffer, _ledsCount * 48);
}

uint8_t WS2812B::extractRed(uint32_t RGB)
{ return (uint8_t)((RGB >> 16) & 0xFF); }
uint8_t WS2812B::extractGreen(uint32_t RGB)
{ return (uint8_t)((RGB >> 8) & 0xFF); }
uint8_t WS2812B::extractBlue(uint32_t RGB)
{ return (uint8_t)((RGB >> 0) & 0xFF); }
uint32_t combineRGB(uint8_t red, uint8_t green, uint8_t blue)
{
    uint32_t RGB = (
        (uint32_t)red << 16 |
        (uint32_t)green << 8 |
        (uint32_t)blue << 0
    );
    return RGB;
}
uint32_t WS2812B::toGRB(uint32_t RGB)
{
    uint32_t GRB = (
        (uint32_t)(WS2812B::extractGreen(RGB) << 16) |
        (uint32_t)(WS2812B::extractRed(RGB) << 8) |
        (uint32_t)(WS2812B::extractBlue(RGB) << 0)
    );
    return GRB;
}

void WS2812B::updateBuffer()
{
    uint32_t bufferIndex = 0;
    for (uint16_t ledIndex = 0; ledIndex < _ledsCount; ledIndex++)
        for (int8_t bitIndex = 23; bitIndex >= 0; bitIndex--)
        {
            if ((_colorData[ledIndex] >> bitIndex) & 0b1)
                _buffer[bufferIndex] = 60 - 1;
            else
                _buffer[bufferIndex] = 30 - 1;
            bufferIndex++;
        }
}