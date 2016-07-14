#include "Edge.h"

// using std::map;
using std::make_pair;
// using std::weak_ptr;

// std::map<std::pair<int,int>, std::shared_ptr<Edge>> Edge::edgeMap; //create Edge Map
struct FlowError : std::exception {
  const char* what() const noexcept {return "Error trying to access an edge that does not exist";}
};

int Edge::getCapacity()
{
	return currentCapacity
;}
void Edge::push(int amount)
{
	//why do I need to do anything with vertex
	if(amount < 0 && currentCapacity <0)
	throw FlowError();
	currentCapacity -= amount;
	std::cout << "Pushed " << amount << " on edge from " << u << " to " << v << "\n";
}
std::shared_ptr<Edge> Edge::createEdge(int capacity, int u, int v)
{
	std::shared_ptr<Edge> sh(new Edge(capacity, u, v));
	// Edge::edgeMap.emplace(std::make_pair(u,v),  sh));
	return sh;
}

struct EdgeError : std::exception {
  const char* what() const noexcept {return "Error trying to access an edge that does not exist";}
};

// weak_ptr<Edge> Edge::getEdge(int u, int v)
// {
// 	auto it = Edge::edgeMap.find(std::make_pair(u,v));
// 	if(it == Edge::edgeMap.end()) throw EdgeError();
// 	return it->second;
// }

int operator+(int value, std::shared_ptr<Edge> e)
{
	return value + e->capacity;
}