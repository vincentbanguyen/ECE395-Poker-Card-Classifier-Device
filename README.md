
https://github.com/user-attachments/assets/9b204c32-8d50-4713-b9ab-50e7000abaa3

## Introduction ##
Our project is a poker card classifier.  The device works by first placing a card on the white slot. A picture of the card is taken when the button is pressed, and the image is processed into RGB values and fed into a neural network. The neural network outputs the probabilities of each card, and displays the most probable card on the LCD display. 
<img width="843" alt="image" src="https://github.com/user-attachments/assets/7c88376e-2691-4388-b00e-d341960cbabb">

## Specifications ## 
STM32H743VIT6 Chip
OV7670 Camera
USB-C Receptacle (USB4085)
5V to 3.3V LDO (TC1262-33)
1602 LCD Display

## Block Diagram ##
<img width="844" alt="image" src="https://github.com/user-attachments/assets/199b5f68-5d9e-4b67-b2a7-e2ddbfd516c3">
<img width="747" alt="image" src="https://github.com/user-attachments/assets/b82d395b-9e24-4555-9573-e28a7a556756">

## Design Process ##
### Step 1: Schematic and PCB Design ###
We started the project by designing our PCB which connected the STM32 microcontroller with all other components. We chose a 2-layer design for our PCB, with the front layer being grounded and the back layer being 3V3. As different chips are driven by different voltages, the board receives 5V power input from the USB-C receptacle, and 3.3V voltage is obtained from the 5V to 3.3V LDO. We decoupled both 5V and 3V3 input with decoupling capacitors, so that our design became less noise-sensitive. 

In order to effectively utilize the space on the PCB, we decided to split 24 camera pins into 4 different headers centered around the microcontroller, such that there wouldn’t be a long header occupying the entire board. The headers for the LCD display and the serial port are placed around the STM32 chip similar to the camera pins. The left part of our PCB contains three buttons, which control the BOOT pin, the reset pin, and the capture pin. All the buttons have a pull-down resistor such that the pins will be grounded when the buttons are not pressed. 
<img width="1437" alt="image" src="https://github.com/user-attachments/assets/8200666b-c56a-4c92-8eb4-250990006d3f">


Step 2: Test UART on Nucleo-Board
Configuring UART properly is very crucial to this project, as we not only need the information for debugging, but also log data from the console to generate our image. Since the OV7670 camera needs  I2C and DMCI pins, we configured UART4 to be our UART communication port with a baud rate of 115200. The TX and RX pins on the chip are connected to the RX and TX pins on the serial port to transfer data in the right direction.

Since the console doesn’t have access to printf directly, we realize printing through the sprintf function to send whatever string we need to print. Below is an example on how this sprintf method works:

Buffer is a string with the size of 100 characters, and sprintf function will define the content of the buffer variable with the desired test string we try to print. Afterwards, the HAL_UART_Transmit function will output the buffer from the uart4 port. By doing so, we accomplish printing strings that contain both characters and numbers, realizing the functionality of printf.



Step 3: Test I2C for LCD on a Nucleo-Board
LCD 1602 is the first device that needs to communicate through the I2C protocol, hence we allocate I2C2 for the LCD display. We implemented the lcd_send_cmd function to configure the lcd and the lcd_send_data function to send strings into the display. Both functions rely on the HAL_I2C_Master_Transmit function to accomplish the data transfer.

When a new string is sent to the LCD, the new string will be appended to the current content of the LCD. Therefore, we implement the lcd_clear function to clear out the screen such that only the new string would be displayed:

Step 4: Use I2C to write to Camera Registers
Similar to LCD 1602, the OV7670 - STM32 communication is realized through the I2C protocol. We implement the ov7670_write and ov7670_read functions to transfer data into / from the registers in the camera module. 


Step 5: Read Camera Data Output
<img width="1125" alt="image" src="https://github.com/user-attachments/assets/adcf7ed3-2d71-4dfc-87ad-6c62fab37739">


The OV7670 has a DCMI (Digital-Camera-Interface) where it outputs 8 data signals into the chip’s DCMI. The data is temporarily stored in a 32-bit register, and a DMA request is generated. The DMA (Direct-Memory-Access) controller then transfers the data into our requested memory address, which is our imagedata buffer. 

We used UART to print and read our imagedata buffer index by index into the console. 
Our camera outputs in RGB565 format. This means the first 5 bits are red, next 6 bits are green, and the last 5 bits are blue. Each index is a 32-bit word, so each index is 2 pixels and each pixel is 2 bytes large.


