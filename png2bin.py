
import os
import sys

import numpy as np

from PIL import Image
from struct import pack

default_img_dir = "img"
default_bin_dir = "bin"
default_size_dir = "sz"
current_dir = os.getcwd()

input_img = "Bagira.png"
output_bin = "Bagira.bin"

for arg in sys.argv[1:]:
	if "--in=" in arg:
		input_img = arg.split("=")[-1]
	elif  "--out" in arg:
		output_bin = arg.split("=")[-1]
	else:
		print("Invalid argument: {}".format(arg))



#image_in_filename = "images/baboon.png"
#image_out_filename = "baboon.bin"

image_in_filename = default_img_dir + "\\" + input_img
image_out_filename = default_bin_dir + "\\" + output_bin

image_handle = Image.open(image_in_filename)
image_array = np.array(image_handle)

h, w = image_array.shape

fd = open(default_size_dir + "\\" + input_img.split(".")[0] + ".size.txt", "w+")
fd.write("{} {}".format(w, h))
fd.close()


fd = open(image_out_filename, "wb")

#fd.write("{}\n".format(w))
#fd.write("{}\n".format(h))


tmp_str = b""

for i in image_array:
	for j in i:
#		tmp_str = tmp_str + "{} ".format(j)
		tmp_str += pack("B", j)


#fd.write(tmp_str.strip())
fd.write(tmp_str)

#fd.write("\n")
fd.close()

sys.exit(0)
