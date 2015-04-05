//sample input set is given below
#include <iostream>
#include <queue>
#include <climits>
#include <vector>
#include <stack>
using namespace std;
#define MAX 20
#define NIL -2

struct Graph{
	int v, e, adj[MAX][MAX];
};

struct Node{
	int name;
	int pred;
	int key;
};

struct compareNodes{
	bool operator() (Node& n1, Node& n2){
		if(n1.key>n2.key) return true;
		return false;
	}
};

Graph g;
vector <Node> A;
stack <Node> graph;  //used stack instead of vector
priority_queue<Node, vector<Node>, compareNodes> Q;

void initQueue(int s){
	for (int i = 1; i <= g.v; i++){
		Node node;
		node.name = i;
		node.pred = NIL;
		if (i == s)
			node.key = 0;
		else
			node.key = INT_MAX;
		Q.push(node);
	}
}

void mst_prim(int s){

	initQueue(s);

	while (!Q.empty()){
		Node u= Q.top();
		A.push_back(u);
		Q.pop();

		for(int i=1; i<=g.v; i++){
			if(g.adj[u.name][i] != 0){
				while(!Q.empty()){
					graph.push(Q.top());
					Q.pop();
				}

				while (!graph.empty()){
					if (graph.top().name == i ){
						if (g.adj[u.name][i] < graph.top().key){
							graph.top().key = g.adj[u.name][i];
							graph.top().pred = u.name;
						}
					}
					Q.push(graph.top());
					graph.pop();
				}
			}
		}
	}
}

void printCostTable(){
	int tot_cost=0;
	cout << "<Node>\t<Pred>\t<Cost>" << endl;
	for (int j = 0; j<A.size(); j++){
		tot_cost += A.at(j).key;
		cout << A.at(j).name << "\t" << A.at(j).pred << "\t" << A.at(j).key << endl;
	}

	cout <<"--\t--\t--" << endl;
	cout << "Total cost:\t" << tot_cost << endl;
}

int main (){

	cout << "Enter no of nodes: ";
	cin >> g.v;

	cout << "Enter no of edges: ";
	cin >> g.e;

	cout << "Enter edge values in following format:"<< endl
		<< "<node_no> <node_no> <edge_value>" << endl ;
	for (int i=1; i<=g.e; i++){
		int u, v, e;
		cin >> u >> v >> e;
		g.adj[u][v]=g.adj[v][u]=e;
	}

	mst_prim(1);
	printCostTable();
	return 0;
}

/*
//Input values
9
14
1 2 4
1 8 8
2 3 8
2 8 12
3 4 6
3 6 4
3 9 3
4 5 9
4 6 13
5 6 10
6 7 3
7 9 5
7 8 1
8 9 6

//Matrix
0       4       0       0       0       0       0       8       0
4       0       8       0       0       0       0       12      0
0       8       0       6       0       4       0       0       3
0       0       6       0       9       13      0       0       0
0       0       0       9       0       10      0       0       0
0       0       4       13      10      0       3       0       0
0       0       0       0       0       3       0       1       5
8       12      0       0       0       0       1       0       6
0       0       3       0       0       0       5       6       0
*/
