import numpy as np
from PIL import Image
import os

pixel_data = []
with open('log2img/rgb565/putty.log', 'r', encoding='utf-8', errors='ignore') as file:
    for line in file:
        parts = line.split(',')
        for part in parts:
            if 'data:' in part:
                # Extract the hex after 'data:'
                word = part.split(': ')[1].strip().zfill(8)
                # word = [R1, G1, B1, R0, G0, B0]
                print(f"word: {word}")
                hex_value = int(word, 16)

                R = (hex_value >> 16) & 0xFF
                G = (hex_value >> 8) & 0xFF
                B = hex_value & 0xFF

                R0 = (R >> 3) & 0x1F
                G0 = (G >> 2) & 0x3F
                B0 = (B >> 3) & 0x1F

                R1 = (R >> 11) & 0x1F
                G1 = (G >> 10) & 0x3F
                B1 = (B >> 11) & 0x1F

                # Print the RGB565 values
                print(f"Pixel 0: R1={R0}, G1={G0}, B1={B0}")
                print(f"Pixel 1: R2={R1}, G2={G1}, B2={B1}")

                p0 = [R0, B0, B0]
                p1 = [R1, G1, B1]
                
                pixel_data.append(p0)
                pixel_data.append(p1)

# Convert YCbCr to RGB for each pixel
# rgb_data = []
# for pixel in pixel_data:
#     rgb_data.append(pixel)

height = 148
width = 172
data = np.array(pixel_data)
target_shape = (height, width, 3)

image_data = np.zeros((height * width, 3), dtype=np.uint8)
image_data[:len(data)] = data
image_data = image_data.reshape(target_shape)
image = Image.fromarray(image_data)
image.show()