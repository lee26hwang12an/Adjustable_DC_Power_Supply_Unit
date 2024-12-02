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

void WS2812B::init(uint8_t DMAincrement)
{
    _colorData = (uint32_t *)calloc(_ledsCount, sizeof(uint32_t));
    _buffer = (uint32_t *)calloc(
        _ledsCount * 24 + WS2812B_RESET_CODE_PADDING, sizeof(uint32_t)
    );
    _BIT_1_HIGH = 2 * _PWMgenerator->Instance->ARR / 3 + 1;
    _BIT_0_HIGH = _PWMgenerator->Instance->ARR / 3 + 1;
    _bufferDataMultiplier = 24 * DMAincrement;
}

void WS2812B::solidColor(uint32_t color, uint16_t start, uint16_t end)
{
    color = WS2812B::toGRB(color);
    for (uint16_t ledIndex = start; ledIndex <= end; ledIndex++)
        _colorData[ledIndex] = color;
}

void WS2812B::render()
{
    WS2812B::updateBuffer();

    HAL_TIM_PWM_Start_DMA(
        _PWMgenerator, _channel,
        (uint32_t *)_buffer,
        _ledsCount * _bufferDataMultiplier
    );

    UPDATE_STATE = WS2812B_UPDATE_ONGOING;
    while (UPDATE_STATE == WS2812B_UPDATE_ONGOING);
}

uint8_t WS2812B::extractRed(uint32_t RGB)
{ return (uint8_t)((RGB >> 16) & 0xFF); }
uint8_t WS2812B::extractGreen(uint32_t RGB)
{ return (uint8_t)((RGB >> 8) & 0xFF); }
uint8_t WS2812B::extractBlue(uint32_t RGB)
{ return (uint8_t)((RGB >> 0) & 0xFF); }
uint32_t WS2812B::combineRGB(uint8_t red, uint8_t green, uint8_t blue)
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
            _buffer[bufferIndex] = ((_colorData[ledIndex] >> bitIndex) & 0b1) ? _BIT_1_HIGH : _BIT_0_HIGH;
            bufferIndex++;
        }
    for (bufferIndex; bufferIndex < _ledsCount * 24 + WS2812B_RESET_CODE_PADDING; bufferIndex++)
        _buffer[bufferIndex] = 0;
}

void WS2812B::clearBuffer()
{
    for (uint32_t bufferIndex = 0;
        bufferIndex < _ledsCount * 24 + WS2812B_RESET_CODE_PADDING;
        bufferIndex++)
    { _buffer[bufferIndex] = 0; }
}