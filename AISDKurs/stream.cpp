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
void stream::push(int u, int v, int** f, int* e) //push stream to next vertex
{
	int d;
	if (e[u] < this->matrix[u][v] - f[u][v])
		d = e[u];
	else
		d = this->matrix[u][v] - f[u][v];
	f[u][v] = f[u][v] + d;
	f[v][u] = -f[u][v];
	e[u] = e[u] - d;
	e[v] = e[v] + d;
}
bool stream::lift(int u, int* h, int** f, int max) //lift vertex
{
	int d = max;
	for (int i = 0; i < this->All_vertex.get_size(); i++) {
		if (this->matrix[u][i] - f[u][i] > 0) {
			if (d > h[i])
				d = h[i];
		}
	}
	if (d == max)
		return false;
	h[u] = d + 1;
	return true;
}
int stream::FindMaxFlow() //pushing the pre-stream algorithm
{
	if (this->TrueTransport_network() != true)
		throw std::out_of_range("wrong graph");
	int max = -1;// maximum weight
	for (int i = 0; i < this->All_vertex.get_size(); i++)
		for (int j = 0; j < this->All_vertex.get_size(); j++)
			if (this->matrix[i][j] > max)
				max = this->matrix[i][j];
	max++;
	int** f = new int* [this->All_vertex.get_size()]; //f - it is flow
	for (int i = 0; i < this->All_vertex.get_size(); i++)
	{
		f[i] = new int[this->All_vertex.get_size()];
	}
	for (int i = 0; i < this->All_vertex.get_size(); i++)
	{
		for (int j = 0; j < this->All_vertex.get_size(); j++)
			f[i][j] = 0;
	}
	for (int i = 1; i < this->All_vertex.get_size(); i++)
	{
		f[0][i] = this->matrix[0][i];
		f[i][0] = -this->matrix[0][i];
	}
	int* h = new int[this->All_vertex.get_size()]; //h- it is height
	h[0] = this->All_vertex.get_size();
	for (int i = 1; i < this->All_vertex.get_size(); i++)
		h[i] = 0;
	int* e = new int[this->All_vertex.get_size()]; //excess flow
	for (int i = 1; i < this->All_vertex.get_size(); i++)
		e[i] = f[0][i];
	for (; ;)
	{
		int i;
		for (i = 1; i < this->All_vertex.get_size() - 1; i++)
			if (e[i] > 0)
				break;
		if (i == this->All_vertex.get_size() - 1)
			break;
		int j;
		for (j = 0; j < this->All_vertex.get_size(); j++)
			if (this->matrix[i][j] - f[i][j] > 0 && h[i] == h[j] + 1)
				break;
		if (j < this->All_vertex.get_size())
			push(i, j, f, e);
		else
			if (lift(i, h, f, max) != true)
				break;
	}
	int flow = 0;
	for (int i = 0; i < this->All_vertex.get_size(); i++)
		if (f[i][this->All_vertex.get_size() - 1])
			flow += f[i][this->All_vertex.get_size() - 1];
	cout << "Maximum flow equal - " << flow << endl;
	for (int i = 0; i < this->All_vertex.get_size(); i++)
	{
		delete[] f[i];
	}
	return flow;
}