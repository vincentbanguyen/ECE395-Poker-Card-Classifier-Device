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
                hex_value = int(word, 16)  # Convert hexadecimal string to integer

                # Extract individual R, G, and B components
                R0 = (hex_value >> 27) & 0b11111
                G0 = (hex_value >> 21) & 0b111111
                B0 = (hex_value >> 16) & 0b11111
                R1 = (hex_value >> 11) & 0b11111
                G1 = (hex_value >> 5) & 0b111111
                B1 = hex_value & 0b11111

                # Combine components into RGB565 pixel values
                pixel_1 = (R0 << 11) | (G0 << 5) | B0
                pixel_2 = (R1 << 11) | (G1 << 5) | B1

                # Print the RGB565 values
                print(f"Pixel 0: R1={R0}, G1={G0}, B1={B0}")
                print(f"Pixel 1: R2={R1}, G2={G1}, B2={B1}")

                p0 = [R0, G0, B0]
                p1 = [R1, G1, B1]
                
                pixel_data.append(p1)
                pixel_data.append(p0)

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