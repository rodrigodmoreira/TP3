#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cmath>
#include <string>

using namespace std;

/**
  * Este arquivo (.h) descreve 2 classes:
  *	  - Vector3: vetor de tamanho 3 (só este será necessário na primeira parte (15/01/15))
  *   - Vector4: vetor de tamanho 4
  *
  * O que é uma classe?
  *    - Apenas uma struct, mas que também pode conter funções (o nome certo passa a ser "método")
  *    - Para criar um objeto à partir de um struct em C:
  *		    struct Pessoa {
  *           char nome[50];
  *           int idade;
  *         }
  *         Pessoa professor;
  *         professor.nome = "Flavio";
  *         professor.idade = 18;
  *	   - Para criar um objeto à partir de uma classe em C++, há duas formas:
  *         class Pessoa {
  *           char nome[50];
  *           int idade;
  *         public:
  *           Pessoa(char nome[50], int idade) {
  *				this->nome = nome;
  *				this->idade = idade;
  *         }
  *         Pessoa professor = Professor("Flavio", 18);
  *			// ou então, via ponteiro e usando "new"
  *			Pessoa* professor = new Professor("Flavio", 18);
  */

class Vector3 {

public:
    union {
        double components[3];
        struct {
            double x, y, z;
        };
        struct {
            double r, g, b;
        };
    };


    // construtores
    Vector3(double, double, double);
    Vector3(double[]);
    Vector3(const Vector3&);
    Vector3() {}

    // operações
    Vector3 add(const Vector3&);			// imutável (não altera o Vector3, apenas retorna o resultado)
    Vector3 add(const double);			// imutável
    Vector3 diff(const Vector3&);			// imutável
    Vector3 diff(const double);			// imutável
    Vector3 mult(const double);			// imutável
    Vector3 cwMult(const Vector3);       // imutável
    Vector3 cwDiv(const Vector3);       // imutável
    Vector3 cross(const Vector3&);		// imutável
    double dotProduct(const Vector3&);	// imutável
    double norm();					// imutável
    Vector3 normalized();			// imutável
    void normalize();				// mutável  (altera o Vector3 e não retorna nada)
    void truncate();				// mutável

    string printDebugInfo();

};



class Vector4 {
public:
    union {
        double components[4];
        struct {
            double x, y, z, w;
        };
        struct {
            double r, g, b, a;
        };
    };

    // construtores
    Vector4(double, double, double, double);
    Vector4(double[]);
    Vector4() {};

    // operações
    Vector4 add(Vector4&);			// imutável
    Vector4 add(double);			// imutável
    Vector4 diff(Vector4&);			// imutável
    Vector4 diff(double);			// imutável
    double dotProduct(Vector4&);	// imutável
    double norm();					// imutável
    void normalize();				// mutável
};


#endif
