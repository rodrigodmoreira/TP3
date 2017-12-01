#include "scene.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>

// Retorna **true** se o objeto tem interseção com o raio ou
// **false**, do contrário.
//
// Além do valor retornado, caso exista interseção,
// este método preenche _ray_ com informações cosbre o ponto
// de colisão:
//   - ray.intersectionPoint, contendo o ponto (x,y,z) de interseção
//   - ray.intersectionNormal, contendo o vetor normal do objeto no
//     ponto de interseção. A normal deve ser **normalizada** (norma = 1)
RayResponse Object::intersectsWith(Ray& ray) {
    Vector3 u = ray.v.normalized();
    Vector3 p = this->position.diff(ray.p0);
    double a = 1;
    double b = (-2) * u.dotProduct(p);
    double c = p.dotProduct(p) - pow(this->radius, 2);
    double delta = pow(b, 2) - 4*a*c;
    double root1, root2;
    bool hitFromInside = false;

    // Inicia uma resposta com um "intersects" falso,
    // indicando que não houve interseção
    RayResponse response = {
        false
    };

    if (delta < -TINY) {
        return response;
    } else if (delta > TINY) {
        // duas interseções - determinar qual foi a mais próxima
        root1 = (-b - sqrt(delta))/2*a;
        root2 = (-b + sqrt(delta))/2*a;
        if (root1 > TINY) {
            response.intersected = true;
            response.intersectionT = root1;
        } else if (root2 > TINY) {
            response.intersected = true;
            response.intersectionT = root2;
            hitFromInside = true;
        } else {
            return response;
        }
    } else {
        // uma interseção
        root1 = (-b + sqrt(delta))/2*a;
        if (root1 > TINY) {
            response.intersected = true;
            response.intersectionT = root1;
        } else {
            return response;
        }
    }

    response.intersectionPoint = Vector3(u.mult(response.intersectionT).add(ray.p0));
    response.intersectionNormal = response.intersectionPoint.diff(this->position).normalized();
    if (hitFromInside) {
        response.intersectionNormal = response.intersectionNormal.mult(-1);
    }
    return response;
}

// Carrega uma cena a partir de uma descrição em arquivo
// texto (e.g, cena-simples.txt)
Scene Scene::fromFile(string fileName) {
    cout << "Carregando arquivo: " << fileName << endl;
    Scene* newScene = new Scene();
    ifstream sceneFile(fileName.c_str());

    // variáveis temporárias para leitura de arquivo
    string line;
    double doubleValues[9];
    string temp;
    stringstream iss;

    //-----------------------------------------------------------------
    // lendo a CÂMERA
    getline(sceneFile, line);
    iss << line;
    iss >> doubleValues[0] >> doubleValues[1] >> doubleValues[2];
    newScene->camera.eye = Vector3(doubleValues);
    iss.clear();

    getline(sceneFile, line);
    iss << line;
    iss >> doubleValues[0] >> doubleValues[1] >> doubleValues[2];
    newScene->camera.target = Vector3(doubleValues);
    iss.clear();

    getline(sceneFile, line);
    iss << line;
    iss >> doubleValues[0] >> doubleValues[1] >> doubleValues[2];
    newScene->camera.up = Vector3(doubleValues);
    iss.clear();

    //-----------------------------------------------------------------
    // lendo as FONTES DE LUZ
    getline(sceneFile, line);
    iss << line;
    iss >> (newScene->numLights);
    cout << "newScene->numLights: " << newScene->numLights << endl;
    newScene->lights = new Light[newScene->numLights];
    iss.clear();

    for (int i = 0; i < newScene->numLights; i++) {
        newScene->lights[i] = Light();
        // posição
        getline(sceneFile, line);
        iss << line;
        iss >> doubleValues[0] >> doubleValues[1] >> doubleValues[2] >> doubleValues[3] >> doubleValues[4] >> doubleValues[5] >> doubleValues[6] >> doubleValues[7] >> doubleValues[8];
        iss.clear();
        newScene->lights[i].position = Vector3(doubleValues[0], doubleValues[1], doubleValues[2]);
        // cor
        newScene->lights[i].color = Vector3(doubleValues[3], doubleValues[4], doubleValues[5]);
        // atenuação
        newScene->lights[i].constantAttenuation = doubleValues[6];
        newScene->lights[i].linearAttenuation = doubleValues[7];
        newScene->lights[i].quadraticAttenuation = doubleValues[8];
    }

    //-----------------------------------------------------------------
    // lendo os PIGMENTOS
    getline(sceneFile, line);
    iss << line;
    iss >> (newScene->numPygments);
    cout << "newScene->numPygments: " << newScene->numPygments << endl;
    newScene->pygments = new Pygment[newScene->numPygments];
    iss.clear();

    // ASSUMINDO SOLID
    for(int i = 0; i < newScene->numPygments; i++) {
        newScene->pygments[i] = Pygment();
        // tipo ("solid", "checker", "texmap") e cor
        getline(sceneFile, line);
        iss << line;
        iss >> temp;
        newScene->pygments[i].type = temp;
        // cor
        iss >> doubleValues[0] >> doubleValues[1] >> doubleValues[2];
        iss.clear();
        newScene->pygments[i].color1 = Vector3(doubleValues[0], doubleValues[1], doubleValues[2]);
    }


    //-----------------------------------------------------------------
    // lendo os MATERIAIS
    getline(sceneFile, line);
    iss << line;
    iss >> newScene->numMaterials;
    cout << "newScene->numMaterials: " << newScene->numMaterials << endl;
    newScene->materials = new Material[newScene->numMaterials];
    iss.clear();

    for (int i = 0; i < newScene->numMaterials; i++) {
        newScene->materials[i] = Material();
        // coeficientes
        getline(sceneFile, line);
        iss << line;
        iss >> doubleValues[0] >> doubleValues[1] >> doubleValues[2] >> doubleValues[3] >> doubleValues[4] >> doubleValues[5] >> doubleValues[6];
        newScene->materials[i].ambientCoefficient = doubleValues[0];
        newScene->materials[i].diffuseCoefficient = doubleValues[1];
        newScene->materials[i].specularCoefficient = doubleValues[2];
        newScene->materials[i].specularExponent = doubleValues[3];
        newScene->materials[i].reflectionCoefficient = doubleValues[4];
        newScene->materials[i].transmissionCoefficient = doubleValues[5];
        newScene->materials[i].snellCoefficient = doubleValues[6];
        iss.clear();
    }


    //-----------------------------------------------------------------
    // lendo os OBJETOS DA CENA
    getline(sceneFile, line);
    iss << line;
    iss >> newScene->numObjs;
    newScene->objects = new Object[newScene->numObjs];
    iss.clear();

    for (int i = 0; i < newScene->numObjs; i++) {
        newScene->objects[i] = Object();
        // índices de pigmento e acabamento
        getline(sceneFile, line);
        iss << line;
        int pygmentIndex;
        int materialIndex;
        iss >> pygmentIndex >> materialIndex;

        newScene->objects[i].pygment = &(newScene->pygments[pygmentIndex]);
        newScene->objects[i].material = &(newScene->materials[materialIndex]);

        // tipo de objeto
        iss >> newScene->objects[i].type;

        // ASSUMINDO "sphere": posição e raio
        iss >> doubleValues[0] >> doubleValues[1] >> doubleValues[2] >> doubleValues[3];
        newScene->objects[i].position = Vector3(doubleValues[0], doubleValues[1], doubleValues[2]);
        newScene->objects[i].radius = doubleValues[3];
        iss.clear();
    }


    // Calcula a base ortonormal da câmera
    newScene->camera.calculateBase();


    newScene->printDebugInfo();

    return *newScene;
}


