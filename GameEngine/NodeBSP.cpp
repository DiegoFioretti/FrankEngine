#include "NodeBSP.h"

vec3 middle(const vec3& a, const vec3& b) 
{
	vec3 ref;
	ref.x = (a.x + b.x) / 2;
	ref.y = (a.y + b.y) / 2;
	ref.z = (a.z + b.z) / 2;
	return ref;
}

// COnstructor publico para el nodo principal
NodeBSP::NodeBSP(vec3 min, vec3 max):depth(0), min(min), max(max), center(middle(min,max)), models(), children(){}

NodeBSP::~NodeBSP() 
{
	delete[] children;
}

// Contructor privado para construir a los hijos
// Calcula su propio centro y rango de acuerdo al indicador de lado
// El lado especifica cual lado del padre el hijo representa
NodeBSP::NodeBSP(NodeBSP const& father, bool side)
	: depth(father.depth + 1),
	min(side ? father.min : father.center),
	max(side ? father.center : father.max),
	center(middle(min, max)),
	models(),
	children(){}

bool NodeBSP::isEmpty() const
{
	return !((models.empty()) || children || (children[0]->isEmpty() && children[1]->isEmpty()));
}

void NodeBSP::addModel(vec3 position, Model* mod)
{
	if (models.size() > max_models && depth < depth_max)
	{	// Si se llego al limite de modelos pero no de profundidad
		if (children == nullptr)
		{	// Si se necesitan crear hijos
			//children = new NodeBSP(*this, false), NodBSP(*this, true) };
		}
	}
}

void NodeBSP::delModel(Model* mod)
{
	
}

void NodeBSP::movModel(vec3 newPos, Model* mod)
{

}

void NodeBSP::getModel(vec3 posMin, vec3 posMax, list<Model*>& list)
{

}