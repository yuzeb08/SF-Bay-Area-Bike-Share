#!/usr/bin/env python
#coding = utf-8

import sys
import time

print("Processing...")
time.sleep(0.1)

matrix = [[0 for i in range(85)] for j in range(85)]

path = sys.path[0]

with open(path + "\\trip.csv", 'r') as tripFile:

    tripFile.readline()

    while True:
        string = tripFile.readline()

        if string == "":
            break

        string = string.strip()

        record = string.split(',')

        matrix[int(record[5])][int(record[3])] += 1

    with open(path + "\\matrix.csv", 'w') as matrixFile:
        for i in range(85):

            for j in range(84):
                matrixFile.write(str(matrix[i][j]))
                matrixFile.write(',')

            matrixFile.write(str(matrix[i][84]))
            matrixFile.write('\n')

print("Complete!")