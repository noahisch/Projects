#include "Vertex.h"
#include "Edge.h" //edge methods
#include <algorithm>

#include <iostream>
using std::cout;
using std::deque;
using std::shared_ptr;
using std::find;
using std::copy_if;
using std::for_each;

inline int min(int a, int b)
{
	return a < b ? a : b;
}

// std::function<void(int, std::shared_ptr<Edge>)> addOutEdge;
std::function<Vertex &(int)> getVertex;
std::function<LayeredVertex &(int)> getLayeredVertex;


void assign(std::function<Vertex &(int)> f, std::function<LayeredVertex&(int)> b)
{
	getVertex = f;
	getLayeredVertex = b;
}

int Vertex::global_index = 0;

Vertex::Vertex():index(global_index++), blocked(false){}

void Vertex::addEdge(int dest, int capcity)
{
	auto edge = Edge::createEdge(capcity, index, dest);
	out.push_back(edge);
	getVertex(dest).addInEdge(edge);
	// addOutEdge(dest, edge);
}

void Vertex::addInEdge(std::shared_ptr<Edge> e)
{
	in.push_back(e);
}

int Vertex::excess()
{
	int inFlow = 0;
	int outFlow = 0;
	for(auto x : in)
	{
		inFlow += x->getFlow();
	}
	for(auto x : out)
	{
		outFlow += x->getFlow();
	}
	return inFlow - outFlow;
}
deque<shared_ptr<Edge>> Vertex::available()
{
	auto output = out;
	// cout << out.size();
	output.erase(std::remove_if(output.begin(), output.end(), [](shared_ptr<Edge> e){return e->getCapacity() == 0 || e->isBlocked();}), output.end());
	// cout << output.size();
	return output;
}

void Vertex::sPush()
{
	auto availableEdges = available();
	int sExcess = 0;
	for(auto x : out)
	{
		sExcess += x->getCapacity();
	}
	while(sExcess > 0 && !availableEdges.empty())
	{
		auto e = availableEdges.front();
		int q = min(e->getCapacity(), sExcess);
		getVertex(e->getDest()).Stack.push(std::make_pair(e, q));
		e->push(q);
		if(e->getCapacity() == 0) availableEdges.pop_front();
	}
	if(availableEdges.empty())
	{
		blocked = true;
		for(auto x : in)
		{
			x->block();
		}
	}
}

void Vertex::push()
{
	auto availableEdges = available();
	while(excess() > 0 && !availableEdges.empty())
	{
		auto e = availableEdges.front();
		int q = min(e->getCapacity(), excess());
		getVertex(e->getDest()).Stack.push(std::make_pair(e, q));
		e->push(q);
		if(e->getCapacity() == 0) availableEdges.pop_front();
	}
	if(availableEdges.empty())
	{
		blocked = true;
		for(auto x : in)
		{
			x->block();
		}
	}
}

bool Vertex::done()
	{
		for(auto x : out)
		{
			if(!x->isBlocked()) return false;
		}
		return true;
	}

void Vertex::returnPush()
{
	while(excess() > 0)
	{
		if(Stack.empty()) cout << "STACK IS EMPTY, ABORT\n";
		auto Q = Stack.top();
		int q = min(Q.second, excess());
		Q.first->push(-q);
		if(q == Q.second)
		{
			Stack.pop();
		}
		else{
			Stack.pop();
			Q.second -= q;
			Stack.push(Q);
		}
	}
}

void LayeredVertex::excessHelper()
{
	int inFlow = 0;
	int outFlow = 0;
	for(auto x : in)
	{
		inFlow += x->getFlow();
	}
	for(auto x : out)
	{
		outFlow += x->getFlow();
	}
	excess = inFlow - outFlow;
}
void LayeredVertex::availableHelper()
{
	available = out;
	available.erase(std::remove_if(available.begin(), available.end(), [](shared_ptr<Edge> e){return e->getCapacity() == 0 || e->isBlocked();}), available.end());
}

LayeredVertex::LayeredVertex(Vertex & vertex_): vertex(vertex_), index(vertex_.index), blocked(vertex_.blocked)
{
	copyEdgeHolder(out, vertex.out, [](shared_ptr<Edge> e) {return e->getCapacity() != 0;});
	copyEdgeHolder(in, vertex.in, [](shared_ptr<Edge> e) {return e->getCapacity() != 0;});
	excessHelper();
	availableHelper();
}
void LayeredVertex::modifyEdges(const std::set<int>& nextLayer)
{
	int tmp = index;
	out.erase(remove_if(out.begin(), out.end(), [tmp, nextLayer](shared_ptr<Edge> e) { 
		if(nextLayer.count(e->getDest()) == 0) 
		{
			getLayeredVertex(e->getDest()).removeIn(tmp);
			return true;
		}
		return false;
		}), out.end());
}
void LayeredVertex::removeIn(int index)
{
	in.erase(find_if(in.begin(), in.end(), [index](shared_ptr<Edge> e){return e->getOrigin() == index;}));
}
void LayeredVertex::push()
{
	while(excess > 0 && !available.empty())
	{
		auto e = available.front();
		while(e->isBlocked())
		{
			available.pop_front();
			if(available.empty()) break;
			e = available.front();
		}
		if(available.empty()) break;
		int q = min(e->getCapacity(), excess);
		getLayeredVertex(e->getDest()).Stack.push(std::make_pair(e, q));
		e->push(q);
		excess -= q;
		getLayeredVertex(e->getDest()).excess += q;
		if(e->getCapacity() == 0) available.pop_front();
	}
	if(available.empty())
	{
		blocked = true;
		for(auto x : in)
		{
			x->block();
		}
	}
}
void LayeredVertex::returnPush()
{
	while(excess > 0)
	{
		if(Stack.empty()) cout << "STACK IS EMPTY, ABORT\n";
		auto Q = Stack.top();
		auto e = Q.first;
		int q = min(Q.second, excess);
		excess -= q;
		getLayeredVertex(e->getOrigin()).excess += q;
		e->push(-q);
		if(q == Q.second)
		{
			Stack.pop();
		}
		else{
			Stack.pop();
			Q.second -= q;
			Stack.push(Q);
		}
	}
}
bool LayeredVertex::isBlocked()
{
	return blocked;
}

void LayeredVertex::pushMax()
{
	
	excess = 0;
	for(auto x : out)
	{
		excess += x->getCapacity();
	}
	push();
}

std::set<int> LayeredVertex::getNextLayer()
{
	std::set<int> s;
	for_each(out.begin(), out.end(), [&s](auto e){s.insert(e->getDest());});
	return s;
}

void LayeredVertex::copyEdgeHolder(EdgeHolder & eh, const EdgeHolder & orig, std::function<bool(std::shared_ptr<Edge>)> f)
{
	eh.resize(orig.size());
	auto it = copy_if(orig.begin(), orig.end(), eh.begin(), f);
	eh.resize(std::distance(out.begin(), it));
}
// private:
// 	Vertex & vertex;
// 	std::deque<std::shared_ptr<Edge>> out;
// 	std::deque<std::shared_ptr<Edge>> in;
// 	int excess;
// };