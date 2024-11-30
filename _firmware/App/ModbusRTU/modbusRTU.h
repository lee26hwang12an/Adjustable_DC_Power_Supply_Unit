#ifndef _MODBUSRTU_H_
#define _MODBUSRTU_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#include "main.h"

class ModbusRTU
{
public:
    ModbusRTU(UART_HandleTypeDef *hserial);

public:

private:
    UART_HandleTypeDef *_serial;

public:

private:

};


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MODBUSRTU_H_ */