#include "Vertex.h"
#include "Edge.h"
#include <vector>
#include <memory>
#include <functional>
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
#include <set>
#include <iterator>
using namespace std;


class Graph
{
public:
	Graph()
	{
		using namespace std::placeholders;
		// assign(std::bind(&Graph::addEdge, this, std::ref(data), _1));
		assign(std::bind(&Graph::getVertex, this, _1), std::bind(&Graph::getLayeredVertex, this, _1));
	}

	//read in the data
	friend istream& operator >> (istream & is, Graph & graph)
	{
		int nodes;
		is >> nodes;
		graph.data.resize(nodes);
		//LOOP THROUGH MATRIX
		for(int i = 0; i != nodes-1; ++i)
		{
			for(int j = 0; j != nodes; ++j)
			{
				int capacity;
				is >> capacity;
				if(capacity == 0) continue;
				graph.data[i].addEdge(j, capacity);
			}
		}
		return is;
	}

	set<int> getLayer(int i)
	{
		return layers[i];
	}
	LayeredVertex& operator[] (int i)
	{
		return layeredNetwork[i];
	}
	Vertex& getVertex(int dest)//std::vector<Vertex> &data, int dest)
	{
		return data[dest];//.addInEdge(e);
	}
	LayeredVertex& getLayeredVertex(int dest)
	{
		return layeredNetwork[dest];
	}
	void print()
	{
		for (size_t i = 0; i != data.size(); ++i)
		{
			cout << "Vertex " << i << "\n";
			for(auto& x : data[i].available())
			{
				cout << *x;
			}
		}
	}

	std::vector<int> unbalanced()
	{	
		vector<int> v;
		v.reserve(data.size()-2);
		for(unsigned i =1; i != data.size()-1;++i)
		{
			if(data[i].excess() > 0) v.push_back(i);
		}
		return v;
	}

	std::vector<int> unbalancedLayer()
	{	
		vector<int> v;
		v.reserve(data.size()-2);
		for(unsigned i =1; i != data.size()-1;++i)
		{
			if(layeredNetwork[i].getExcess() > 0) v.push_back(i);
		}
		return v;
	}
	std::vector<int> unbalanced(int i)
	{
		vector<int> v;
		v.reserve(layers[i].size());
		for(unsigned j= 0; j != layers[i].size(); ++j)
		{
			if(layeredNetwork[j].getExcess() > 0) v.push_back(j);
		}
		return v;
	}
	void start()
	{
		data[0].sPush();
	}
	void push(int node)
	{
		data[node].push();
	}
	operator bool() const
	{
		return data[0].done();
	}
	void GenerateLayeredNetwork()
	{
		//Set up Edges
		layeredNetwork.clear();
		layeredNetwork.reserve(data.size());
		for(auto & vertex : data)
		{
			layeredNetwork.emplace_back(vertex);
		}
		//Design Layers
		layers.clear();
		breadthFirstSearch();
		for(size_t i = 0; i != layers.size()-1; ++i)
		{
			for(auto index : layers[i])
			{
				layeredNetwork[index].modifyEdges(layers[i+1]);
			}
		}

	}

private:
	std::vector<Vertex> data;
	std::vector<LayeredVertex> layeredNetwork;
	std::vector<set<int>> layers;

	void breadthFirstSearch()
	{
		queue<pair<unsigned, unsigned>> q;
		q.push(make_pair(0, 0));
		layers.push_back({0}); //this won't work
		while(!q.empty())
		{
			if(layers.size() <= q.front().first)
			{
				layers.push_back(set<int>());
			}
			// layers[q.top().first].insert(q.top().second);
			unsigned i = q.front().first +1;
			auto next = layeredNetwork[q.front().second].getNextLayer();
			for(size_t i = 0; i != layers.size(); ++i)
			{
				// for()
				set<int> s;
				set_intersection(layers[i].begin(), layers[i].end(), next.begin(), next.end(), inserter(s, s.begin()));
				for_each(s.begin(), s.end(), [&next](int j){next.erase(j);});
			}
			layers[i].insert(next.begin(), next.end());
			q.pop();
			for_each(next.begin(), next.end(), [i, &q](int val){q.push(make_pair(i,val));});
		}
	}

};

void addEdge(std::vector<Vertex> &data, int dest, std::shared_ptr<Edge> e)
{
	data[dest].addInEdge(e);
}
template <typename T>
void printVector(const vector<T> & v)
{
	for(size_t i = 0; i != v.size(); ++i)
	{
		cout << v[i] << " ";
	}
	cout << "\n";
}

int main()
{
	//build somehow
	Graph graph;
	cin >> graph;
	graph.start();
	// int i = 0;
	std::string junk;
	// graph.GenerateLayeredNetwork();
	auto unbalance = graph.unbalanced();
	// graph[0].pushMax();
	while(!unbalance.empty())
	{
		// auto layerUnbalance = 
		for(auto & x: unbalance)
		{
			if(!graph[x].isBlocked())
			{
				// cout << x << "\n";
				graph.getVertex(x).push();
				graph.getVertex(x).returnPush();
			}
		}
		cin >> junk;
		unbalance = graph.unbalanced();

	}
	cout << "Max flow is " << -graph.getVertex(0).excess() << "\n";
	// int i = 0;

	// graph.print();
	// std::vector<Vertex> data;
	// using namespace std::placeholders;
	// assign(std::bind(addEdge, std::ref(data), _1, _2));
	return 0;
}
 