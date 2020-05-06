#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "IScene.h"
#include "IInput.h"
#include "shaders/Shader.h"
#include "GameObject.h"
#include "shaders/shader.h"
#include "camerar.h"
#include "ModelLoader.h"
#include "GameObjectModelLoadedFactory.h"
#include "ParallelogramLoader.h"

class SpaceGenerator {
public:
    std::vector<glm::vec4>* PlanetCoordCreate(int num)
    {
        std::vector<glm::vec4> *planetD = new std::vector<glm::vec4>();
        for (int i = 0; i < num; i++)
        {
            glm::vec4 temp;
            temp.x = rndFloat(-10.00f, 10.0f);
            temp.y = rndFloat(-10.00f, 10.0f);
            temp.z = rndFloat(-10.00f, 10.0f);
            temp.w = rndFloat(0.1f, 1.0f);
            planetD->push_back(temp);
        }
        return planetD;
    }
private:
    uint32_t nProcGen = 0;

    float rndFloat(float min, float max)
    {
        return ((float)rnd() / (float)(0x7FFFFFFF)) * (max - min) + min;
    }

    int rndInt(int min, int max)
    {
        return (rnd() % (max - min)) + min;
    }

    uint32_t rnd()
    {
        nProcGen += 0xe120fc15;
        uint64_t tmp;
        tmp = (uint64_t)nProcGen * 0x4a39b70d;
        uint32_t m1 = (tmp >> 32) ^ tmp;
        tmp = (uint64_t)m1 * 0x12fad5c9;
        uint32_t m2 = (tmp >> 32) ^ tmp;
        return m2;
    }


};

