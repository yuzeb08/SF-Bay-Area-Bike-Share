#!/usr/bin/env python
#coding = utf-8

import sys
import time
import numpy

print("Computing...")
time.sleep(0.1)

path = sys.path[0]

A = [[0 for j in range(85)] for i in range(85)]

with open(path + "\\matrix.csv", 'r') as matrixFile:
    for i in range(85):

        string = matrixFile.readline()
        string.strip()

        row = string.split(',')

        for j in range(85):
            A[i][j] = int(row[j])

betweennessCentrality = [0.0 for i in range(85)]

for centralVertex in range(85):
    tree = [[False for j in range(85)] for i in range(85)]
    distance = [-1 for i in range(85)]
    weight = [0 for i in range(85)]
    x = [1.0 for i in range(85)]

    queue0 = []
    queue = []

    distance[centralVertex] = 0
    weight[centralVertex] = 1
    queue0.append(centralVertex)

    while True:
        if len(queue0) is 0:
            break
        for start in queue0:
            for goal in range(85):
                if A[goal][start] > 0:
                    if distance[goal] is -1:
                        tree[goal][start] = True
                        distance[goal] = distance[start] + 1
                        weight[goal] = weight[start] * A[goal][start]
                        queue.append(goal)
                    elif distance[goal] is distance[start] + 1:
                        tree[goal][start] = True
                        weight[goal] += weight[start] * A[goal][start]
                    else:
                        pass
        queue0 = queue
        queue = []

    dcount = max(distance) - 1
    while dcount >= 0:
        for start in range(85):
            if distance[start] is dcount:
                for goal in range(85):
                    if tree[goal][start] is True:
                        x[start] += weight[start] * A[goal][start] / weight[goal]
        dcount -= 1

    for i in range(85):
        betweennessCentrality[i] += x[i]

print(betweennessCentrality)

with open(path + "\\betweennessCentrality.csv", 'w') as bcFile:
    for i in range(84):
        pass
        bcFile.write(str(betweennessCentrality[i]))
        bcFile.write(",")
    bcFile.write(str(betweennessCentrality[84]))

print("Complete!")