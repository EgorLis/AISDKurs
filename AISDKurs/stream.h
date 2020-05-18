
#include "List.cpp"
#include <fstream>
#include <iostream>
class stream
{
	private:
		class string
		{
		public:
			char vertex_1;
			char vertex_2;
			int weight;
			string() :vertex_1(0), vertex_2(0), weight(0) {};
			~string() {}
		};
		List<string*> File;;
		int** matrix;
		List<char> All_vertex;
public:
	stream() : matrix(NULL) {};		
	~stream()		{
					File.~List();	
					All_vertex.~List();			
					for (int i = 0; i < this->All_vertex.get_size(); i++)			
					{				
						delete[] matrix[i];			
					}		
	}		
	void input(ifstream& file); //input text from text file		
	void SetVertexCount(); //find all Vertex		
	void CreateAdjacencyMatrix(); //create Adjacency Matrix		
	void printMatrix(); //print  Adjacency Matrix		
	bool TrueTransport_network();//is this graph a transport network
	
	void recurFind(int top, int end, int** color_matrix, bool& temp);//dfs algoritm with color
		
	void push(int u, int v, int** f, int* e);//push stream to next vertex
		
	bool lift(int u, int* h, int** f, int max);//lift vertex
		
	int FindMaxFlow();//pushing the pre-stream algorithm

	int get_size_of_file() //count of strings
	{
		return this->File.get_size();
	}
	int get_count_of_Vertex()//count of veretxs
	{
		return this->All_vertex.get_size();
	}
};
