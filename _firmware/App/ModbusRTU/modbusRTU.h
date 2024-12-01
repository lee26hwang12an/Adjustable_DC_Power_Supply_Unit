#ifndef _MODBUSRTU_H_
#define _MODBUSRTU_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include "main.h"

typedef enum
{
    MODBUS_RTU_SERIAL_NON_BLOCKING = 1,
    MODBUS_RTU_SERIAL_NORMAL = 0,
    MODBUS_RTU_READ_COIL = 0x01,
    MODBUS_RTU_READ_DISCRETE_INPUTS = 0x02,
    MODBUS_RTU_READ_HOLDING_REGISTERS = 0x03,
    MODBUS_RTU_READ_INPUT_REGISTERS = 0x04,
    MODBUS_RTU_WRITE_COIL_ = 0x05,
    MODBUS_RTU_WRITE_HOLDING_REGISTER = 0x06,
    MODBUS_RTU_WRITE_COILS = 0x0F,
    MODBUS_RTU_WRITE_HOLDING_REGISTERS = 0x10,
} MODBBUS_RTU_CONST;

class ModbusRTU
{
public:
    ModbusRTU(UART_HandleTypeDef *hserial);

public:
    uint8_t *receiveBuffer;

private:
    UART_HandleTypeDef *_serial;
    uint8_t _enableNonBlocking;
    uint8_t _sendBuffer[8];
    uint8_t _requestedBytes;

public:
    void init(uint8_t nonBlocking = MODBUS_RTU_SERIAL_NORMAL);
    void request(uint8_t slaveAddress, uint8_t funcCode, uint16_t startReg, uint16_t regCount);

private:
    uint16_t appendCRC(uint8_t *data);
    void send();
    void receive();

};


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MODBUSRTU_H_ */