#include "scene.h"
#include "raytracer.h"
#include "output.h"
#include <iostream>
#include <sstream>
using namespace std;

#define WIDTH 800
#define HEIGHT 600

void printHelp() {
    cout << "Funcionamento do programa:" << '\n'
         << '\n'
         << "- Windows:" << '\n'
         << "\t raytracer.exe arquivo-de-cena.txt" << '\n'
         << '\n'
         << "- Linux/OSX:" << '\n'
         << "\t ./raytracer arquivo-de-cena.txt" << '\n'
         << '\n'
         << '\n'
         << "Possivelmente o programa foi executado sem os devidos parâmetro(s)" << '\n'
         << endl;
}

string baseFileName(string const& path) {
  return path.substr(path.find_last_of("/\\") + 1);
}

string removeExtension(string const& filename) {
  const int p = filename.find_last_of('.');
  return p > 0 ? filename.substr(0, p) : filename;
}

int main(int argc, char* argv[]) {
    // Carrega cena do arquivo cujo nome foi passado como o primeiro parâmetro
    if (argc < 2) {
        printHelp();
    }
    Scene s = Scene::fromFile(argv[1]);
    RayTracer raytracer;


    // Matriz de pixels que serão "coloridos"
    Vector3** pixels = new Vector3*[HEIGHT];
    for (int i = 0; i < HEIGHT; i++) {
        pixels[i] = new Vector3[WIDTH];
    }
    raytracer.renderScene(s, pixels, HEIGHT, WIDTH);


    // Transforma os pixels de double (0..1) para byte (0..255)
    unsigned char* buffer = new unsigned char[HEIGHT * (3 * WIDTH)];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            Vector3* p = &(pixels[i][j]);
            buffer[i*WIDTH*3 + j*3+0] = min((int)(p->r * 255), 255);
            buffer[i*WIDTH*3 + j*3+1] = min((int)(p->g * 255), 255);
            buffer[i*WIDTH*3 + j*3+2] = min((int)(p->b * 255), 255);
        }
    }


    // Escreve um arquivo ppm e outro bmp
    string outputName = removeExtension(baseFileName(string(argv[1])));
    cout << "Salvando arquivos: " << outputName << ".bmp e " << outputName << ".ppm" << endl;
    stringstream bmp, ppm;
    bmp << outputName << string(".bmp");
    ppm << outputName << string(".ppm");

    writeImageBmp(bmp.str().c_str(), WIDTH, HEIGHT, buffer);
    writeImagePpm(ppm.str().c_str(), WIDTH, HEIGHT, buffer);

    return 0;
}