Step 6: Convert Card Log into a JPG image
In order to see the camera output image, we have to convert the RGB log into a JPG image. We did this by creating a python script called “log2img.py” and the pillow library to interpret each line in the log as 2 pixels with RGB values, and arranging them into a 128 by 128 array. The Pillow library then can convert this array into a JPG image that we can view.

Step 7: Assess Image and Adjust Camera registers for Desired Image Quality
<img width="1089" alt="image" src="https://github.com/user-attachments/assets/7e6837b7-9f34-4046-8f6f-984d033da7bd">


After getting a viewable image from the log, we adjusted the registers to produce an image RGB565 format and in QCIF (176 x 144) resolution. At first, the color in our images seemed to be incorrect, and we referenced another camera project that adjusted the color matrix registers in the camera. Writing their same values seemed to correctly calibrate our outputs, and now we are able to distinguish black and red cards.

Step 8: Collect Logs of All Cards and Create Dataset
When using the device, the captured photos will have slight variations due to the environment. Since we only collected a single image for each card, it’s important to create synthetic images with slight variations by slightly transforming each card image with some rotation, and brightness, and contrast. Pytorch has helpful transform functions to do so. 

Step 9: Design Convolutional Neural Network
<img width="752" alt="image" src="https://github.com/user-attachments/assets/3adf3048-00e7-4bf5-b37b-60ee80eca519">

The image above is a popular architecture for image classification, so our project implemented a similar but simpler design since it was important to keep our model as small as possible in order to fit onto the chip. We aimed to keep it below 1 MB. 
<img width="1373" alt="image" src="https://github.com/user-attachments/assets/bba66d5f-e377-4880-8fee-41d8ad90108b">

Our architecture above accepts a 128x128 image tensor, and passes through two convolution layers, and 2 fully connected layers, and outputs 54 probabilities.

Step 10: Train and Assess CNN
The basic idea of training our model was to iterate through the training dataset and input it into the neural network, and compare its prediction to the actual value, and adjust the weights to minimize loss. Doing this enough times will result in optimized weights that will more accurately predict our cards. We can then assess our model by iterating through our test dataset images and input them into the model, and see the predicted vs. actual image.
<img width="1214" alt="image" src="https://github.com/user-attachments/assets/c79b08ec-5b20-4585-8802-3a9571822d15">


Step 11: Convert Pytorch Model into TFLite Model
The STM32CubeIDE allows us to upload a TFLite Model. Since we developed our model using pytorch, we had to convert it into a Tensorflow model, then into a TensorFlow Lite model.

Step 12: Using a TFLite Model with STM32
We first uploaded the TFLITE model into STM32CubeIDE through the .ioc file. The specific steps to do this are documented on ST’s CubeAI website. After the model is uploaded, the configuration file auto generates an “app_x-cube-ai.c file” where we can interface with the model.

There are three steps within this file in order to get a prediction:

Acquire and Process:
The first step is to populate the neural network’s input buffer with normalized RGB values. Note that our order into the buffer was pixel 2 GBR and then pixel 1 GBR. 

Run Network with Input
After populating the input buffer, we call ai_run(), which will run the model’s inference code and populate the output data with the 54 probabilities. 

Post Process
We iterated through the output buffer that contained probabilities, and the largest probability is our prediction. We then print out this prediction into the LCD display.



Challenges 
The first challenge we had was when trying to perform I2C to display a string on the LCD display. The issue was that the pin headers on the nucleo-board covered the pin name, so we connected the wrong pin for SDA. 

After getting I2C to work for the LCD, we attempted to use I2C to write to the camera register. The HAL_UART_MASTER_TRANSMIT and HAL_UART_MASTER_RECEIVE kept returning an error code, but we realized that the Camera Reset should be active low instead of active high.

After correctly configuring the camera through writing to its registers, we attempted to read camera data using DCMI. The HAL_DCMI_START_DMA function is supposed to use the DMA to copy over DCMI data from the camera into our specified image_buffer, but the image_buffer didn’t seem to get populated. Online sources suggested to disable D-Cache, and we found out that VSYNC wasn’t properly soldered to the nucleo-board. The combination of these fixed our issue, and we were able to receive image data into our image buffer.

When we attempted to program the PCB, we received “No ST-Link Device Found”. We first assumed that the clone programmer was broken, and that a genuine one was needed. However, we used the multimeter to determine that the VDD pins were receiving 2.8 V instead of the required 3.3V. We realized that our decoupling schematic was incorrect, so we manually correct it onto the board. Another issue was that we forgot to power VREF, so we connected it to VDD. These two fixes allowed us to program the board.

Another challenge we had was collecting our training data for the neural network. Our approach was to manually get all of the cards log data through printing through the serial port, and converting the log data into images on a python script. A better way would have been encoding the image data and saving them all to an SD card.
