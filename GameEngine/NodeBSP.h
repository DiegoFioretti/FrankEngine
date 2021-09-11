#pragma once
#include <list>
#include "Model.h"

class NodeBSP
{
private:
	static const unsigned int depth_max = 32;
	static const unsigned int max_models = 32; 
	
	const unsigned int depth;
	const vec3 min, max, center;	// Geometría del nodo
	list<Model*> models;			// Contenedor para referencia de modelos
	NodeBSP* children[2];			// Solo se construye si el contenedor esta lleno

	NodeBSP(NodeBSP const&, bool);	// Constructor para chear un hijo
	bool isEmpty() const;			// Checkea si el hijo tambien esta vacio
public:
	NodeBSP(vec3 min, vec3 max);		// Constructor del primer nodo
	~NodeBSP();						// Destructor

	void addModel(vec3 position, Model *);
	void delModel(Model*);
	void movModel(vec3 newPos, Model*);

	// Consigue todos los modelos en el campo requerido
	void getModel(vec3 posMin, vec3 posMax, list<Model*>&);
};

