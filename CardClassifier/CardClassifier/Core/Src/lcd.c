#include "lcd.h"
#include "main.h"
I2C_HandleTypeDef  *lcd_sp_hi2c;
uint16_t SLAVE_ADDRESS_LCD = 0x4E;
void lcd_send_cmd (char cmd)
{
  char data_u, data_l;
	uint8_t data_t[4];
	data_u = (cmd&0xf0);
	data_l = ((cmd<<4)&0xf0);
	data_t[0] = data_u|0x0C;  //en=1, rs=0
	data_t[1] = data_u|0x08;  //en=0, rs=0
	data_t[2] = data_l|0x0C;  //en=1, rs=0
	data_t[3] = data_l|0x08;  //en=0, rs=0
	uint16_t ret = HAL_I2C_Master_Transmit (lcd_sp_hi2c, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}

void lcd_send_data (char data)
{
	char data_u, data_l;
	uint8_t data_t[4];
	data_u = (data&0xf0);
	data_l = ((data<<4)&0xf0);
	data_t[0] = data_u|0x0D;  //en=1, rs=1
	data_t[1] = data_u|0x09;  //en=0, rs=1
	data_t[2] = data_l|0x0D;  //en=1, rs=1
	data_t[3] = data_l|0x09;  //en=0, rs=1
	HAL_I2C_Master_Transmit (lcd_sp_hi2c, SLAVE_ADDRESS_LCD,(uint8_t *) data_t, 4, 100);
}
void lcd_send_string (char *str)
{
	while (*str) {
		HAL_Delay(10);
		lcd_send_data (*str++);
	}
}

void lcd_init (I2C_HandleTypeDef* p_hi2c)
{
	lcd_sp_hi2c = p_hi2c;
	// 4 bit initialisation
	HAL_Delay(50);  // wait for >40ms
	lcd_send_cmd (0x30);
	HAL_Delay(50);  // wait for >4.1ms
	lcd_send_cmd (0x30);
	HAL_Delay(50);  // wait for >100us
	lcd_send_cmd (0x30);
	HAL_Delay(50);
	lcd_send_cmd (0x20);  // 4bit mode
	HAL_Delay(50);

  // dislay initialisation
	lcd_send_cmd (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(50);
	lcd_send_cmd (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(50);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(50);
	HAL_Delay(50);
	lcd_send_cmd (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(50);
	lcd_send_cmd (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
	lcd_send_string("");
}

void lcd_clear() {
	HAL_Delay(500);
	lcd_send_cmd (0x01);  // clear display
	HAL_Delay(1);
	lcd_send_string("");
	HAL_Delay(500);
}
