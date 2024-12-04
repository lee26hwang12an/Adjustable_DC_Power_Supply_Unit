#include "modbusRTU.h"
#include "stm32Abstract.h"
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

ModbusRTU::ModbusRTU(UART_HandleTypeDef *hserial)
    : _serial(hserial)
{
}


/*
=====================================================================
    METHODS
=====================================================================
*/

void ModbusRTU::init()
{
    ModbusRTU::receiveBuffer = (uint8_t *)calloc(8, sizeof(uint8_t));
}

void ModbusRTU::request(uint8_t slaveAddress, uint8_t funcCode, uint16_t startReg, uint16_t regCount)
{
    if (funcCode != MODBUS_RTU_READ_COIL &&
        funcCode != MODBUS_RTU_READ_DISCRETE_INPUTS &&
        funcCode != MODBUS_RTU_READ_HOLDING_REGISTERS &&
        funcCode != MODBUS_RTU_READ_INPUT_REGISTERS)
        return;

    // Prepare send buffer:
    _sendBuffer[0] = slaveAddress;
    _sendBuffer[1] = funcCode;
    _sendBuffer[2] = (startReg >> 8) & 0xFF;
    _sendBuffer[3] = (startReg >> 0) & 0xFF;
    _sendBuffer[4] = (regCount >> 8) & 0xFF;
    _sendBuffer[5] = (regCount >> 0) & 0xFF;
    // Calculate and append CRC:
    uint16_t clientCRC = appendCRC(_sendBuffer);
    _sendBuffer[6] = (uint8_t)((clientCRC >> 0) & 0xFF);
    _sendBuffer[7] = (uint8_t)((clientCRC >> 8) & 0xFF);

    // Allocate memory for receive buffer:
    _requestedBytes = (uint8_t)(regCount * 2);
    free(ModbusRTU::receiveBuffer);
    ModbusRTU::receiveBuffer = (uint8_t *)calloc(_requestedBytes + 5, sizeof(uint8_t));

    // Send to modbus server, then listen:
    ModbusRTU::send();
    ModbusRTU::receive();
}

uint16_t ModbusRTU::appendCRC(uint8_t *data)
{
    uint16_t crc = 0xFFFF;
    for (uint16_t i = 0; i < 6; i++)
    {
        crc ^= data[i];
        for (uint8_t j = 0; j < 8; j++) 
        { 
            if (crc & 0b1)
            {
                crc >>= 1;
                crc ^= 0xA001; // Polynomial
            }
            else crc >>= 1;
        }
    }
    return crc;
}

void ModbusRTU::send()
{ HAL_UART_Transmit(_serial, _sendBuffer, 8, HAL_MAX_DELAY); }
void ModbusRTU::receive()
{
    HAL_UART_Receive(_serial, receiveBuffer, _requestedBytes + 5, 100);
    // __STM32flipGPIO(PC13);
}