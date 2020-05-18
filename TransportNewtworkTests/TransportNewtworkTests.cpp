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
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\test1.txt");
			matrix.input(file);
			Assert::AreEqual(matrix.get_size_of_file(), 8);
			file.close();
		}

		TEST_METHOD(TestInputGraphWithoutS)
		{
			stream* matrix;
			matrix = new stream();
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\GraphWithoutS.txt");
			matrix->input(file);
			matrix->SetVertexCount();
			auto  funPtr = [matrix] {matrix->CreateAdjacencyMatrix();};
			Assert::ExpectException<std::out_of_range>(funPtr);
			file.close();
		}

		TEST_METHOD(TestInputWithMinus)
		{
			stream* matrix;
			matrix = new stream();
			auto  funPtr = [matrix] {
				ifstream file;
				file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\inputWithMinus.txt");
				matrix->input(file); };
			Assert::ExpectException<std::out_of_range>(funPtr);
		}

		TEST_METHOD(TestInputNoWayFromStoT)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\NoWayFromStoT.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::IsFalse(matrix.TrueTransport_network());
			file.close();
		}

		TEST_METHOD(TestSetVertexCount1)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\test1.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			Assert::AreEqual(matrix.get_count_of_Vertex(), 6);
		}

		TEST_METHOD(TestSetVertexCount2)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\test2.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			Assert::AreEqual(matrix.get_count_of_Vertex(), 7);
		}

		TEST_METHOD(TestIsTrueTransportNetwork1)
		{
			//normal transport graph 
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\test2.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::IsTrue(matrix.TrueTransport_network());
		}

		TEST_METHOD(TestIsTrueTransportNetwork2)
		{
			//in this test 2 end vertexes
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\test3.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::IsFalse(matrix.TrueTransport_network());
		}

		TEST_METHOD(TestIsTrueTransportNetwork3)
		{
			//in this test we have cycle in graph
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\test3.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::IsFalse(matrix.TrueTransport_network());
		}
		TEST_METHOD(TestCreateAdjencyMatrix)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\test2.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
		}

		TEST_METHOD(TestFindMaxFlow1)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\test1.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 5);
		}

		TEST_METHOD(TestFindMaxFlow2)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\test2.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 7);
		}
		

		TEST_METHOD(TestFindMaxFlow3)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\test4.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 7);
		}

		TEST_METHOD(TestFindMaxFlow4)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\test5.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 10);
		}

		TEST_METHOD(TenVertexTestFindMaxFlow1)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\10vertextest1.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 21);
		}

		TEST_METHOD(TenVertexTestFindMaxFlow2)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\10vertextest2.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 26);
		}

		TEST_METHOD(TenVertexTestFindMaxFlow3)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\10vertextest3.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 28);
		}

		TEST_METHOD(TenVertexTestFindMaxFlow4)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\10vertextest4.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 14);
		}

		TEST_METHOD(TenVertexTestFindMaxFlow5)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\10vertextest5.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 18);
		}

		TEST_METHOD(TenVertexTestFindMaxFlow6)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\10vertextest6.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 50);
		}

		TEST_METHOD(TenVertexTestFindMaxFlow7)
		{
			stream matrix;
			ifstream file;
			file.open("C:\\Users\\User\\source\\repos\\AISDKurs\\TransportNewtworkTests\\10vertextest7.txt");
			matrix.input(file);
			matrix.SetVertexCount();
			matrix.CreateAdjacencyMatrix();
			Assert::AreEqual(matrix.FindMaxFlow(), 95);
		}
	};
}
