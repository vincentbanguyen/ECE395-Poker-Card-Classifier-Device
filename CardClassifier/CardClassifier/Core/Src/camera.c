#include "camera.h"
#include "main.h"
#include <stdio.h>
#include <string.h>
extern UART_HandleTypeDef huart4;
extern DCMI_HandleTypeDef hdcmi;
DCMI_HandleTypeDef *sp_hdcmi = &hdcmi;
//DCMI_HandleTypeDef *sp_hdcmi;
//DMA_HandleTypeDef  *sp_hdma_dcmi;
I2C_HandleTypeDef  *sp_hi2c;
uint32_t    s_destAddressForContiuousMode;
uint32_t ov7670_write(uint8_t regAddr, uint8_t data)
{
  uint16_t SLAVE_ADDR = 0x42;
  HAL_StatusTypeDef ret;
  uint8_t buffer[2] = {regAddr, data};
  ret = HAL_I2C_Master_Transmit(sp_hi2c, 0x42, &buffer, 2, HAL_MAX_DELAY);
  char temp[100];
  sprintf(temp, "Write Status: %d\r\n", ret);
  HAL_UART_Transmit(&huart4,temp,strlen(temp),10);
//  sprintf(temp, "Data: %x is now written into address: %x\r\n",data, regAddr);
  HAL_UART_Transmit(&huart4,temp,strlen(temp),10);
  return ret;
}

uint32_t ov7670_read(uint8_t regAddr, uint8_t *data)
{
  HAL_StatusTypeDef ret;
  uint16_t SLAVE_ADDR = 0x42;
  ret = HAL_I2C_Master_Transmit(sp_hi2c, 0x43, &regAddr, 1, HAL_MAX_DELAY);
  char buffer [100];
  sprintf(buffer, "Read_Transmit Status: %d\r\n", ret);
  HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
  ret = HAL_I2C_Master_Receive(sp_hi2c, 0x43, data, 1, HAL_MAX_DELAY);
  sprintf(buffer, "Read_Receive Status: %d\r\n", ret);
  HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
  sprintf(buffer, "Address: %x; Data: %x\r\n", regAddr, *data);
  HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
  return ret;
}

uint32_t ov7670_init(I2C_HandleTypeDef *p_hi2c)
{
//  sp_hdcmi     = p_hdcmi;
//  sp_hdma_dcmi = p_hdma_dcmi;
  sp_hi2c      = p_hi2c;
 // s_destAddressForContiuousMode = 0;

  HAL_GPIO_WritePin(CAM_RST_GPIO_Port, CAM_RST_Pin, GPIO_PIN_RESET);
  HAL_Delay(100);
  HAL_GPIO_WritePin(CAM_RST_GPIO_Port, CAM_RST_Pin, GPIO_PIN_SET);
  HAL_Delay(100);
  char temp[100];
  sprintf(temp, "Initializing OV7670...\r\n");
  ov7670_write(0x12, 0x80);  // RESET
  HAL_Delay(100);
  HAL_UART_Transmit(&huart4,temp,strlen(temp),10);
  HAL_Delay(100);
  uint8_t buffer[4];
  ov7670_read(0x0F, buffer);
  HAL_Delay(100);


  return 1;
}

//DCMI Data Transfer
static uint32_t s_dstAddress;

uint32_t ov7670_stopCap()
{
  char buffer [100];
  HAL_StatusTypeDef ret;
  ret = HAL_DCMI_Stop(sp_hdcmi);
  s_dstAddress = 0;
  return 0;
}

uint32_t ov7670_startCap(uint32_t destAddress)
{
  HAL_StatusTypeDef ret;
  ov7670_stopCap();
  /* note: continuous mode automatically invokes DCMI, but DMA needs to be invoked manually */
  s_dstAddress = destAddress;
  ret = HAL_DCMI_Start_DMA(sp_hdcmi,1, destAddress, OV7670_QVGA_WIDTH * OV7670_QVGA_HEIGHT / 2); //mode 1 for single frame
  ov7670_stopCap();
  char buffer [100];
  sprintf(buffer, "Return code: %d\r\n", ret);
  HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
  return 0;
}

void Resize_to_128(uint32_t* inputImg, uint32_t* outputImg) {
    float factor_x = 172.0 / 128.0;
    float factor_y = 148.0 / 128.0;

    for (int i = 0; i < 128; i++) {
        for (int j = 0; j < 128; j+=2) { // Increment by 2 since each inputImg element handles 2 pixels
            int col = (int)(j * factor_x); // Calculate the column in the input image
            int row = (int)(i * factor_y); // Calculate the row in the input image

            // Calculate the position in the input image
            // Considering that each uint32_t has two RGB565 pixels packed
            int inputIndex = (row * 172 + col) / 2;

            uint32_t Pixel = inputImg[inputIndex];
            // Place the processed pixels in the output image
            outputImg[(i * 128 + j) / 2] = Pixel;
        }
    }
}


void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
  if(s_dstAddress != 0) {
    HAL_DMA_Start_IT(hdcmi->DMA_Handle, (uint32_t)&hdcmi->Instance->DR, s_dstAddress, OV7670_QVGA_WIDTH * OV7670_QVGA_HEIGHT / 2);
  }
}
