#include "ws2812b.h"
#include <stdlib.h>
#include <string.h>

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
    _targetColorData = (uint32_t *)calloc(_ledsCount, sizeof(uint32_t));
    _buffer = (uint32_t *)calloc(
        _ledsCount * 24 + WS2812B_RESET_CODE_PADDING, sizeof(uint32_t)
    );
    _BIT_1_HIGH = 2 * _PWMgenerator->Instance->ARR / 3 + 1;
    _BIT_0_HIGH = _PWMgenerator->Instance->ARR / 3 + 1;
    _bufferDataMultiplier = 24 * DMAincrement;
}

void WS2812B::solidColor(uint32_t color, uint16_t start, uint16_t end)
{
    // color = WS2812B::toGRB(color);
    for (uint16_t ledIndex = start; ledIndex <= end; ledIndex++)
        _targetColorData[ledIndex] = color;
}

void WS2812B::gradient2Colors(uint32_t startColor, uint16_t start, uint32_t endColor, uint16_t end)
{
    float stepRed = (float)WS2812B::extractRed(startColor) - (float)WS2812B::extractRed(endColor);
    float stepGreen = (float)WS2812B::extractGreen(startColor) - (float)WS2812B::extractGreen(endColor);
    float stepBlue = (float)WS2812B::extractBlue(startColor) - (float)WS2812B::extractBlue(endColor);
    stepRed = stepRed / (float)(end - start);
    stepGreen = stepGreen / (float)(end - start);
    stepBlue = stepBlue / (float)(end - start);

    uint16_t colorIterate = 0;
    while (start <= end)
    {
        _targetColorData[start] = WS2812B::combineRGB(
            WS2812B::extractRed(startColor) - colorIterate * stepRed,
            WS2812B::extractGreen(startColor) - colorIterate * stepGreen,
            WS2812B::extractBlue(startColor) - colorIterate * stepBlue
        );
        _targetColorData[end] = WS2812B::combineRGB(
            WS2812B::extractRed(endColor) + colorIterate * stepRed,
            WS2812B::extractGreen(endColor) + colorIterate * stepGreen,
            WS2812B::extractBlue(endColor) + colorIterate * stepBlue
        );
        colorIterate++; start++; end--;
    }
}

void WS2812B::render()
{
    memcpy(_colorData, _targetColorData, _ledsCount * 4);
    WS2812B::updateBuffer();

    HAL_TIM_PWM_Start_DMA(
        _PWMgenerator, _channel,
        (uint32_t *)_buffer,
        _ledsCount * _bufferDataMultiplier
    );

    UPDATE_STATE = WS2812B_UPDATE_ONGOING;
    while (UPDATE_STATE == WS2812B_UPDATE_ONGOING);
}

WS2812B_CONST WS2812B::transition()
{
    // uint16_t checkDifference = 0;
    // for (uint16_t ledIterate = 0; ledIterate < _ledsCount; ledIterate++)
    // {
    //     if (_colorData[ledIterate] == _targetColorData[ledIterate])
    //     {
    //         checkDifference++;
    //         continue;
    //     }

    //     uint8_t currentRed = WS2812B::extractRed(_colorData[ledIterate]);
    //     uint8_t currentGreen = WS2812B::extractGreen(_colorData[ledIterate]);
    //     uint8_t currentBlue = WS2812B::extractBlue(_colorData[ledIterate]);

    //     uint8_t targetRed = WS2812B::extractRed(_targetColorData[ledIterate]);
    //     uint8_t targetGreen = WS2812B::extractGreen(_targetColorData[ledIterate]);
    //     uint8_t targetBlue = WS2812B::extractBlue(_targetColorData[ledIterate]);

    //     if (currentRed < targetRed) currentRed++;
    //     else if (currentRed > targetRed) currentRed--;

    //     if (currentGreen < targetGreen) currentGreen++;
    //     else if (currentGreen > targetGreen) currentGreen--;

    //     if (currentBlue < targetBlue) currentBlue++;
    //     else if (currentBlue > targetBlue) currentBlue--;

    //     _colorData[ledIterate] = WS2812B::combineRGB(currentRed, currentGreen, currentBlue);
    // }

    // if (checkDifference == _ledsCount)
    //     return WS2812B_TRANSITION_FINISHED;

    // WS2812B::updateBuffer();

    // HAL_TIM_PWM_Start_DMA(
    //     _PWMgenerator, _channel,
    //     (uint32_t *)_buffer,
    //     _ledsCount * _bufferDataMultiplier
    // );

    // UPDATE_STATE = WS2812B_UPDATE_ONGOING;
    // while (UPDATE_STATE == WS2812B_UPDATE_ONGOING);

    // return (WS2812B_CONST)0;
}

