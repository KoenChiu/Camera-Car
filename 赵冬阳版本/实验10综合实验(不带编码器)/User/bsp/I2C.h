#ifndef __I2C_H__
#define __I2C_H__ 

void I2C_Configuration(void);
void I2C_Start(void);/*I2C������������*/ 
void I2C_Stop(void);/*I2C�����ͷź���*/
uint8_t I2C_WaitAck(void);/*I2C���߼��ӻ�Ӧ����*/
void I2C_SendByte(uint8_t _ucByte);/*I2C����д���ݺ���*/
uint8_t I2C_ReadByte(void);
void I2C_Ack(void);
void I2C_NAck(void);
int I2C_WriteByte( uint16_t WriteAddress , uint8_t SendByte) ;
uint8_t I2C_ReadOneByte(uint8_t Address);

#endif	 






















