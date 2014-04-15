"""
 * FloydWarshall.py
 *
 * Implementation of Floyd Warshall Algorithm
 * 
 * See README for details
 * 
 * by:
 *    Ananth Murthy
 * 	  Chandan Yeshwanth
 * 
 * on:
 * 	  14th April 2014
 * 
"""

import sys 


# recursive function to obtain the path as a string
def obtainPath(i, j):
    if dist[i][j] == float("inf"):
        return " no path to "
    if parent[i][j] == i:
        return " "
    else :
        return obtainPath(i, parent[i][j]) + str(parent[i][j]+1) + obtainPath(parent[i][j], j)


if len(sys.argv) < 2:
	print "Check README for usage."
	sys.exit(-1)
	
try:	
	fil = open(sys.argv[1], "r")
except IOError:
	print "File not found."
	sys.exit(-1)


# no of vertices
V = int(fil.readline().strip())

# array of shortest path distances 
dist = []

# array of shortest paths
parent = []

# no of edges
E = int(fil.readline().strip())




# initialize to infinity
for i in range (0, V):
    dist.append([])
    parent.append([])
    for j in range (0, V):
        dist[i].append(float("inf"))
        parent[i].append(0)




# read edges from input file and store
for i in range (0,E):
    t = fil.readline().strip().split()
    x = int(t[0]) - 1
    y = int(t[1]) - 1
    w = int(t[2])
    dist[x][y] = w
    parent[x][y] = x


# path from vertex to itself is set to 0
for i in range (0,V):
    dist[i][i] = 0



# initialize the path matrix
for i in range (0,V):
    for j in range (0,V):
        if dist[i][j] == float("inf"):
            parent[i][j] = 0
        else:
            parent[i][j] = i



# actual floyd warshall algorithm
for k in range(0,V):
    for i in range(0,V):
        for j in range(0,V):
            if dist[i][j] > dist[i][k] + dist[k][j]:
                dist[i][j] = dist[i][k] + dist[k][j]
                parent[i][j] = parent[k][j]
                
                
                
# check for negative cycles
for i in range (0,V):
    if dist[i][i] != 0:
        print "Negative cycle at : ", i+1
        sys.exit() 


# display final paths
print "All Pairs Shortest Paths : \n"

# display shortest paths 
for i in range (0,V):
    print
    for j in range (0,V):
        print "From :", i+1, " To :", j+1
        print "Path :", str(i+1) + obtainPath(i,j) + str(j+1)
        print "Distance :", dist[i][j]
        print 

fil.close()
