#include "stream.h"

using namespace std;

void stream::input(ifstream& file) //input text from text file
{
	if (file.eof() != true)
	{
		file.unsetf(ios::skipws);
		List<char>* temp_number;
		string* str;
		while (!file.eof())
		{
			int step = 1;
			temp_number = new List<char>;
			str = new string;
			char symbol = 0;
			while (symbol != '\n')
			{
				file >> symbol;
				if (file.eof())
					return;
				if (symbol == ' '|| symbol == '\n')
				{
					if (step == 2)
					{

						temp_number = new List<char>;
					}
					if (step == 3)
					{
						if (temp_number->get_size() == 0)
							throw std::out_of_range("wrong number");
						else
						{
							int temp = 0;
							for (int i = 0; i < temp_number->get_size(); i++)
							{
								if (temp_number->at(i) >= 48 && temp_number->at(i) <= 57)
								{
									temp = temp * 10 + (temp_number->at(i) - 48);
								}
								else
									throw std::out_of_range("wrong number");
							}
							str->weight = temp;
						}
						temp_number = new List<char>;
					}
					
					step++;
				}
				else {
					switch (step)
					{
					case 1:
						str->vertex_1 = symbol;
						break;
					case 2:
						str->vertex_2 = symbol;
						break;
					case 3:
						temp_number->push_back(symbol);
						break;
					default:
						break;
					}
				}
			}
			if (step == 1)
				throw std::out_of_range("wrong string");
			this->File.push_back(str);
		}
	}
}

void stream::SetVertexCount() //find all cities
{
	for (int i = 0; i < this->File.get_size(); i++)
	{
		int step = 1;
		while (step != 3)
		{
			if (this->All_vertex.get_size() == 0)
			{

				switch (step)
				{
				case 1:
					this->All_vertex.push_back(this->File.at(i)->vertex_1);
					break;
				case 2:
					this->All_vertex.push_back(this->File.at(i)->vertex_2);
					break;
				}
			}
			else
			{
				int match = 0;
				switch (step)
				{
				case 1:
					for (int j = 0; j < this->All_vertex.get_size(); j++)
					{
						if (this->File.at(i)->vertex_1 == this->All_vertex.at(j))
						{
							match = 1;
							break;
						}
					}
					break;
				case 2:
					for (int j = 0; j < this->All_vertex.get_size(); j++)
					{
						if (this->File.at(i)->vertex_2 == this->All_vertex.at(j))
						{
							match = 1;
							break;
						}
					}
					break;
				}
				if (match == 0)
				{
					switch (step)
					{
					case 1:
						this->All_vertex.push_back(this->File.at(i)->vertex_1);
						break;
					case 2:
						this->All_vertex.push_back(this->File.at(i)->vertex_2);
						break;
					}
				}
			}
			step++;
		}
	}
}

void stream::CreateAdjacencyMatrix() //create Adjacency Matrix
{
	int top = -1;
	int stock = -1;
	for (int i = 0; i < this->All_vertex.get_size(); i++) {
		if (this->All_vertex.at(i) == 'S')
			top = i;
		if (this->All_vertex.at(i) == 'T')
			stock = i;
	}
	if (stock == -1 || top == -1)
		throw std::out_of_range("wrong graph");
	this->All_vertex.swap(0, top);
	this->All_vertex.swap(this->All_vertex.get_size() - 1, stock);
	this->matrix = new int* [this->All_vertex.get_size()];

	for (int i = 0; i < this->All_vertex.get_size(); i++)
	{
		this->matrix[i] = new int[this->All_vertex.get_size()];
	}

	for (int i = 0; i < this->All_vertex.get_size(); i++)
	{
		for (int j = 0; j < this->All_vertex.get_size(); j++)
		{
			this->matrix[i][j] = 0;
		}
	}

	for (int i = 0; i < this->File.get_size(); i++)
	{
		int step = 1;
		int index_1 = -1;
		int index_2 = -1;
		while (step != 3)
		{
			int match = 0;
			switch (step)
			{
			case 1:
				for (int j = 0; j < this->All_vertex.get_size(); j++)
				{
					if (this->File.at(i)->vertex_1 == this->All_vertex.at(j))
					{
						match = 1;
						index_1 = j;
						break;
					}
					else
					{
						match = 0;
						index_1 = -1;
					}
				}
				break;
			case 2:
				for (int j = 0; j < this->All_vertex.get_size(); j++)
				{
					if (this->File.at(i)->vertex_2 == this->All_vertex.at(j))
					{
						
						match = 1;
						index_2 = j;
						break;
					}
				    else
					{
						match = 0;
						index_2 = -1;
					}	
				}
				break;
			}
			step++;
		}
		this->matrix[index_1][index_2] = this->File.at(i)->weight;
	}
}
void stream::printMatrix() //print Adjacency Matrix 
{
	cout << " ";
	for (int i = 0; i < this->All_vertex.get_size(); i++)
		cout<<" "<< this->All_vertex.at(i);
	for (int i = 0; i < this->All_vertex.get_size(); i++)
	{
		cout << endl;
		cout << this->All_vertex.at(i)<<" ";
		for (int j = 0; j < this->All_vertex.get_size(); j++)
		{
			cout << this->matrix[i][j] << " ";
		}
	}
	cout << endl;
}

