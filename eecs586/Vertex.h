#ifndef VERTEX_H
#define VERTEX_H
 
#include <queue>
#include <memory> //weak_ptr
#include <functional>
#include <stack>
#include <set>
//forward declartion
class Edge;
using EdgeHolder = std::deque<std::shared_ptr<Edge>>;
//need a flow quantum
// void (*addOutEdge)(int dest, std::shared_ptr<Edge> e); //takes input (u, v)
// std::function<void(int, std::shared_ptr<Edge>)> addOutEdge;


class Vertex
{
public:
	Vertex();//:index(++global_index), blocked(false){} //how to init edges
	void addEdge(int dest, int capcity);
	void addInEdge(std::shared_ptr<Edge> e);
	int excess();
	void sPush();
	void push();
	void returnPush();
	bool done() const;
	inline bool isBlocked(){return blocked;}
	std::deque<std::shared_ptr<Edge>> available();
	// flow_quantum stack();
private:
	//edges
	std::deque<std::shared_ptr<Edge>> out;
	std::deque<std::shared_ptr<Edge>> in;
	
	//Vertex lookup
	int index;
	static int global_index;

	bool blocked;
	using flow_quantum = std::pair<std::shared_ptr<Edge>, int>;
	std::stack<flow_quantum> Stack;

	friend class LayeredVertex;
};

class LayeredVertex
{
public:
	LayeredVertex(Vertex & vertex_);
	void modifyEdges(const std::set<int>& nextLayer);
	void push();
	void returnPush();
	bool isBlocked();
	void pushMax();
	inline int getExcess() { return excess; }
	std::set<int> getNextLayer();

private:
	Vertex & vertex;
	EdgeHolder out;
	EdgeHolder in;
	int excess;
	int index;
	std::deque<std::shared_ptr<Edge>> available;
	bool blocked;
	using flow_quantum = std::pair<std::shared_ptr<Edge>, int>;
	std::stack<flow_quantum> Stack;
	//helper functions
	void removeIn(int index);
	void copyEdgeHolder(EdgeHolder & eh, const EdgeHolder & orig, std::function<bool(std::shared_ptr<Edge>)> f);
	void excessHelper();
	void availableHelper();
	void pushHelper();
};

void assign(std::function<Vertex& (int)> f, std::function<LayeredVertex&(int)> b);

#endif