#ifndef EDGE_H
#define EDGE_H
// #include <map>
#include <utility> //pair
#include <memory> //shared_ptr, weak_ptr
#include <iostream>
//Edge Methods

class Edge
{
public:
	bool isBlocked() const{return blocked;}
	void block(){blocked = true;}
	void unblock(){blocked = false;}
	int getCapacity();
	void push(int amount);
	inline int getOrigin() {return u; }
	inline int getDest() { return v;}
	inline int getFlow()
	{
		if(currentCapacity < 0) return currentCapacity;
		return capacity - currentCapacity;
	}
	static std::shared_ptr<Edge> createEdge(int capacity, int u, int v);
	// static std::weak_ptr<Edge> getEdge(int u, int v);
	friend int operator+(int value, std::shared_ptr<Edge> e);
	friend std::ostream& operator <<(std::ostream& os, Edge & e)
	{
		os << "Edge from " << e.u << " to " << e.v << " with capacity " << e.capacity << "\n";
		return os;
	}
private:
	Edge(int capacity_, int u_, int v_): capacity(capacity_), currentCapacity(capacity_), u(u_), v(v_), blocked(false){}
	int capacity;
	int currentCapacity;
	int u;
	int v;
	bool blocked;
	// static std::map<std::pair<int,int>, std::shared_ptr<Edge>> edgeMap; //unordered_map has no defined hash function for pairs...
};

#endif