bool stream::TrueTransport_network()
{
	int** temp_matrix = new int* [this->All_vertex.get_size()];
	for (int i = 0; i < this->All_vertex.get_size(); i++)
	{
		temp_matrix[i] = new int[this->All_vertex.get_size()];
	}
	for (int i = 0; i < this->All_vertex.get_size(); i++)
	{
		for (int j = 0; j < this->All_vertex.get_size(); j++)
		{
			if (this->matrix[i][j] != 0)
				temp_matrix[i][j] = 1; // 1 it is white color, 2 it is gray, 3 it is black					
			else
				temp_matrix[i][j] = 0;
		}
	}
	bool this_matrix = true;
	int double_match = -1;
	for (int j = 0; j < this->All_vertex.get_size(); j++)
		if (temp_matrix[j][0] != 0)
			temp_matrix[j][0] = 2; //gray color mean that you in this vertex 
	                               //black mean that you left from this vertex
	recurFind(0, this->All_vertex.get_size() - 1, temp_matrix, this_matrix);
	return this_matrix;
}
void stream::recurFind(int top, int end, int** color_matrix, bool& temp)
{
	int match = 0;
	for (int i = 0; i < this->All_vertex.get_size(); i++)
	{
		if (this->matrix[top][i] != 0)
		{

			switch (color_matrix[top][i])
			{
			case 1:
				for (int j = 0; j < this->All_vertex.get_size(); j++)
					if (color_matrix[j][i] != 0)
						color_matrix[j][i] = 2;
				break;
			case 2:
				temp = false;
				return;
				break;
			default:
				break;
			}
			match++;
			recurFind(i, end, color_matrix, temp);
		}
	}
	if (match == 0 && top == end) {
		temp * true;
		for (int j = 0; j < this->All_vertex.get_size(); j++)
			if (color_matrix[j][top] != 0)
				color_matrix[j][top] = 3;
		return;
	}
	else if (match == 0 && top != end) {
		temp = false;
		for (int j = 0; j < this->All_vertex.get_size(); j++)
			if (color_matrix[j][top] != 0)
				color_matrix[j][top] = 3;
		return;
	}
	else {
		for (int j = 0; j < this->All_vertex.get_size(); j++)
			if (color_matrix[j][top] != 0)
				color_matrix[j][top] = 3;
		return;
	}
}
void stream::push(int previous_vertex, int next_vertex, int** flow, int* excess_flow) //push stream to next vertex
{
	int possible_flow;
	if (excess_flow[previous_vertex] < this->matrix[previous_vertex][next_vertex] - flow[previous_vertex][next_vertex])
		possible_flow = excess_flow[previous_vertex];
	else
		possible_flow = this->matrix[previous_vertex][next_vertex] - flow[previous_vertex][next_vertex];
	flow[previous_vertex][next_vertex] = flow[previous_vertex][next_vertex] + possible_flow;
	flow[next_vertex][previous_vertex] = -flow[previous_vertex][next_vertex];
	excess_flow[previous_vertex] = excess_flow[previous_vertex] - possible_flow;
	excess_flow[next_vertex] = excess_flow[next_vertex] + possible_flow;
}
bool stream::lift(int vertex, int* height_of_vertexes, int** flow, int max) //lift vertex
{
	int min_height = max;
	for (int i = 0; i < this->All_vertex.get_size(); i++) {
		if (this->matrix[vertex][i] - flow[vertex][i] > 0) {
			if (min_height > height_of_vertexes[i])
				min_height = height_of_vertexes[i];
		}
	}
	if (min_height == max)
		return false;
	height_of_vertexes[vertex] = min_height + 1;
	return true;
}
int stream::FindMaxFlow() //pushing the pre-stream algorithm
{
	if (this->TrueTransport_network() != true)
		throw std::out_of_range("wrong graph");
	int max = this->All_vertex.get_size()+1;// maximum weight
	for (int i = 0; i < this->All_vertex.get_size(); i++)
		for (int j = 0; j < this->All_vertex.get_size(); j++)
			if (this->matrix[i][j] > max)
				max = this->matrix[i][j];
	max++;
	int** flow = new int* [this->All_vertex.get_size()]; 
	for (int i = 0; i < this->All_vertex.get_size(); i++)
	{
		flow[i] = new int[this->All_vertex.get_size()];
	}
	for (int i = 0; i < this->All_vertex.get_size(); i++)
	{
		for (int j = 0; j < this->All_vertex.get_size(); j++)
			flow[i][j] = 0;
	}
	for (int i = 1; i < this->All_vertex.get_size(); i++)
	{
		flow[0][i] = this->matrix[0][i];
		flow[i][0] = -this->matrix[0][i];
	}
	int* height_of_vertexes = new int[this->All_vertex.get_size()]; 
	height_of_vertexes[0] = this->All_vertex.get_size();
	for (int i = 1; i < this->All_vertex.get_size(); i++)
		height_of_vertexes[i] = 0;
	int* excess_flow = new int[this->All_vertex.get_size()];
	for (int i = 1; i < this->All_vertex.get_size(); i++)
		excess_flow[i] = flow[0][i];
	for (; ;)
	{
		int i;
		for (i = 1; i < this->All_vertex.get_size() - 1; i++)
			if (excess_flow[i] > 0)
				break;
		if (i == this->All_vertex.get_size() - 1)
			break;
		int j;
		for (j = 0; j < this->All_vertex.get_size(); j++)
			if (this->matrix[i][j] - flow[i][j] > 0 && height_of_vertexes[i] == height_of_vertexes[j] + 1)
				break;
		if (j < this->All_vertex.get_size())
			push(i, j, flow, excess_flow);
		else
			if (lift(i, height_of_vertexes, flow, max) != true)
				break;
	}
	int max_flow = 0;
	for (int i = 0; i < this->All_vertex.get_size(); i++)
		if (flow[i][this->All_vertex.get_size() - 1])
			max_flow += flow[i][this->All_vertex.get_size() - 1];
	cout << "Maximum flow equal - " << max_flow << endl;
	for (int i = 0; i < this->All_vertex.get_size(); i++)
	{
		delete[] flow[i];
	}
	return max_flow;
}