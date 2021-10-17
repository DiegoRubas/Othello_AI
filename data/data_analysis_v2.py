#! /usr/bin/env python3
import os
import time
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

path = "data/"


data_files = [file for file in os.listdir(path) if (file.endswith(".csv") & (not file.endswith("last.csv"))) ]
data_files.sort()
max_times = [ [] for i in range(0,6) ]

for file in data_files :
    data_sample = pd.read_csv(path + "/"+file)
    

    m = data_sample.max(axis=0)

    max_times[int(file[0])-1].append(m[0])
    max_times[int(file[3])-1].append(m[1])

print("Mean times : \n")
string = ""
for i in range(0,6) :
    level = max_times[i]
    if(len(level)==0) :
        meann = 0
    else:
        meann = np.mean(level)
        
    print(str(i+1) + " >>> " + str(float(int(meann))*10**-3) + " seconds >>> " + str(level))
