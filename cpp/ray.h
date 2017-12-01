#ifndef __RAY_H__
#define __RAY_H__

#include "scene.h"

struct Ray {
    // Ponto de origem do raio (ponteiro, atribuir usando "new": ray.p0 = new Vector3(...))
    Vector3 p0;
    // Vetor de direção do raio (ponteiro)
    Vector3 v;
};


struct RayResponse {
    // Indica se houve interseção com algum objeto
    bool intersected;
    // O valor de "t" do raio para quando houve interseção.
    // Se tiver acontecido duas interseções (raio entrou e saiu), guarda o menor valor.
    double intersectionT;
    // O ponto (x,y,z) da superfície do objeto onde houve a interseção no valor de "t" igual a "intersectionT"
    Vector3 intersectionPoint;
    // O vetor normal do objeto atingido, calculado no ponto de interseção ("intersectionPoint")
    Vector3 intersectionNormal;
};

#endif

