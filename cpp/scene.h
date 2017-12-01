#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include "vector.h"
#include "ray.h"
using namespace std;

// A classe Scene contém informações sobre:
//	1. A câmera
//	2. Luzes
//	3. Pigmentos (texturas)
//	4. Acabamentos (materiais)
//	5. Objetos
const double TINY = 1E-3;

struct Camera {
    Vector3 eye;
    Vector3 target;
    Vector3 up;

    // MÉTODO que calcula a base ortornomal da câmera
    // Ele preenche os vetores cameraBase{X,Y,Z} de acordo com os vetores eye, target e up.
    void calculateBase();

    // base ortonormal da câmera (sistema de coords.)
    Vector3 cameraBaseX;
    Vector3 cameraBaseY;
    Vector3 cameraBaseZ;
};

struct Light {
    // Posição da luz (x,y,z)
    Vector3 position;
    // Cor da luz em (r,g,b)
    Vector3 color;

    // Coeficientes de atenuação da luz de acordo com a distância até o objeto
    double constantAttenuation;
    double linearAttenuation;
    double quadraticAttenuation;
};

struct Pygment {
    string type;			// "solid", ou "checker" ou "texmap"
    Vector3 color1;			// usado por "solid" e "checker"
    Vector3 color2;			// usado por "checker"
    double checkerLength;	// usado por "checker"
    string fileName;		// usado por "texmap"
    Vector4 p1;				// usado por "texmap"
    Vector4 p2;				// usado por "texmap"
};

struct Material {
    double ambientCoefficient;
    double diffuseCoefficient;
    double specularCoefficient;
    double specularExponent;

    double reflectionCoefficient;
    double transmissionCoefficient;
    double snellCoefficient;
};

struct ObjectFace {
    Vector4 plane;
};

struct Object {
    Pygment* pygment;
    Material* material;
    string type;			// "sphere" ou "polyhedron"
    Vector3 position;		// usado por "sphere"
    double radius;			// usado por "sphere"
    ObjectFace faces;		// usado por "polyhedron"

    RayResponse intersectsWith(Ray& ray);
};

class Scene {
public:
    Camera camera;

    int numLights;
    Light* lights;

    int numPygments;
    Pygment* pygments;

    int numMaterials;
    Material* materials;

    int numObjs;
    Object* objects;


    // builder
    static Scene fromFile(string);

private:
    // construtor privado - impede "new Scene()"
    Scene();

    void printDebugInfo();
};

#endif
