#include "stream.h"



int main()
{
	stream graph;
	ifstream file;
	file.open("input.txt");
	graph.input(file);
	graph.SetVertexCount();
	graph.CreateAdjacencyMatrix();
	graph.printMatrix();
	graph.TrueTransport_network();
	graph.FindMaxFlow();
	file.close();
}