#pragma once
#include "GameObject.h"

class Cube : public GameObject
{
public:
	Cube(vector<Mesh> meshes) { this->meshes = meshes; }
	~Cube() {}

private:

};