#include "stm32h7xx_hal.h"
#define _OPEN_SYS_ITOA_EXT
#include <stdio.h>
#include <stdlib.h>


#define OV7670_QVGA_WIDTH   176
#define OV7670_QVGA_HEIGHT  144


uint32_t ov7670_write(uint8_t regAddr, uint8_t data);
uint32_t ov7670_read(uint8_t regAddr, uint8_t *data);
uint32_t ov7670_init(I2C_HandleTypeDef *p_hi2c);
uint32_t ov7670_stopCap();
uint32_t ov7670_startCap(uint32_t destAddress);
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi);
