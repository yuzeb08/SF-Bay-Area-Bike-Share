#!/usr/bin/env python
#coding = utf-8

import sys
import time
import numpy

print("Computing...")
time.sleep(0.1)

path = sys.path[0]

A = [[0 for j in range(85)] for i in range(85)]
D = [[0 for j in range(85)] for i in range(85)]
l = [[1] for i in range(85)]

with open(path + "\\matrix.csv", 'r') as matrixFile:
    for i in range(85):

        string = matrixFile.readline()
        string.strip()

        row = string.split(',')

        for j in range(85):
            A[i][j] = int(row[j])

for j in range(85):
    for i in range(85):
        D[j][j] += A[i][j]
    if D[j][j] is 0:
        D[j][j] = 1

A = numpy.array(A, dtype = float)
D = numpy.array(D, dtype = float)
l = numpy.array(l, dtype = float)

temp = D - 0.85 * A

temp = numpy.asmatrix(temp)
temp = temp.I
temp = numpy.asarray(temp)

temp = numpy.dot(D, temp)

x = numpy.dot(temp, l)

print(x)

with open(path + "\\PageRank.csv", 'w') as vcFile:
    for i in range(84):
        pass
        vcFile.write(str(x[i][0]))
        vcFile.write(",")
    vcFile.write(str(x[84][0]))

print("Complete!")