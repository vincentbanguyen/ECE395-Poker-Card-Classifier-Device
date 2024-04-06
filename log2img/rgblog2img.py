import numpy as np
from PIL import Image

pixel_data = []
with open('puttyExposure2.log', 'r', encoding='utf-8', errors='ignore') as file:
    for line in file:
        parts = line.split(',')
        for part in parts:
            if 'data:' in part:
                # Extract the hex after 'data:'
                word = part.split(': ')[1].strip().zfill(8)
                # word = [R1, G1, B1, R0, G0, B0]
                # r1 = int(word[0:5], 16)
                # g1 = int(word[6:13], 16)
                # b1 = int(word[14:19], 16)

                # r0 = int(word[20:6], 16)
                # g0 = int()
                # b0 = 

                p1 = [r1, g1, b1]
                p0 = [r0, g0, b0]
                
                pixel_data.append(p1)
                pixel_data.append(p0)

# Convert YCbCr to RGB for each pixel
rgb_data = []
for pixel in pixel_data:
    rgb_data.append(rgb)

data = np.array(rgb_data)
target_shape = (146, 174, 3)

image_data = np.zeros((146 * 174, 3), dtype=np.uint8)
image_data[:len(data)] = data
image_data = image_data.reshape(target_shape)
image = Image.fromarray(image_data)
image.show()