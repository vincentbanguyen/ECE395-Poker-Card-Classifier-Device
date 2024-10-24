
/**
  ******************************************************************************
  * @file    app_x-cube-ai.c
  * @author  X-CUBE-AI C code generator
  * @brief   AI program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

 /*
  * Description
  *   v1.0 - Minimum template to show how to use the Embedded Client API
  *          model. Only one input and one output is supported. All
  *          memory resources are allocated statically (AI_NETWORK_XX, defines
  *          are used).
  *          Re-target of the printf function is out-of-scope.
  *   v2.0 - add multiple IO and/or multiple heap support
  *
  *   For more information, see the embeded documentation:
  *
  *       [1] %X_CUBE_AI_DIR%/Documentation/index.html
  *
  *   X_CUBE_AI_DIR indicates the location where the X-CUBE-AI pack is installed
  *   typical : C:\Users\<user_name>\STM32Cube\Repository\STMicroelectronics\X-CUBE-AI\7.1.0
  */

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#if defined ( __ICCARM__ )
#elif defined ( __CC_ARM ) || ( __GNUC__ )
#endif

/* System headers */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "app_x-cube-ai.h"
#include "main.h"
#include "ai_datatypes_defines.h"
#include "network.h"
#include "network_data.h"

/* USER CODE BEGIN includes */
#include "lcd.h"
/* USER CODE END includes */

/* IO buffers ----------------------------------------------------------------*/
AI_ALIGNED(4) float data_in_1[AI_NETWORK_IN_1_SIZE];
AI_ALIGNED(4) float data_out_1[AI_NETWORK_OUT_1_SIZE];
char buffer[100];
extern UART_HandleTypeDef huart4;
//#if !defined(AI_NETWORK_INPUTS_IN_ACTIVATIONS)
//AI_ALIGNED(4) ai_i8 data_in_1[AI_NETWORK_IN_1_SIZE_BYTES];
//ai_i8* data_ins[AI_NETWORK_IN_NUM] = {
//data_in_1
//};
//#else
//ai_i8* data_ins[AI_NETWORK_IN_NUM] = {
//NULL
//};
//#endif
//
//#if !defined(AI_NETWORK_OUTPUTS_IN_ACTIVATIONS)
//AI_ALIGNED(4) ai_i8 data_out_1[AI_NETWORK_OUT_1_SIZE_BYTES];
//ai_i8* data_outs[AI_NETWORK_OUT_NUM] = {
//data_out_1
//};
//#else
//ai_i8* data_outs[AI_NETWORK_OUT_NUM] = {
//NULL
//};
//#endif

/* Activations buffers -------------------------------------------------------*/

AI_ALIGNED(32)
static uint8_t pool0[AI_NETWORK_DATA_ACTIVATION_1_SIZE];

ai_handle data_activations0[] = {pool0};

/* AI objects ----------------------------------------------------------------*/

static ai_handle network = AI_HANDLE_NULL;

static ai_buffer* ai_input;
static ai_buffer* ai_output;

static void ai_log_err(const ai_error err, const char *fct)
{
  /* USER CODE BEGIN log */
  if (fct)
    {sprintf(buffer, "TEMPLATE - Error (%s) - type=0x%02x code=0x%02x\r\n", fct,
        err.type, err.code);
  HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
  HAL_Delay(20);
    }
  else {
    sprintf(buffer, "TEMPLATE - Error - type=0x%02x code=0x%02x\r\n", err.type, err.code);
    HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
    HAL_Delay(20);
  }
  do {} while (1);
  /* USER CODE END log */
}

