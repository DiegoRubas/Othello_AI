#! /usr/bin/env python3
import os
import time
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

path = "data/Pruning"



data_files = [file for file in os.listdir(path) if (file.endswith(".csv")) ]
data_files.sort()
mean_times = [ [] for i in range(0,6) ]

for file in data_files :
    data_sample = pd.read_csv(path + "/"+file)
    plt.plot(range(0, len(data_sample["a1"])), data_sample["a1"])
    plt.title(file[0] + " vs " +file[3])
    plt.xlabel("Tours")
    plt.ylabel(file[0])
    #plt.show()

    plt.plot(range(0, len(data_sample["a2"])), data_sample["a2"])
    plt.title(file[0] + " vs " +file[3])
    plt.xlabel("Tours")
    plt.ylabel(file[3])
    #plt.show()

    m = data_sample.mean(axis=0)

    mean_times[int(file[0])-1].append(m[0])
    mean_times[int(file[3])-1].append(m[1])

print("Mean times : \n")
for i in range(0,6) :
    level = mean_times[i]
    if(len(level)==0) :
        meann = 0
    else:
        meann = np.mean(level)
        
    print(str(i+1) + " >>> " + str(float(meann)*10**-3) + " seconds >>> " + str(level))