import numpy as np
from PIL import Image
import os

pixel_data = []
found_start = False

with open('Playing Card Classifier Model/log_white_led/DQ.log', 'r', encoding='utf-8', errors='ignore') as file:
    for line in file:
        # skip straight to the data
        if not found_start:
            if "index: 0" in line:
                found_start = True
            continue
        else:
            if "AI" in line:
                break
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

                    # NOTE: reorder these RGB values to see which best fits the ml model and camera output
                    p0 = [G0, B0, R0]
                    p1 = [G1, B1, R1]
                    
                    pixel_data.append(p1)
                    pixel_data.append(p0)

height = 128
width = 128

data = np.array(pixel_data)
target_shape = (height, width, 3)

image_data = np.zeros((height * width, 3), dtype=np.uint8)
image_data[:len(data)] = data
image_data = image_data.reshape(target_shape)
image = Image.fromarray(image_data)
image.show()