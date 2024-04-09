#include "stm32h7xx_hal.h"
#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>
void lcd_send_cmd (char cmd);
void lcd_send_data (char data);
void lcd_init (I2C_HandleTypeDef *p_hi2c);
void lcd_send_string (char *str);
void lcd_clear();