static int ai_boostrap(ai_handle *act_addr)
{
  ai_error err;

  /* Create and initialize an instance of the model */
  err = ai_network_create_and_init(&network, act_addr, NULL);
  if (err.type != AI_ERROR_NONE) {
    ai_log_err(err, "ai_network_create_and_init");
    return -1;
  }

  ai_input = ai_network_inputs_get(network, NULL);
  ai_output = ai_network_outputs_get(network, NULL);
  for (int i = 0; i < sizeof(data_out_1); ++i) {
	  data_out_1[i] = 0;
  }
//#if defined(AI_NETWORK_INPUTS_IN_ACTIVATIONS)
//  /*  In the case where "--allocate-inputs" option is used, memory buffer can be
//   *  used from the activations buffer. This is not mandatory.
//   */
//  for (int idx=0; idx < AI_NETWORK_IN_NUM; idx++) {
//	data_ins[idx] = ai_input[idx].data;
//  }
//#else
//  for (int idx=0; idx < AI_NETWORK_IN_NUM; idx++) {
//	  ai_input[idx].data = data_ins[idx];
//  }
//#endif
//
//#if defined(AI_NETWORK_OUTPUTS_IN_ACTIVATIONS)
//  /*  In the case where "--allocate-outputs" option is used, memory buffer can be
//   *  used from the activations buffer. This is no mandatory.
//   */
//  for (int idx=0; idx < AI_NETWORK_OUT_NUM; idx++) {
//	data_outs[idx] = ai_output[idx].data;
//  }
//#else
//  for (int idx=0; idx < AI_NETWORK_OUT_NUM; idx++) {
//	ai_output[idx].data = data_outs[idx];
//  }
//#endif

  return 0;
}

static int ai_run(const void *in_data, void *out_data)
{
  ai_i32 batch;
  ai_input[0].data = AI_HANDLE_PTR(in_data);
  ai_output[0].data = AI_HANDLE_PTR(out_data);
  batch = ai_network_run(network, &ai_input[0], &ai_output[0]);
  if (batch != 1) {
	  	sprintf(buffer, "Batch Mismatch! Batch number rn is: %d",batch);
	  	HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
	  	HAL_Delay(20);
    ai_log_err(ai_network_get_error(network),
        "ai_network_run");
    return -1;
  }

  return 0;
}

/* USER CODE BEGIN 2 */
int acquire_and_process_data(void)
{
  HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
  HAL_Delay(20);
  extern uint32_t imagedata128[128 * 128 /2];
  for (int i = 0; i < 128 * 128 / 2; ++i) {
          uint32_t pixels = imagedata128[i];

          // Extract first RGB565 pixel components (upper 16 bits)
          uint8_t red1 = (pixels >> 27) & 0x1F;
          uint8_t green1 = (pixels >> 21) & 0x3F;
          uint8_t blue1 = (pixels >> 16) & 0x1F;

          // Extract second RGB565 pixel components (lower 16 bits)
          uint8_t red2 = (pixels >> 11) & 0x1F;
          uint8_t green2 = (pixels >> 5) & 0x3F;
          uint8_t blue2 = pixels & 0x1F;

          // Scale to 8-bit components
          uint8_t red1_8bit = (red1 * 255) / 31;
          uint8_t green1_8bit = (green1 * 255) / 63;
          uint8_t blue1_8bit = (blue1 * 255) / 31;

          uint8_t red2_8bit = (red2 * 255) / 31;
          uint8_t green2_8bit = (green2 * 255) / 63;
          uint8_t blue2_8bit = (blue2 * 255) / 31;

          // Place the 8-bit components in the AI input buffer
          // Assuming the AI expects RGB values in separate consecutive bytes

          // Store first pixel
          data_in_1[6*i] = (float) green2_8bit / 255;
          data_in_1[6*i+1] = (float) blue2_8bit / 255;
          data_in_1[6*i+2] = (float) red2_8bit / 255;
          data_in_1[6*i+3] = (float) green1_8bit / 255;
          data_in_1[6*i+4] = (float) blue1_8bit / 255;
          data_in_1[6*i+5] = (float) red1_8bit /255;
  }
  return 0;
}

