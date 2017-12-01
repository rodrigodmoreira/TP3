#include "raytracer.h"
#include "vector.h"
#include <limits>

#include <iostream>
#include <cmath>

using namespace std;


// MÉTODO que gera um "raio inicial" (ou primário): aquele que parte do olho (câmera) e passa pelo pixel (i,j)
Ray RayTracer::generateInitialRay(Camera& camera, int row, int column, const int height, const int width) {
    Vector3 gridPointInCameraSpace = Vector3(column - width/2.0f, row - height/2.0f, -1);
    Ray ray;
    ray.p0 = camera.eye;
    ray.v = Vector3(gridPointInCameraSpace.diff(ray.p0));
    ray.v.normalize();
    return ray;
}

Vector3 RayTracer::castRay(Scene& scene, Ray& ray) {
    // Para todos os objetos da cena, verifica se o raio o acerta e pega aquele
    // que foi atingido primeiro (menor "t")
    RayResponse closestIntersection = {
        false, numeric_limits<double>::max()
    };
    Object* closestObjectHit = NULL;
    for (int c = 0; c < scene.numObjs; c++) {
        Object* currentObject = &(scene.objects[c]);
        RayResponse response = currentObject->intersectsWith(ray);
        if (response.intersected) {
            if (response.intersectionT < closestIntersection.intersectionT) {
                closestIntersection = response;
                closestObjectHit = currentObject;
            }
        }
    }


    // Verifica se um objeto foi atingido. Se tiver sido, colore o pixel
    if (closestObjectHit != NULL) {
        // Um objeto foi atingido. Vamos descobrir sua cor no ponto de
        // interseção do raio

        // material e pigmento do objeto atingido
        Material* material= closestObjectHit->material;
        Pygment* pygment = closestObjectHit->pygment;

        // Esta é a variável contendo a COR RESULTANTE do pixel,
        // que deve ser devidamente calculada e retornada ao final
        // deste método (castRay)
        Vector3 shadingColor = Vector3(1,1,1);

        //---------------------------------------------------------------------------------------------------------
        // Aqui começamos a implementar a equaçăo de Phong (e armazenar o resultado parcial em shadingColor)
        // Sugiro seguir as anotaçőes do prof. David Mount (p. 83)
        // ---
        // Exercício 1: Coloque a componente ambiente  na cor resultante
        // luz ambiente: coefAmbienteLuz*corMat (1 linha)

        shadingColor = shadingColor.mult(closestObjectHit->material->ambientCoefficient);
        shadingColor = shadingColor.cwMult(closestObjectHit->pygment->color1);

        // Agora, precisamos saber se as fontes de luz estão iluminando
        // este ponto do objeto
        for (int c = 0; c < scene.numLights; c++) {
            Light* light = &(scene.lights[c]);

            // Para verificar,
            // ---
            // Exercício 2: crie um raio do ponto de interseção com o
            //   objeto até a fonte de luz (basta instanciar devidamente
            //   um Ray, ~4 linhas)
            
            Ray raioLight = {closestIntersection.intersectionPoint , (light->position.diff(closestIntersection.intersectionPoint)).normalized()};

            // Verificamos se o raio atinge algum objeto ANTES da fonte de
            //   luz
            // Se for o caso, esta fonte de luz não contribui para a luz
            //   do objeto
            bool hitsAnotherObjectBeforeLight = false;
            // ---
            // Exercício 3: Percorra os objetos da cena verificando se
            //   houve interseção com eles, antes da interseção com a
            //   fonte luminosa
            // Salve essa informação na variável
            //   hitsAnotherObjectBeforeLight (~10 linhas)
            for(int n_obj = 0; n_obj < scene.numObjs; n_obj++)
            {
                Object* currentObject = &(scene.objects[n_obj]);
                RayResponse response = currentObject->intersectsWith(raioLight);
                if (response.intersected) {
                    hitsAnotherObjectBeforeLight = true;
                    break;
                }
            }

            if (!hitsAnotherObjectBeforeLight) {
                // ---
                // Exercício 4: Devemos terminar de calcular a equaçăo
                //   de Phong (atenuação, componente difusa e componente
                //   especular) e somar o resultado na cor resultante
                //   (na variável shadingColor, ~15 linhas)

                // 2º termo
                double d = (light->position.diff(closestIntersection.intersectionPoint)).norm(); // light-intersection point distance

                double attenuation = 1/(light->constantAttenuation + light->linearAttenuation*d + light->quadraticAttenuation*d*d);
                Vector3 lightLight = (light->color).mult(attenuation); // Light color term

                double dotProductNxL = (closestIntersection.intersectionNormal.normalized()).dotProduct(raioLight.v.normalized());
                if(dotProductNxL<0) dotProductNxL = 0;
                Vector3 diffuseTerm = (closestObjectHit->pygment->color1.mult(closestObjectHit->material->diffuseCoefficient)).mult(dotProductNxL);

                Vector3 viewV = ((closestObjectHit->position).diff(ray.p0)).normalized();
                Vector3 lightV = ((light->position).diff(closestObjectHit->position)).normalized();
                Vector3 halfwayV = (lightV.add(viewV)).normalized();
                double dotProductNxH = (closestIntersection.intersectionNormal.normalized()).dotProduct(halfwayV);
                if(dotProductNxH<0) dotProductNxH = 0;
                double specularTerm = closestObjectHit->material->specularCoefficient*pow(dotProductNxH,closestObjectHit->material->specularExponent);
                
                lightLight = lightLight.cwMult(diffuseTerm.add(specularTerm));
                

                shadingColor = shadingColor.add( lightLight );

            }
        }

        // trunca a cor: faz r, g e b ficarem entre 0 e 1, caso tenha excedido
        shadingColor.truncate();
        return shadingColor;
    }

    // nada foi atingido. Retorna uma cor padrão (de fundo)
    return Vector3(0, 0, 0);
}


// MÉTODO que renderiza uma cena, gerando uma matriz de cores.
// Parâmetros:
//   1. Scene& scene: um objeto do tipo Scene contendo a descrição da cena (ver scene.h)
//   2. Vector3** pixels: uma matriz de cores (representadas em Vector3 - r,g,b) que vamos "colorir"
//   3. const int height: altura da imagem que estamos gerando (e.g., 600px)
//   4. const int width: largura da imagem que estamos gerando (e.g., 800px)
void RayTracer::renderScene(Scene& scene, Vector3** pixels, const int height, const int width) {

    // Para cada pixel, lança um raio
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // cria um raio primário
            Ray ray = generateInitialRay(scene.camera, i, j, height, width);

            // lança o raio e recebe a cor
            Vector3 color = this->castRay(scene, ray);

            // salva a cor na matriz de cores
            pixels[i][j] = color;
        }
    }
}
