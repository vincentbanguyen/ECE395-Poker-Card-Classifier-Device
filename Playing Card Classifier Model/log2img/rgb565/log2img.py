import numpy as np
from PIL import Image
import os

pixel_data = []
found_start = False

with open('Playing Card Classifier Model/log_data/C2.log', 'r', encoding='utf-8', errors='ignore') as file:
    for line in file:
        # skip straight to the data
        if not found_start:
            if "index: 0" in line:
                found_start = True
            continue
        else:
            parts = line.split(',')
            for part in parts:
                if 'data:' in part:
                    # Extract the hex after 'data:'
                    word = part.split(': ')[1].strip().zfill(8)
                    # word = [R1, G1, B1, R0, G0, B0]
                    int_val = int(word, 16)  # Convert hexadecimal string to integer

                    # Extract individual R, G, and B components
                    R0 = ((int_val >> 27) & 0b11111) << 3
                    G0 = ((int_val >> 21) & 0b111111) << 2
                    B0 = ((int_val >> 16) & 0b11111) << 3
                    R1 = ((int_val >> 11) & 0b11111) << 3
                    G1 = ((int_val >> 5) & 0b111111) << 2
                    B1 = (int_val & 0b11111) << 3

                    p0 = [R0, G0, B0]
                    p1 = [R1, G1, B1]
                    
                    pixel_data.append(p1)
                    pixel_data.append(p0)

height = 148
width = 172

# reshape into 128 x 128
new_pixel_data = [0] * 128 * 128
ml_height = 128
ml_width = 128

factor_x = width / ml_width
factor_y = height / ml_height

for i in range(128):
    for j in range (128):
        col = int(j * factor_x)
        row = int(i * factor_y)
        val = pixel_data[row * width + col]
        new_pixel_data[i * 128 + j] = val

data = np.array(new_pixel_data)
target_shape = (ml_height, ml_width, 3)

image_data = np.zeros((ml_height * ml_width, 3), dtype=np.uint8)
image_data[:len(data)] = data
image_data = image_data.reshape(target_shape)
image = Image.fromarray(image_data)
image.show()