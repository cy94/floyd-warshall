/*
 * FloydWarshall.cc
 *
 * Implementation of Floyd Warshall Algorithm
 * 
 * Uses C++11 standard
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
 * */

# include <iostream>
# include <fstream>
# include <string>

using namespace::std;

// class to handle comparisions and additions of infinite weighted quantities, used to store distances
class Distance
{
private:

	int weight;
	bool infinite;
	
public:

	Distance()
	{
		weight = 0;
		infinite = true;
	}	
	
	void setWeight(int weight)
	{
		this->weight = weight;
		infinite = false;
	}
	
	string getWeight() const
	{
		if(infinite) 
			return "inf";
			
		return to_string(weight);
	}
	
	bool isInfinite()
	{
		return infinite;
	}
	
	bool isZero()
	{
		if(!infinite && weight==0)
			return true;
		
		return false;
	}
	
	// comparing infinite weights
	bool operator > (const Distance & e)
	{
		if (e.infinite)
			return false;
		else if (this->infinite)
			return true;
		else if (this->weight > e.weight)
			return true;
		
		return false;
	}
	
	// adding infinite weights
	Distance operator + (const Distance & e)
	{
		Distance d;
		
		if(this->infinite || e.infinite)
		{
			return d;
		}
		
		d.setWeight(e.weight + this->weight);
		return d;
	}
};



// To store shortest path distances
Distance ** dist ;

// To store the path and corresponding parents 
int ** parent ;



// Recursive function to obtain the path as a string
string obtainPath(int i, int j)
{
    if (dist[i][j].isInfinite())
        return " no path to ";
    
    if (parent[i][j] == i)
        return " ";
    else 
        return obtainPath(i, parent[i][j]) + to_string(parent[i][j]+1) + obtainPath(parent[i][j], j);
}



int main(int argc, char** argv)
{
	if(argc < 2)
	{
		cout << "Check README for usage." << endl;
		exit(-1);
	}
	
	ifstream ifile (argv[1]);
	
	if(!ifile)
	{
		cout << "File not found." << endl;
		exit(-1);
	}
	
	// number of vertices and edges
	int V, E;
	int i, j, k, u, v, w;
	
	ifile >> V >> E;
	
	
	// Matrices declared and initialised to infinity and zero respectively
	dist = new Distance * [V];
	for (int i = 0; i < V; i++)
		dist[i] = new Distance[V];
	
	
	parent = new int *[V];
	for (int i = 0; i < V; i++)
		parent[i] = new int[V];
	
	
	
	
	// Read edges from input file
	for (i=0; i<E; i++)
	{
		ifile >> u >> v >> w;
		dist[u-1][v-1].setWeight(w);
		parent[u-1][v-1] = u-1;
	}
	ifile.close();
	
	
	
	// Path from vertex to itself is set
	for (i=0; i<V; i++)
	{
		dist[i][i].setWeight(0);
		parent[i][i] = i;
	}
	
	
	// Actual Floyd Warshall Algorithm
	for (k=0; k<V; k++)
	{
		for (i=0; i<V; i++)
		{
			for (j=0; j<V; j++)
			{
				if (dist[i][j] > dist[i][k] + dist[k][j])
                {
					dist[i][j]    =   dist[i][k]    +   dist[k][j];
					parent[i][j]  =   parent[k][j];
				}
			}
		}
	}
	
	
	// Check for negative cycles
	for (i=0; i<V; i++)
	{
		if (!dist[i][i].isZero())
		{
			cout << "Negative cycle at : " << i+1 << endl;
			return 0;
		}
	}
	
	
	// Print all paths
	cout << "All Pairs Shortest Paths : \n\n";
	for (i=0; i<V; i++)
	{
		cout << endl;
		for (j=0; j<V; j++)
		{
			cout << "From : " << i+1 << " To : " << j+1 << endl;
			cout << "Path : " << 1+i << obtainPath(i,j) << j+1 << endl;
			cout << "Distance : " << dist[i][j].getWeight() << endl << endl;
		}
	}
	
	delete [] dist;
	delete [] parent;
	
	return 0;
}

