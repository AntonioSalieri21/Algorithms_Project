#include "Graph.h"

using namespace std;

void Graph::insertVertex(int id)
{
	this->vertices.push_back(new Vertex(id));
}
void Graph::insertVertex(Vertex* vertex) 
{ 

	this->vertices.push_back(vertex);
	vertex->index = vertices.size() - 1;
}

void Graph::readGraphFromFile(string path)
{
	string vertex_pair;
	ifstream file(path);

	int searchCount = 0;
	int addCount = 0;
	while (getline(file, vertex_pair))
	{
		int a = 0;
		int b = 0;
		getDoubleInt(vertex_pair, a, b);

		Vertex* v_a = searchTree.searchBST(a);
		Vertex* v_b = searchTree.searchBST(b);

		if (v_a == nullptr)
		{
			v_a = searchTree.InsertBST(a);
			insertVertex(v_a);
		}
		if (v_b == nullptr)
		{
			v_b = searchTree.InsertBST(b);
			insertVertex(v_b);
		}
			

		v_b->neighbours.push_back(v_a);
		v_a->neighbours.push_back(v_b);

	}

	file.close();

}

Graph::Component* Graph::getLargestComponent()
{

	for (auto vertex : vertices)
	{
		if (vertex->color == 0)
			components.push_back(defineComponent(vertex));
	}

	Component* res = &components.at(0);

	for(auto component : components)
		if (component.members.size() > res->members.size()) { res = &component; }

	for (int i = 0; i < res->members.size(); i++)
	{
		res->members.at(i)->index = i;
	}

	return res;
}

Graph::Component Graph::defineComponent(Vertex* startVertex)
{
	Component comp;

	Vertex* current = startVertex;
	stack<Vertex*> stack;

	stack.push(current);
	current->color = 1;

	while (!stack.empty())
	{
		current = stack.top();
		comp.members.push_back(current);
		stack.pop();

		//cout << current->id << endl;

		current->color = 2;

		for (auto neighbour : current->neighbours)
		{
			if (neighbour->color == 0)
			{
				stack.push(neighbour);
				neighbour->color = 1;
			}
		}
	}

	return comp;
}

void Graph::print()
{
	for (auto vertex : vertices)
	{
		cout << vertex->id;
		for (auto neighbour : vertex->neighbours)
			cout << "   " << neighbour->id;

		cout << endl;
	}

}



