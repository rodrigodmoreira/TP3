#include "scene.h"
#include "ray.h"

class RayTracer {

private:
    Vector3 castRay(Scene& scene, Ray& ray);
    Ray generateInitialRay(Camera& camera, int row, int column, const int height, const int width);

public:
    void renderScene(Scene& scene, Vector3**, const int height, const int width);
};