WS2812B_CONST WS2812B::transition(float *timeTick, float duration)
{
    if (*timeTick > duration)
    {
        free(_transRed); free(_transGreen); free(_transBlue);
        free(_prevColorData);
        return WS2812B_TRANSITION_FINISHED;
    }

    if (duration <= 0.00f)
        return WS2812B_TRANSITION_FINISHED;

    if (*timeTick == 0.00f)
    {
        *timeTick = *timeTick + duration / 1000.0f; // Prevent accidental memory leak
        _transRed = (float *)calloc(_ledsCount, sizeof(uint32_t));
        _transGreen = (float *)calloc(_ledsCount, sizeof(uint32_t));
        _transBlue = (float *)calloc(_ledsCount, sizeof(uint32_t));
        _prevColorData = (uint32_t *)calloc(_ledsCount, sizeof(uint32_t));
        for (uint16_t ledIterate = 0; ledIterate < _ledsCount; ledIterate++)
        {
            _transRed[ledIterate] = (float)WS2812B::extractRed(_targetColorData[ledIterate]) - (float)WS2812B::extractRed(_colorData[ledIterate]);
            _transGreen[ledIterate] = (float)WS2812B::extractGreen(_targetColorData[ledIterate]) - (float)WS2812B::extractGreen(_colorData[ledIterate]);
            _transBlue[ledIterate] = (float)WS2812B::extractBlue(_targetColorData[ledIterate]) - (float)WS2812B::extractBlue(_colorData[ledIterate]);
            _transRed[ledIterate] = _transRed[ledIterate] / duration;
            _transGreen[ledIterate] = _transGreen[ledIterate] / duration;
            _transBlue[ledIterate] = _transBlue[ledIterate] / duration;
        }
        for (uint16_t ledIterate = 0; ledIterate < _ledsCount; ledIterate++)
            _prevColorData[ledIterate] = _colorData[ledIterate];
    }

    for (uint16_t ledIterate = 0; ledIterate < _ledsCount; ledIterate++)
        _colorData[ledIterate] = WS2812B::combineRGB(
            WS2812B::extractRed(_prevColorData[ledIterate]) + *timeTick * _transRed[ledIterate],
            WS2812B::extractGreen(_prevColorData[ledIterate]) + *timeTick * _transGreen[ledIterate],
            WS2812B::extractBlue(_prevColorData[ledIterate]) + *timeTick * _transBlue[ledIterate]
        );

    WS2812B::updateBuffer();

    HAL_TIM_PWM_Start_DMA(
        _PWMgenerator, _channel,
        (uint32_t *)_buffer,
        _ledsCount * _bufferDataMultiplier
    );

    UPDATE_STATE = WS2812B_UPDATE_ONGOING;
    while (UPDATE_STATE == WS2812B_UPDATE_ONGOING);

    return (WS2812B_CONST)0;
}

 void WS2812B::startCallbackClock()
 { HAL_TIM_Base_Start_IT(_PWMgenerator); }
  void WS2812B::stopCallbackClock()
 { HAL_TIM_Base_Stop_IT(_PWMgenerator); }

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
            _buffer[bufferIndex] = ((WS2812B::toGRB(_colorData[ledIndex]) >> bitIndex) & 0b1) ? _BIT_1_HIGH : _BIT_0_HIGH;
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