floyd-warshall
==============

This README outlines an implementation of the Floyd Warshall algorithm by - 
	Ananth Murthy     (ananth.murthy@iiitb.org)
	Chandan Yeshwanth (chandan.yeshwanth@iiitb.org)


Contents
-----------
1. Introduction
2. Data structures used
3. Pseudocode
4. Compiling and Executing
5. Contribution
6. References


1. Introduction
---------------
The Floyd Warshall algorithm is used to find shortest paths between all pairs of vertices in a graph. It is a dynamic-programming algorithm; shortest path distances are calculated bottom up, these estimates are refined until the shortest path is obtained. Positive and zero weight cycles in the graph are ignored, and negative weight cycles are detected. 
The algorithm runs in O(V^3) time, where V is the number of vertices in the graph.



2. Data structures used
-----------------------
1. Python - adjacency and parent matrices stored using standard Python list
2. C++ - adjacency matrix is a matrix of Distance objects, implemented by class Distance. Operator overloading takes care of infinite distance values. Parent matrix stored using regular int matrix


3. Pseudocode
-------------
The Floyd Warshall Algorithm finds all-pairs shortest paths given the adjacency matrix of a graph. 
The algorithm here is from the textbook mentioned in the references section (page 695).

Given an adjacency matrix W,

	FLOYD-WARSHALL( W ):
		n = W.rows
		D(0) = W
		for k = 1 to n
			let D(k) = = [ d[i][j](k) ] be a new n x n matrix
			for i = 1 to n
				for j = 1 to n
					d[i][j](k) = min(d[i][j](k-1), d[i][k](k) + d[k][j](k-1))

		return D(n)


4. Compiling and Execution
--------------------------
Several testcases are included in the 'testcases' folder, along with the expected output files. 
<input_file> path must be given as "testcases/inputX" where X = 1 to 5 to use provided inputs.

1. Python - execution
		python FloydWarshall.py <input_file>
2. C++    - compile using the makefile
		make all
          - execution
		./FloydWarshall <input_file>

Both Python and C++ versions use the same input and output formats. 

	Input
	-----
	(number of vertices V - integer)
	(number of edges    E - integer)
	(u - integer)   (v - integer)   (weight of edge connecting u, v)
	(from 1 to V)   (from 1 to V)   (edge  is  considered  directed)
	.
	.
	. (E lines)
	
	Output
	------
	All Pairs Shortest Paths : 

	<groups of 3 lines>

	From : u To : v
	Path : u <u1 u2 ... if path exists else "no path to"> v
	Distance : <shortest distance if it exists else "inf">	

	If the graph contains a negative weight cycle, "Negative cycle at : X" is displayed where X is a vertex. 
	The program is then terminated.



5. Contribution
---------------

Ananth Murthy
-------------
- implemented Python version
- implemented the algorithm in C++
- wrote sections 1-3 of this README
- wrote testcases and expected output 2, 4    (negative testcases)

Chandan Yeshwanth
-----------------
- implemented C++ Distance class
- implemented display of shortest paths
- wrote sections 4-6 of this README
- wrote testcases and expected output 1, 3, 5 (positive testcases)


6. References
-------------
1. Introduction to Algorithms 3rd edition, Cormen, Leiserson, Rivest, Stein
2. Wikipedia page on Floyd Warshall algorithm (en.wikipedia.org/wiki/Floyd–Warshall_algorithm)

