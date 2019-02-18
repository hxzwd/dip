
import os
import sys

import numpy as np

from PIL import Image
from struct import unpack

w_size = 512
h_size = 512

input_bin = "baboon_out.bin"
output_png = "baboon_out.png"

input_bin = "baboon_out_t.bin"
output_png = "baboon_out_t.png"

input_bin = "baboon_out_3.bin"
output_png = "baboon_out_3.png"


input_bin = "baboon_out_4.bin"
output_png = "baboon_out_4.png"

default_bin_dir = "bin"
default_out_bin_dir = "out_bin"
default_out_dir = "out"

input_bin = "baboon_out.bin"
output_png = "baboon_out.png"

for arg in sys.argv[1:]:
	if "--in=" in arg:
		input_bin = arg.split("=")[-1]
	elif "--out" in arg:
		output_png = arg.split("=")[-1]
	else:
		print("Invalud argument: {}".format(arg))

full_in = default_out_bin_dir + "//" + input_bin
full_out = default_out_dir + "//" + output_png

input_bin = full_in
output_png = full_out

bin_data = b""
image_array = []


handle = open(input_bin, "rb")

bin_data = handle.read()
handle.close()

for one_byte in bin_data:
#	image_array.append(unpack("B", one_byte))
	image_array.append(one_byte)

image_array = np.array(image_array, dtype = np.uint8)


#image_array = image_array.reshape(w_size, h_size)
image_array = image_array.reshape(h_size, w_size)
image_array.dtype = np.uint8

image_handle = Image.fromarray(image_array)

image_handle.save(output_png)

