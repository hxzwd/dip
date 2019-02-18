
import os
import sys

import numpy as np
from matplotlib import pyplot as plt

default_hist_dir = "hist"
input_hist = "baboon_hist.txt"
out_hist = "baboon_hist.png"

for arg in sys.argv[1:]:
	if "--in=" in arg:
		input_hist = arg.split("=")[-1]
	elif "--out=" in arg:
		out_hist = arg.split("=")[-1]
	else:
		print("Invalid argument: {}".format(arg))

full_path = default_hist_dir + "//" + input_hist
full_out_path = default_hist_dir + "//" + out_hist

handle = open(full_path, "r")
data = handle.readlines()
handle.close()

hist_array = [ int(i.strip()) for i in data ]

x_ticks = np.arange(0, len(hist_array))

hist = plt.plot(x_ticks, hist_array)
fig = hist[0].figure
fig.savefig(full_out_path)

