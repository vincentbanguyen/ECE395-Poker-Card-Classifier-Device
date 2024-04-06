import numpy as np
from PIL import Image

pixel_data = []
with open('log2img/ycbcr/puttyExposure2.log', 'r', encoding='utf-8', errors='ignore') as file:
    for line in file:
        parts = line.split(',')
        for part in parts:
            if 'data:' in part:
                # Extract the hex after 'data:'
                word = part.split(': ')[1].strip().zfill(8)
                # word = [y0, cb, y1, cr]
                cb = int(word[2:4], 16)
                cr = int(word[6:8], 16)
                y0 = int(word[0:2], 16)
                y1 = int(word[4:6], 16)
                p1 = [y0, cb, cr]
                p2 = [y1, cb, cr]
                pixel_data.append(p2)
                pixel_data.append(p1)

# Define the YCbCr to RGB conversion function
def ycbcr_to_rgb(YCbCr):
    Y = YCbCr[0]
    Cb = YCbCr[1]
    Cr = YCbCr[2]

    R = Y + 1.402 * (Cr - 128)
    G = Y - 0.344136 * (Cb - 128) - 0.714136 * (Cr - 128)
    B = Y + 1.772 * (Cb - 128)

    R = max(0, min(255, int(R)))
    G = max(0, min(255, int(G)))
    B = max(0, min(255, int(B)))

    return (R, G, B)

# Convert YCbCr to RGB for each pixel
rgb_data = []
for pixel in pixel_data:
    rgb = ycbcr_to_rgb(pixel)
    rgb_data.append(rgb)

data = np.array(rgb_data)
target_shape = (146, 174, 3)

image_data = np.zeros((146 * 174, 3), dtype=np.uint8)
image_data[:len(data)] = data
image_data = image_data.reshape(target_shape)
image = Image.fromarray(image_data)
image.show()

file_path = '2spade.jpg'
image.save(file_path)