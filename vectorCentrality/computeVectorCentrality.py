#!/usr/bin/env python
#coding = utf-8

import sys
import time
import numpy

print("Computing...")
time.sleep(0.1)

path = sys.path[0]

A = [[0 for j in range(85)] for i in range(85)]
x = [[1] for i in range(85)]

with open(path + "\\matrix.csv", 'r') as matrixFile:
    for i in range(85):

        string = matrixFile.readline()
        string.strip()

        row = string.split(',')

        for j in range(85):
            A[i][j] = int(row[j])

A = numpy.array(A, dtype = float)
x = numpy.array(x, dtype = float)

u0 = x
v0 = numpy.dot(A,u0)
m0 = numpy.max(v0)

u = v0 / m0
v = numpy.dot(A,u)
m = numpy.max(v)

while abs(m - m0) > 0.00001:
    u0 = u
    v0 = v
    m0 = m

    u = v0 / m0
    v = numpy.dot(A,u)
    m = numpy.max(v)

x = u / u.sum()

print(x)

with open(path + "\\vectorCentrality.csv", 'w') as vcFile:
    for i in range(84):
        pass
        vcFile.write(str(x[i][0]))
        vcFile.write(",")
    vcFile.write(str(x[84][0]))

print("Complete!")