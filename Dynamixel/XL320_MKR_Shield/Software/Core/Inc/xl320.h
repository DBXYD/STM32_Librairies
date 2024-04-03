/*
 * xl320.h
 *
 *  Created on: Apr 3, 2024
 *      Author: nicolas
 *      From :
 *      	https://emanual.robotis.com/docs/en/dxl/protocol2/
 *      	https://emanual.robotis.com/docs/en/dxl/x/xl320/
  */

#ifndef INC_XL320_H_
#define INC_XL320_H_

#include "main.h"

////////// EEPROM ///////////
#define XL320_REG_MODEL_NUMBER            	0
#define XL320_REG_VERSION                 	2
#define XL320_REG_XL_ID                   	3
#define XL320_REG_BAUD_RATE               	4	//0: 9600, 1:57600, 2:115200, 3:1Mbps
#define XL320_REG_RETURN_DELAY_TIME       	5
#define XL320_REG_CW_ANGLE_LIMIT          	6
#define XL320_REG_CCW_ANGLE_LIMIT         	8
#define XL320_REG_SYSTEM_DATA2            	10
#define XL320_REG_CONTROL_MODE            	11
#define XL320_REG_LIMIT_TEMPERATURE       	12
#define XL320_REG_LOWER_LIMIT_VOLTAGE     	13
#define XL320_REG_UPPER_LIMIT_VOLTAGE     	14
#define XL320_REG_MAX_TORQUE              	15
#define XL320_REG_RETURN_LEVEL            	17
#define XL320_REG_ALARM_SHUTDOWN          	18

////////// RAM ///////////
#define XL320_REG_TORQUE_ENABLE           	24
#define XL320_REG_LED                     	25
#define XL320_REG_D_GAIN                  	27
#define XL320_REG_I_GAIN                  	28
#define XL320_REG_P_GAIN                  	29
#define XL320_REG_GOAL_POSITION           	30
#define XL320_REG_GOAL_SPEED              	32
#define XL320_REG_GOAL_TORQUE             	35
#define XL320_REG_PRESENT_POSITION        	37
#define XL320_REG_PRESENT_SPEED           	39
#define XL320_REG_PRESENT_LOAD            	41
#define XL320_REG_PRESENT_VOLTAGE         	45
#define XL320_REG_PRESENT_TEMPERATURE     	46
#define XL320_REG_REGISTERED_INSTRUCTION  	47
#define XL320_REG_MOVING                  	49
#define XL320_REG_HARDWARE_ERROR_STATUS   	50
#define XL320_REG_PUNCH                   	51

////////// INSTRUCTION ///////////
#define XL320_INST_PING                    	1
#define XL320_INST_READ_DATA               	2
#define XL320_INST_WRITE_DATA              	3
#define XL320_INST_REG_WRITE               	4
#define XL320_INST_ACTION                  	5
#define XL320_INST_FACTORY_RESET           	6
#define XL320_INST_REBOOT                  	8
#define XL320_INST_STATUS                  	85
#define XL320_INST_SYNC_READ               	130
#define XL320_INST_SYNC_WRITE              	131
#define XL320_INST_BULK_READ               	146
#define XL320_INST_BULK_WRITE       		147

////////// HEADER ///////////
#define XL320_HEADER_1						0xFF
#define XL320_HEADER_2						0xFF
#define XL320_HEADER_3						0xFD
#define XL320_RSRV							0x00

////////// CTRL MODE ///////////
#define XL320_WHEEL_MODE					1
#define XL320_JOIN_MODE						2	// Default

////////// LED ///////////
#define XL320_LED_OFF 						0
#define XL320_LED_RED 						1
#define XL320_LED_GREEN 					2
#define XL320_LED_YELLOW					3
#define XL320_LED_BLUE						4
#define XL320_LED_PURPLE					5
#define XL320_LED_CYAN						6
#define XL320_LED_WHITE						7

////////// UART RX TX Mode  ///////////
#define XL320_UART_RX						RESET
#define XL320_UART_TX						SET
#define XL320_CRC_LENGTH					2

typedef struct __XL320_HandleTypeDef
{											// Default	Min 	Max
	UART_HandleTypeDef *huart;
	GPIO_TypeDef *tx_En_Port;
	uint16_t tx_En_Pin;
	uint16_t model_number;					// 350
	uint8_t firmware_version;				// -
	uint8_t id;								// 1		0		252
	uint8_t baudrate;						// 3		0		3
	uint8_t	return_delay_time;				// 250		0		254
	uint8_t CW_angle_limit;					// 0		0		1023
	uint8_t CCW_angle_limit;				// 1023		0		1023
	uint8_t control_mode;					// 2		1		2
	uint8_t temperature_limit;				// 65		0		150
	uint8_t min_voltage_limit;				// 60		50		250
	uint8_t max_voltage_limit;				// 90		50		250
	uint16_t max_torque;					// 1023		0		1023
	uint8_t status_return_level;			// 2		0		2
	uint8_t shutdown_error_information;		// 3		0		7
	uint16_t crc;
	uint8_t tx_buffer[64];
	uint8_t tx_data_length;
	uint8_t rx_buffer[64];
	uint8_t rx_data_length;
} __XL320_HandleTypeDef;

extern __XL320_HandleTypeDef hxl320;

XL320_Init(__XL320_HandleTypeDef *XL320_Handle, UART_HandleTypeDef *huart, GPIO_TypeDef *TxEnPort, uint16_t TxEnPin, uint8_t id, uint8_t baudrate);
XL320_Set_UART_RxTxMode(__XL320_HandleTypeDef *XL320_Handle, GPIO_PinState mode);
XL320_Write_Data(__XL320_HandleTypeDef *XL320_Handle, uint16_t Address, uint16_t Value);
//XL320_Read_Data(__XL320_HandleTypeDef *XL320_Handle);
XL320_Set_Position(__XL320_HandleTypeDef *XL320_Handle, uint16_t position);
XL320_Set_Speed(__XL320_HandleTypeDef *XL320_Handle, uint16_t speed);
XL320_Set_Torque_Limit(__XL320_HandleTypeDef *XL320_Handle, uint16_t torque_limit);
XL320_Set_Led_Color(__XL320_HandleTypeDef *XL320_Handle, uint16_t color);
//XL320_Set_ID(__XL320_HandleTypeDef *XL320_Handle);
//XL320_Set_Baudrate(__XL320_HandleTypeDef *XL320_Handle);
XL320_Update_CRC(__XL320_HandleTypeDef *XL320_Handle);

#endif /* INC_XL320_H_ */
