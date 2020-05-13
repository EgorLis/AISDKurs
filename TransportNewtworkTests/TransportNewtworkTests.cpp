#include "pch.h"
#include "CppUnitTest.h"
#include "../AISDKurs/stream.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TransportNewtworkTests
{
	TEST_CLASS(TransportNewtworkTests)
	{
	public:
		
		TEST_METHOD(TestInput)
		{
			stream matrix;
			ifstream file;
			file.open("test1.txt");
			matrix.input(file);
			Assert::AreEqual(matrix.get_size_of_file(), 8);
			file.close();
		}

		TEST_METHOD(TestSetVertexCount1)
		{
			stream matrix;
			ifstream file;
			file.open("test1.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			Assert::AreEqual(matrix.get_count_of_Vertex(), 6);
		}

		TEST_METHOD(TestSetVertexCount2)
		{
			stream matrix;
			ifstream file;
			file.open("test2.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			Assert::AreEqual(matrix.get_count_of_Vertex(), 7);
		}

		TEST_METHOD(TestIsTrueTransportNetwork1)
		{
			stream matrix;
			ifstream file;
			file.open("test2.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::IsTrue(matrix.TrueTransport_network());
		}

		TEST_METHOD(TestIsTrueTransportNetwork2)
		{
			stream matrix;
			ifstream file;
			file.open("test3.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::IsFalse(matrix.TrueTransport_network());
		}

		TEST_METHOD(TestCreateAdjencyMatrix)
		{
			stream matrix;
			ifstream file;
			file.open("test2.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
		}

		TEST_METHOD(TestFindMaxFlow1)
		{
			stream matrix;
			ifstream file;
			file.open("test1.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 5);
		}

		TEST_METHOD(TestFindMaxFlow2)
		{
			stream matrix;
			ifstream file;
			file.open("test2.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 7);
		}
		

		TEST_METHOD(TestFindMaxFlow3)
		{
			stream matrix;
			ifstream file;
			file.open("test4.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 7);
		}

		TEST_METHOD(TestFindMaxFlow4)
		{
			stream matrix;
			ifstream file;
			file.open("test5.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 10);
		}
	};
}