int post_process(void)
{
  /* process the predictions
  */
//	for (int idx=0; idx < AI_NETWORK_OUT_NUM; idx++ )
//	  {
//		ai_output[idx].data = data_outs[idx];
//	  }
	extern UART_HandleTypeDef huart4;
	char buffer [100];
//	for (int i = 0; i < sizeof(data_out_1); ++i) {
//		int shift = (i % 4) * 8;
//		output[i/4] += (data_out_1[i] << shift);
//	}
//	float temp = 0;
//	for (int i = 0; i < 54; ++i) {
////		ai_i8 bytes[4];
////		uint32_t temp = ((uint32_t)bytes[0] << 24) | ((uint32_t)bytes[1] << 16) | ((uint32_t)bytes[2] << 8) | bytes[3];
////		memcpy(&output[i], &temp, sizeof(output[i]));
//		temp += data_out_1[i];
//	  	sprintf(buffer, "index: %d, data: %f\r\n",i, data_out_1[i]);
//	  	HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
//	  	HAL_Delay(20);
//	}
//  	sprintf(buffer, "temp: %f\r\n", temp);
  	HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
  	HAL_Delay(20);
  	int index = indexlargest(data_out_1, 54);
  	char rank[100];
  	char suit[100];
  	int offset = -1;
  	sprintf(buffer, "index :%d \r\n", index);
  	HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
  	HAL_Delay(20);
  	if (index >= 1 && index <= 13) {
  		strcpy(suit, "Clubs");
  	} else if (index >= 14 && index <= 26) {
  		strcpy(suit, "Diamonds");
  	} else if (index >= 27 && index <= 39) {
  		strcpy(suit, "Hearts");
  	} else if (index >= 40 && index <= 52) {
  		strcpy(suit, "Spades");
  	} else if (index == 0) {
  	  lcd_clear();
  	  lcd_send_string("Black Joker");
  	  return 0;
  	} else {	//index == 53, red Jocker
  		lcd_clear();
    	lcd_send_string("Nothing");
    	return 0;
  	}
  	int ranknum = (index + offset) % 13;
  	switch(ranknum) {
  	case 0:
  		strcpy(rank, "Two");
		break;
  	case 1:
  		strcpy(rank, "Three");
  		break;
  	case 2:
  		strcpy(rank, "Four");
  		break;
  	case 3:
  		strcpy(rank, "Five");
  		break;
  	case 4:
  		strcpy(rank, "Six");
  		break;
  	case 5:
  		strcpy(rank, "Seven");
  		break;
  	case 6:
  		strcpy(rank, "Eight");
  		break;
  	case 7:
  		strcpy(rank, "Nine");
  		break;
  	case 8:
  		strcpy(rank, "Ace");
  		break;
  	case 9:
  		strcpy(rank, "Jack");
  		break;
  	case 10:
  		strcpy(rank, "King");
  		break;
  	case 11:
  		strcpy(rank, "Queen");
  		break;
  	case 12:
  		strcpy(rank, "Ten");
  		break;
  	}
  	sprintf(buffer, rank);
  	HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
  	HAL_Delay(20);
  	sprintf(buffer, suit);
  	HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
  	HAL_Delay(20);
  	char temp1[100] = "";
  	strcat(temp1, rank);
  	strcat(temp1, " of ");
  	strcat(temp1, suit);
	lcd_clear();
	lcd_send_string(temp1);
  	sprintf(buffer, temp1);
  	HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
  	HAL_Delay(20);
  return 0;
}

int indexlargest(const float *arr, int n) { //Find the index of the largest element of an array
    if (n <= 0) return -1; // Return -1 for an empty array

    int maxIndex = 0; // Start with the first element as the largest
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
            maxIndex = i; // Update maxIndex to the current index
        }
    }
    return maxIndex;
}
/* USER CODE END 2 */

/* Entry points --------------------------------------------------------------*/

void MX_X_CUBE_AI_Init(void)
{
    /* USER CODE BEGIN 5 */

  ai_boostrap(data_activations0);
    /* USER CODE END 5 */
}

void MX_X_CUBE_AI_Process(void)
{
    /* USER CODE BEGIN 6 */
  int res = -1;
  extern UART_HandleTypeDef huart4;
  char buffer [100];
  sprintf(buffer, "AI Process Starts, AI_NETWORK_IN_NUM: %d, data_out_size: %d, data_in_size: %d\r\n", AI_NETWORK_IN_NUM, sizeof(data_out_1), sizeof(data_in_1));
  HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
  HAL_Delay(20);
  if (network) {
      /* 1 - acquire and pre-process input data */
      res = acquire_and_process_data();
	  sprintf(buffer, "data acquired passed\r\n");
	  HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
	  HAL_Delay(20);
      /* 2 - process the data - call inference engine */
      if (res == 0) {
    	  res = ai_run(data_in_1, data_out_1);
  	  	sprintf(buffer, "ai_run passed:\r\n");
  	  	HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
  	  	HAL_Delay(20);
      }
      /* 3- post-process the predictions */
//      if (res == 0) {
        res = post_process();
	  	sprintf(buffer, "post process passed\r\n");
	  	HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
	  	HAL_Delay(20);
//      }
  }
  if (res) {
	  sprintf(buffer, "AI Failed!\r\n");
	  HAL_UART_Transmit(&huart4,buffer,strlen(buffer),10);
	  HAL_Delay(20);
  }
    /* USER CODE END 6 */
}
#ifdef __cplusplus
}
#endif
