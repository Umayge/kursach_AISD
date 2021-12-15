#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <tuple>
#include <algorithm>

using namespace std;


class Graph
{
	vector<tuple<int, int>> edgesList;
	int edgesCount;
	int verticesCount;

	Graph(const Graph&) = delete;
	Graph(Graph&&) = delete;
	Graph& operator = (const Graph&) const = delete;
	Graph& operator = (Graph&&) const = delete;
public:
	Graph() : edgesCount(0), verticesCount(0) {};

	~Graph() {};

	void InitGraphRandom()
	{
		int maxEdges, a, b;
		
		bool flag;

		srand(time(NULL));

		verticesCount = rand() % 100;
		maxEdges = verticesCount * (verticesCount - 1) / 2 + verticesCount;
		if (maxEdges == 0) edgesCount = 0;
		else edgesCount = rand() % maxEdges;

		edgesList.resize(edgesCount);
		for (int i = 0; i < edgesCount;)
		{
			a = rand() % verticesCount;
			b = rand() % verticesCount;
			

			flag = false;
			for (int j = 0; j < i; j++)
			{
				if (a == get<0>(edgesList[j]) && b == get<1>(edgesList[j]))
				{
					flag = true;
					j = i;
				}
			}
			if (!flag)
			{
				edgesList[i] = { a, b};
				i++;
			}
		}
		sort(edgesList.begin(), edgesList.end());
	}

	void InitGraphManually()
	{
		string aStr, bStr, verticesStr, edgesStr;
		int a, b, count;
		
		bool flag;

		verticesCount = -1;
		do
		{
			cout << "---Enter the number of vertices---: ";
			cin >> verticesStr;
			try
			{
				verticesCount = stoi(verticesStr);
				if (verticesCount < 0) cout << "Invalid input!\n";
			}
			catch (invalid_argument)
			{
				cout << "Invalid input!\n";
			}
			catch (out_of_range)
			{
				cout << "Invalid input!\n";
			}
		} while (verticesCount < 0);
		cout << endl;

		edgesCount = -1;
		do
		{
			cout << "---Enter the number of edges, in cannot be more than " << verticesCount * (verticesCount - 1) / 2 + verticesCount << "---: ";
			cin >> edgesStr;
			try
			{
				edgesCount = stoi(edgesStr);
				if (edgesCount < 0 || edgesCount > verticesCount * (verticesCount - 1) / 2 + verticesCount) cout << "Invalid input!\n";
			}
			catch (invalid_argument)
			{
				cout << "Invalid input!\n";
			}
			catch (out_of_range)
			{
				cout << "Invalid input!\n";
			}
		} while (edgesCount < 0 || edgesCount > verticesCount * (verticesCount - 1) / 2 + verticesCount);
		cout << endl;

		edgesList.resize(edgesCount);
		if (edgesCount > 0) cout << "\n---Enter edges as triplets of numbers, separated by a space (vertex names range from 0 to " << verticesCount - 1 << ")---:\n";
		count = 0;
		while (count < edgesCount)
		{
			cin >> aStr >> bStr;
			try
			{
				a = stoi(aStr);
				b = stoi(bStr);

				if (a >= 0 && a < verticesCount && b >= 0 && b < verticesCount)
				{
					flag = false;
					for (int j = 0; j < count; j++)
					{
						if (a == get<0>(edgesList[j]) && b == get<1>(edgesList[j]))
						{
							flag = true;
							j = count;
						}
					}
					if (!flag)
					{
						edgesList[count] = { a, b};
						count++;
					}
					else
					{
						cout << "You have already entered this edge\n";
					}
				}
				else
				{
					cout << "Invalid input!\n";
				}
			}
			catch (invalid_argument)
			{
				cout << "Invalid input!\n";
			}
			catch (out_of_range)
			{
				cout << "Invalid input!\n";
			}
		}
		sort(edgesList.begin(), edgesList.end());
	}

