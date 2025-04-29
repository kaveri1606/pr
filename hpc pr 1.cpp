#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<omp.h>

using namespace std;

class Graph
{
private:
	int numVertices;
	vector<vector<int>>adj;

public:
	Graph(int vertices) : numVertices(vertices),adj(vertices){}


void addEdge(int src, int dest)
{
	adj[src].push_back(dest);
	adj[dest].push_back(src);
}

void viewGraph()
{
	cout<<"Graph:\n";
	for(int i=0;i<numVertices;i++)
	{
		cout<<"Vertices: "<<i<<"->";
		for(int neighbor:adj[i])
		{
			cout<<neighbor<<" ";
		}
	cout<<endl;
	}
}

void bfs(int startVertex)
{
	vector<int>visited(numVertices,false);
	queue<int>q;

	visited[startVertex]=true;
	q.push(startVertex);

	while(!q.empty()){
		int currentVertex=q.front();
		q.pop();
		cout<<currentVertex<<" ";

		#pragma omp parallel for
		for(size_t i=0;i<adj[currentVertex].size();i++)
		{
			int neighbor=adj[currentVertex][i];
			if(!visited[neighbor])
			{
				visited[neighbor]=true;
				q.push(neighbor);
			}
		}
	}
}

void dfs(int startVertex)
{
	vector<int>visited(numVertices,false);
	stack<int>s;

	visited[startVertex]=true;
	s.push(startVertex);

	while(!s.empty())
	{
		int currentVertex=s.top();
		s.pop();
		cout<<currentVertex<<" ";

		#pragma omp parallel for
		for(size_t i=0;i<adj[currentVertex].size();i++)
		{
			int neighbor=adj[currentVertex][i];
			if(!visited[neighbor])
			{
				visited[neighbor]=true;
				s.push(neighbor);
			}
		}
	}
}
};

int main()
{
	int numVertices;
	cout<<"Enter the number of Vertices in the Graph: ";
	cin>>numVertices;
	Graph graph(numVertices);
	

	int numEdges;
	cout<<"Enter the number of Edges in the graph: ";
	cin>>numEdges;

	cout<<"Enter the Edges(source and destination): ";
	for(int i=0;i<numEdges;i++)
	{
		int src,dest;
		cin>>src>>dest;
		graph.addEdge(src,dest);
	}

	graph.viewGraph();

	int startVertex;
	cout<<"Enter the starting vertex for BFS and DFS: ";
	cin>>startVertex;

	cout<<"Breadth First Search(BFS): ";
	graph.bfs(startVertex);
	cout<<endl;

	cout<<"Depth First Search(DFS): ";
	graph.dfs(startVertex);
	cout<<endl;

	return 0;
}

