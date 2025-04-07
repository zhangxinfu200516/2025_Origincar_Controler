#ifndef __USRATX_H
#define __USRATX_H 

#include "stdio.h"
#include "sys.h"
#include "system.h"

#define DATA_STK_SIZE   512 
#define DATA_TASK_PRIO  4

#define FRAME_HEADER      0X7B //Frame_header //֡ͷ
#define FRAME_TAIL        0X7D //Frame_tail   //֡β
#define SEND_DATA_SIZE    24
#define RECEIVE_DATA_SIZE 11

/*****A structure for storing triaxial data of a gyroscope accelerometer*****/
/*****���ڴ�������Ǽ��ٶȼ��������ݵĽṹ��*********************************/
typedef struct __Mpu6050_Data_ 
{
	short X_data; //2 bytes //2���ֽ�
	short Y_data; //2 bytes //2���ֽ�
	short Z_data; //2 bytes //2���ֽ�
}Mpu6050_Data;

/*******The structure of the serial port sending data************/
/*******���ڷ������ݵĽṹ��*************************************/
typedef struct _SEND_DATA_  
{
	unsigned char buffer[SEND_DATA_SIZE];
	struct _Sensor_Str_
	{
		unsigned char Frame_Header; //1���ֽ�
		u8 Flag_Control_Enable;  // 1���ֽ�
		short X_speed;	            //2 bytes //2���ֽ�
		short Y_speed;              //2 bytes //2���ֽ�
		short Z_speed;              //2 bytes //2���ֽ�
		short Power_Voltage;        //2 bytes //2���ֽ�
		Mpu6050_Data Accelerometer; //6 bytes //6���ֽ�
		Mpu6050_Data Gyroscope;     //6 bytes //6���ֽ�	
		u8 crc;						//1���ֽ�
		unsigned char Frame_Tail;   //1 bytes //1���ֽ�
	}Sensor_Str;
}SEND_DATA;

struct Struct_UART_Tx_Data
{
	u8 Frame_Header;
	u8 Flag_Control_Enable; 
	short Now_X_speed;	//Ҫ����ն�ʹ��ʱҪ������1000������������shortת��Ϊfloat��ת����λΪ m/s
	short Now_Y_speed;	//Ҫ����ն�ʹ��ʱҪ������1000������������shortת��Ϊfloat��ת����λΪ m/s
	short Now_Z_speed;	//Ҫ����ն�ʹ��ʱҪ������1000������������shortת��Ϊfloat��ת����λΪ m/s
	short Mpu6050_Accelerometer_X_Data;
	short Mpu6050_Accelerometer_Y_Data;	
	short Mpu6050_Accelerometer_Z_Data;
	short Mpu6050_Gyroscope_X_Data;
	short Mpu6050_Gyroscope_Y_Data;
	short Mpu6050_Gyroscope_Z_Data;
	short Power_Voltage;//Ҫ����ն�ʹ��ʱҪ������1000������������shortת��Ϊfloat��ת����λΪ V
	short Encoder_Data;//Ҫ����ն�ʹ��ʱҪ������1000������������shortת��Ϊfloat��ת����λΪ V
	u8 crc;
	u8 Frame_Tail;
}__attribute__((packed));


typedef struct _RECEIVE_DATA_  
{
	unsigned char buffer[RECEIVE_DATA_SIZE];
	struct _Control_Str_
	{
		unsigned char Frame_Header; //1 bytes //1���ֽ�

		float X_speed;	            //2 bytes //2���ֽ� ���ڽ��վ���Ϊ2�ֽڣ������ת��Ϊ������
		float Y_speed;              //2 bytes //2���ֽ�	���ڽ��վ���Ϊ2�ֽڣ������ת��Ϊ������
		float Z_speed;              //2 bytes //2���ֽ�	���ڽ��վ���Ϊ2�ֽڣ������ת��Ϊ������
		u8 crc;						//1 bytes
		unsigned char Frame_Tail;   //1 bytes //1���ֽ�
	}Control_Str;
}RECEIVE_DATA;

struct Struct_UART_Rx_Data
{
	u8 Frame_Header;
	short Set_X_speed;
	short Set_Z_speed;
	u8 crc;
	u8 Frame_Tail;
}__attribute__((packed));

void data_task(void *pvParameters);
void data_transition(void);
void USART1_SEND(void);
void USART3_SEND(void);
void USART5_SEND(void);

void CAN_SEND(void);
void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);
void uart5_init(u32 bound);

int USART1_IRQHandler(void);
int USART2_IRQHandler(void);
int USART3_IRQHandler(void);
int UART5_IRQHandler(void);

float Vz_to_Akm_Angle(float Vx, float Vz);
float XYZ_Target_Speed_transition(u8 High,u8 Low);
void usart1_send(u8 data);
void usart2_send(u8 data);
void usart3_send(u8 data);
void usart5_send(u8 data);

u8 Check_Sum(unsigned char Count_Number,unsigned char Mode);


#endif