	void printGraph()
	{
		int a, b, prev, count;
		
		bool flag;

		if (edgesCount > 0)
		{
			cout << "\nNumber of vertices: " << verticesCount << endl;
			cout << "Number of edges: " << edgesCount << endl;
			tie(a, b) = edgesList[0];
			prev = a;
			count = 0;
			cout << "                                                         |Graph|";
			cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
			for (auto& j : edgesList)
			{
				tie(a, b) = j;
				if (count == 5)
				{
					if (a == prev) cout << endl;
					count = 0;
				}
				if (a != prev)
				{
					cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
					prev = a;
					count = 0;
				}
				cout << "(\"" << a << "\"; \"" << b << "\"; " << ") ";
				count++;
			}
			cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
		}
		if (verticesCount > 0)
		{
			cout << "Vertices that have no neighbours:\n";
			for (int i = 0; i < verticesCount; i++)
			{
				flag = false;
				for (auto& j : edgesList)
				{
					if (i == get<0>(j) || i == get<1>(j)) flag = true;
				}
				if (!flag) cout << i << "   ";
			}
			cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
		}
	}

	double BellmanFord(int x, int y)
	{
		vector<double> distance(verticesCount);
		int a, b;
		

		for (int i = 0; i < verticesCount; i++) distance[i] = 1e18;
		distance[x] = 0;

		for (int i = 0; i < verticesCount - 1; i++)
		{
			for (auto& e : edgesList)
			{
				tie(a, b) = e;
				if (distance[a] < 1e18) distance[b] = min(distance[b], distance[a]+1.0);
			}
		}
		for (auto& e : edgesList)
		{
			tie(a, b) = e;
			if (distance[a] < 1e18 && distance[a] + 1 < distance[b])
			{
				return -1e18;
			}
			//distance[b] = min(distance[b], distance[a]);
		}
		return distance[y];
	}

	int getVerticesCount() { return verticesCount; }

	int getEdgesCount() { return edgesCount; }
};


int main()
{
	Graph graph;
	string choice, astr, bstr;
	double res;
	int a = 2, b = 2, c = 2;

	cout << "Enter \"0\" if you want automatic graph generation\n";
	cout << "Enter \"1\" if you want to enter the graph yourself\n\n";
	do
	{
		cin >> choice;
		try
		{
			c = stoi(choice);
			if (c != 0 && c != 1) cout << "Invalid input!\n";
		}
		catch (invalid_argument)
		{
			cout << "Invalid input!\n";
		}
		catch (out_of_range)
		{
			cout << "Invalid input!\n";
		}
	} while (c != 0 && c != 1);
	cout << endl;

	if (c == 0)
	{
		graph.InitGraphRandom();
	}
	else
	{
		graph.InitGraphManually();
	}

	graph.printGraph();
	if (graph.getEdgesCount() > 0)
	{
		cout << "\n\nEnter the vertex from which you want to find the shortest path to the rest.\"\n\n";
		do
		{
			cin >> astr;
			try
			{
				a = stoi(astr);
				if (a >= 0 && a < graph.getVerticesCount())
				{
					for (int b = 0; b < graph.getVerticesCount(); b++)
					{
						res = graph.BellmanFord(a, b);
						if (res == 1e18)
						{
								cout << a << "-->" << b << ":There is no path between vertices " << "\n";
						}
						else
						{
							if (res == -1e18)
							{
								cout << "The graph contains cycles of negative length\n";
							}
							else
							{
								cout << a << "-->" << b << ": " << res << endl;
							}
						}
					}
						

					
				}
				else
				{
					if (a != -1) cout << "Invalid input!\n";
				}
			}
			catch (invalid_argument)
			{
				cout << "Invalid input!\n";
			}
			catch (out_of_range)
			{
				cout << "Invalid input!\n";
			}
		} while (a != -1 || b != -1);
	}
	else
	{
		if (graph.getVerticesCount() == 0) cout << "This is an empty graph\n";
	}
	return 0;
}