Scene::Scene() {
}


void Scene::printDebugInfo() {
    cout << "Informacoes sobre a cena:" << endl;
    cout << "\tCamera:\n\t\teye: " << this->camera.eye.printDebugInfo() << "\n\t\ttarget: " << this->camera.target.printDebugInfo() << "\n\t\tup: " << this->camera.up.printDebugInfo() << endl;
    cout << "\tLuzes: " << this->numLights << "\n\n";
    for (int c = 0; c < this->numLights; c++) {
        cout << "\t\tposition: " << this->lights[c].position.printDebugInfo() << "\n";
        cout << "\t\tcolor: " << this->lights[c].color.printDebugInfo() << "\n";
        cout << "\t\tatenuacoes: " << this->lights[c].constantAttenuation << ", " << this->lights[c].linearAttenuation << ", " << this->lights[c].quadraticAttenuation << "\n\n";
    }
    cout << "\tPigmentos: " << this->numPygments << "\n\n";
    for (int c = 0; c < this->numPygments; c++) {
        cout << "\t\ttype: " << this->pygments[c].type << "\n";
        cout << "\t\tcolor: " << this->pygments[c].color1.printDebugInfo() << "\n";
    }
    cout << "\tMateriais: " << this->numMaterials << "\n\n";
    for (int c = 0; c < this->numMaterials; c++) {
        cout << "\t\tambiente: " << this->materials[c].ambientCoefficient << "\n";
        cout << "\t\tdifuso: " << this->materials[c].diffuseCoefficient << "\n";
        cout << "\t\tespecular: " << this->materials[c].specularCoefficient << "\n";
        cout << "\t\texpoente espec.: " << this->materials[c].specularExponent << "\n";
        cout << "\t\tindice reflex.: " << this->materials[c].reflectionCoefficient << "\n";
        cout << "\t\tindice refrac.: " << this->materials[c].transmissionCoefficient << "\n";
        cout << "\t\tsnell: " << this->materials[c].snellCoefficient << "\n";
    }
    cout << "\tObjetos: " << this->numObjs << "\n\n";
    for (int c = 0; c < this->numObjs; c++) {
        cout << "\t\ttype: " << this->objects[c].type << "\n";
        cout << "\t\tposition: " << this->objects[c].position.printDebugInfo() << "\n";
        cout << "\t\traio: " << this->objects[c].radius << "\n\n";
    }
}

// MÉTODO calcula a base ortonormal da câmera considerando:
//   1. Vetor eye (posição do olho)
//   2. Vetor target (pra onde está olhando)
//   3. Vetor up (vetor "pra cima")
void Camera::calculateBase() {
    Vector3 targetVector = this->target.diff(this->eye);
    targetVector.normalize();
    targetVector.mult(-1);
    this->cameraBaseZ = Vector3(targetVector);

    this->cameraBaseX = Vector3(this->up.cross(this->cameraBaseZ));
    this->cameraBaseX.normalize();

    this->cameraBaseY = Vector3(this->cameraBaseZ.cross(this->cameraBaseX));
}