//#include <iostream>
//#include <vector>
//#include <ctime>
//#include <string>
//#include <tuple>
//#include <algorithm>
//
//using namespace std;
//
//
//class Graph
//{
//	vector<tuple<int, int, double>> edgesList;
//	int edgesCount;
//	int verticesCount;
//
//	Graph(const Graph&) = delete;
//	Graph(Graph&&) = delete;
//	Graph& operator = (const Graph&) const = delete;
//	Graph& operator = (Graph&&) const = delete;
//public:
//	Graph() : edgesCount(0), verticesCount(0) {};
//
//	~Graph() {};
//
//	void InitGraphRandom()
//	{
//		int maxEdges, a, b;
//		double w;
//		bool flag;
//
//		srand(time(NULL));
//
//		verticesCount = rand() % 100;
//		maxEdges = verticesCount * (verticesCount - 1) / 2 + verticesCount;
//		if (maxEdges == 0) edgesCount = 0;
//		else edgesCount = rand() % maxEdges;
//
//		edgesList.resize(edgesCount);
//		for (int i = 0; i < edgesCount;)
//		{
//			a = rand() % verticesCount;
//			b = rand() % verticesCount;
//			w = (double)rand() / rand() * 1000;
//
//			flag = false;
//			for (int j = 0; j < i; j++)
//			{
//				if (a == get<0>(edgesList[j]) && b == get<1>(edgesList[j]))
//				{
//					flag = true;
//					j = i;
//				}
//			}
//			if (!flag)
//			{
//				edgesList[i] = { a, b, w };
//				i++;
//			}
//		}
//		sort(edgesList.begin(), edgesList.end());
//	}
//
//	void InitGraphManually()
//	{
//		string aStr, bStr, wStr, verticesStr, edgesStr;
//		int a, b, count;
//		double w;
//		bool flag;
//
//		verticesCount = -1;
//		do
//		{
//			cout << "---Enter the number of vertices---: ";
//			cin >> verticesStr;
//			try
//			{
//				verticesCount = stoi(verticesStr);
//				if (verticesCount < 0) cout << "Invalid input!\n";
//			}
//			catch (invalid_argument)
//			{
//				cout << "Invalid input!\n";
//			}
//			catch (out_of_range)
//			{
//				cout << "Invalid input!\n";
//			}
//		} while (verticesCount < 0);
//		cout << endl;
//
//		edgesCount = -1;
//		do
//		{
//			cout << "---Enter the number of edges, in cannot be more than " << verticesCount * (verticesCount - 1) / 2 + verticesCount << "---: ";
//			cin >> edgesStr;
//			try
//			{
//				edgesCount = stoi(edgesStr);
//				if (edgesCount < 0 || edgesCount > verticesCount * (verticesCount - 1) / 2 + verticesCount) cout << "Invalid input!\n";
//			}
//			catch (invalid_argument)
//			{
//				cout << "Invalid input!\n";
//			}
//			catch (out_of_range)
//			{
//				cout << "Invalid input!\n";
//			}
//		} while (edgesCount < 0 || edgesCount > verticesCount * (verticesCount - 1) / 2 + verticesCount);
//		cout << endl;
//
//		edgesList.resize(edgesCount);
//		if (edgesCount > 0) cout << "\n---Enter edges as triplets of numbers, separated by a space (vertex names range from 0 to " << verticesCount - 1 << ")---:\n";
//		count = 0;
//		while (count < edgesCount)
//		{
//			cin >> aStr >> bStr >> wStr;
//			try
//			{
//				a = stoi(aStr);
//				b = stoi(bStr);
//				w = stod(wStr);
//
//				if (a >= 0 && a < verticesCount && b >= 0 && b < verticesCount)
//				{
//					flag = false;
//					for (int j = 0; j < count; j++)
//					{
//						if (a == get<0>(edgesList[j]) && b == get<1>(edgesList[j]))
//						{
//							flag = true;
//							j = count;
//						}
//					}
//					if (!flag)
//					{
//						edgesList[count] = { a, b, w };
//						count++;
//					}
//					else
//					{
//						cout << "You have already entered this edge\n";
//					}
//				}
//				else
//				{
//					cout << "Invalid input!\n";
//				}
//			}
//			catch (invalid_argument)
//			{
//				cout << "Invalid input!\n";
//			}
//			catch (out_of_range)
//			{
//				cout << "Invalid input!\n";
//			}
//		}
//		sort(edgesList.begin(), edgesList.end());
//	}
//
//	void printGraph()
//	{
//		int a, b, prev, count;
//		double w;
//		bool flag;
//
//		if (edgesCount > 0)
//		{
//			cout << "\nNumber of vertices: " << verticesCount << endl;
//			cout << "Number of edges: " << edgesCount << endl;
//			tie(a, b, w) = edgesList[0];
//			prev = a;
//			count = 0;
//			cout << "                                                         |Graph|";
//			cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
//			for (auto& j : edgesList)
//			{
//				tie(a, b, w) = j;
//				if (count == 5)
//				{
//					if (a == prev) cout << endl;
//					count = 0;
//				}
//				if (a != prev)
//				{
//					cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
//					prev = a;
//					count = 0;
//				}
//				cout << "(\"" << a << "\"; \"" << b << "\"; " << w << ") ";
//				count++;
//			}
//			cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
//		}
//		if (verticesCount > 0)
//		{
//			cout << "Vertices that have no neighbours:\n";
//			for (int i = 0; i < verticesCount; i++)
//			{
//				flag = false;
//				for (auto& j : edgesList)
//				{
//					if (i == get<0>(j) || i == get<1>(j)) flag = true;
//				}
//				if (!flag) cout << i << "   ";
//			}
//			cout << "\n-----------------------------------------------------------------------------------------------------------------------\n";
//		}
//	}
//
//	double BellmanFord(int x, int y)
//	{
//		vector<double> distance(verticesCount);
//		int a, b;
//		double w;
//
//		for (int i = 0; i < verticesCount; i++) distance[i] = 1e18;
//		distance[x] = 0;
//
//		for (int i = 0; i < verticesCount - 1; i++)
//		{
//			for (auto& e : edgesList)
//			{
//				tie(a, b, w) = e;
//				if (distance[a] < 1e18) distance[b] = min(distance[b], distance[a] + w);
//			}
//		}
//		for (auto& e : edgesList)
//		{
//			tie(a, b, w) = e;
//			if (distance[a] < 1e18 && distance[a] + w < distance[b])
//			{
//				return -1e18;
//			}
//			//distance[b] = min(distance[b], distance[a] + w);
//		}
//		return distance[y];
//	}
//
//	int getVerticesCount() { return verticesCount; }
//
//	int getEdgesCount() { return edgesCount; }
//};
//
//
//int main()
//{
//	Graph graph;
//	string choice, astr, bstr;
//	double res;
//	int a = 2, b = 2, c = 2;
//
//	cout << "Enter \"0\" if you want automatic graph generation\n";
//	cout << "Enter \"1\" if you want to enter the graph yourself\n\n";
//	do
//	{
//		cin >> choice;
//		try
//		{
//			c = stoi(choice);
//			if (c != 0 && c != 1) cout << "Invalid input!\n";
//		}
//		catch (invalid_argument)
//		{
//			cout << "Invalid input!\n";
//		}
//		catch (out_of_range)
//		{
//			cout << "Invalid input!\n";
//		}
//	} while (c != 0 && c != 1);
//	cout << endl;
//
//	if (c == 0)
//	{
//		graph.InitGraphRandom();
//	}
//	else
//	{
//		graph.InitGraphManually();
//	}
//
//	graph.printGraph();
//	if (graph.getEdgesCount() > 0)
//	{
//		cout << "\n\nEnter the vertices, separated by a space, between which you want to find the shortest path until you enter \"-1\" \"-1\"\n\n";
//		do
//		{
//			cin >> astr >> bstr;
//			try
//			{
//				a = stoi(astr);
//				b = stoi(bstr);
//				if (a >= 0 && a < graph.getVerticesCount() && b >= 0 && b < graph.getVerticesCount())
//				{
//					res = graph.BellmanFord(a, b);
//
//					if (res == 1e18)
//					{
//						cout << "There is no path between vertices \"" << a << "\" and \"" << b << "\"\n";
//					}
//					else
//					{
//						if (res == -1e18)
//						{
//							cout << "The graph contains cycles of negative length\n";
//						}
//						else
//						{
//							cout << "Shortest path between vertices \"" << a << "\" and \"" << b << "\": " << res << endl;
//						}
//					}
//				}
//				else
//				{
//					if (a != -1 || b != -1) cout << "Invalid input!\n";
//				}
//			}
//			catch (invalid_argument)
//			{
//				cout << "Invalid input!\n";
//			}
//			catch (out_of_range)
//			{
//				cout << "Invalid input!\n";
//			}
//		} while (a != -1 || b != -1);
//	}
//	else
//	{
//		if (graph.getVerticesCount() == 0) cout << "This is an empty graph\n";
//	}
//	return 0;
//}
