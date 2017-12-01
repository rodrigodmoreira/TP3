#include "vector.h"
#include <sstream>

/*
 * Arquivo: vector.cpp
 * Este arquivo (.cpp) contém a implementação dos métodos das classes:
 *   1. Vector3
 *   2. Vector4
 *
 *
 * Por que temos vector.h e vector.cpp?
 *   - vector.h contém apenas a descrição das classes
 *   - vector.cpp contém a implementação dos métodos
 */


// CONSTRUTOR que recebe 3 doubles como parâmetro
// Como usar:
//   Vector3 v = Vector3(10.0f, 0, 1.0f);
// ...ou com ponteiro:
//   Vector3* u = new Vector3(0, 0, 0);
Vector3::Vector3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

// CONSTRUTOR que recebe um array com 3 doubles
Vector3::Vector3(double components[3]) {
    this->components[0] = components[0];
    this->components[1] = components[1];
    this->components[2] = components[2];
}

// CONSTRUTOR que recebe outro Vector3 e cria um clone
// Como usar:
//   Vector3 v = Vector3(10.0f, 0, 1.0f);
//   Vector3 u = Vector3(v);
//
// Assim, v e u serão vetores com o mesmo (x, y, z)
Vector3::Vector3(const Vector3& other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}



// MÉTODO para adicionar um vetor ao outro.
// Como usar:
//   Vector3 a = Vector3(10, 20, 30);
//   Vector3 b = Vector3(5, 5, 5);
//   Vector3 soma = a.add(b);
//
// Ao final, soma = (15, 25, 35) e a e b continuam sendo (10, 20, 30) e (5, 5, 5) respec.
Vector3 Vector3::add(const Vector3& other) {
    return Vector3(this->x + other.x,
                   this->y + other.y,
                   this->z + other.z);
}

// MÉTODO para adicionar um escalar a cada componente do vetor.
// Como usar:
//   Vector3 a = Vector3(10, 20, 30);
//   Vector3 resultado = a.add(100);
//
// Ao final, resultado = (110, 120, 130) e a continua sendo (10, 20, 30).
Vector3 Vector3::add(const double num) {
    return Vector3(this->x + num,
                   this->y + num,
                   this->z + num);
}


// MÉTODO para subtrair um vetor do outro.
// Como usar:
//   Vector3 a = Vector3(10, 20, 30);
//   Vector3 b = Vector3(5, 5, 5);
//   Vector3 resultado = a.diff(b);
//
// Ao final, resultado = (5, 15, 25) e a e b continuam sendo (10, 20, 30) e (5, 5, 5) respec.
Vector3 Vector3::diff(const Vector3& other) {
    return Vector3(this->x - other.x,
                   this->y - other.y,
                   this->z - other.z);
}

// MÉTODO para subtrair um escalar a cada componente do vetor.
// Como usar:
//   Vector3 a = Vector3(10, 20, 30);
//   Vector3 resultado = a.diff(10);
//
// Ao final, resultado = (0, 10, 20) e a continua sendo (10, 20, 30).
Vector3 Vector3::diff(const double num) {
    return this->add(-num);
}

// MÉTODO para multiplicar um escalar a cada componente do vetor.
// Como usar:
//   Vector3 a = Vector3(10, 20, 30);
//   Vector3 resultado = a.mult(3);
//
// Ao final, resultado = (30, 60, 90) e a continua sendo (10, 20, 30).
Vector3 Vector3::mult(const double num) {
    return Vector3(this->x * num,
                   this->y * num,
                   this->z * num);
}


// MÉTODO que retorna um novo vetor que é o resultado de uma multiplicação
// componente-a-componente (component-wise) entre dois vetores.
// Como usar:
//   Vector3 a = Vector3(10, 20, 30);
//   Vector3 b = Vector3(2, 3, 4);
//   Vector3 resultado = a.mult(b);
//
// Ao final, resultado = (10*2 20*3, 30*4) e a continua sendo (10, 20, 30).
Vector3 Vector3::cwMult(const Vector3 other) {
    return Vector3(this->x * other.x,
                   this->y * other.y,
                   this->z * other.z);
}

// MÉTODO que retorna um novo vetor que é o resultado de uma divisão
// componente-a-componente (component-wise) entre dois vetores.
// Como usar:
//   Vector3 a = Vector3(10, 20, 30);
//   Vector3 b = Vector3(2, 3, 4);
//   Vector3 resultado = a.cwDiv(b);
//
// Ao final, resultado = (10*2 20*3, 30*4) e a continua sendo (10, 20, 30).
Vector3 Vector3::cwDiv(const Vector3 other) {
    return Vector3(this->x / other.x,
                   this->y / other.y,
                   this->z / other.z);
}

// MÉTODO para calcular o produto vetorial entre dois vetores (a x b).
// Como usar:
//   Vector3 a = Vector3(1, 0, 0);
//   Vector3 b = Vector3(0, 1, 0);
//   Vector3 resultado = a.cross(b);
//
// Ao final, resultado = (0, 0, 1) e a e b continuam sendo (1, 0, 0) e (0, 1, 0).
Vector3 Vector3::cross(const Vector3& other) {
    return Vector3(
        this->y*other.z - this->z*other.y,
        this->z*other.x - this->x*other.z,
        this->x*other.y - this->y*other.x
    );
}

// MÉTODO para calcular o produto interno entre dois vetores (a . b).
// Como usar:
//   Vector3 a = Vector3(1, 0, 0);
//   Vector3 b = Vector3(0, 1, 0);
//   double resultado = a.dotProduct(b);
//
// Ao final, resultado = 0.
double Vector3::dotProduct(const Vector3& other) {
    return this->x*other.x + this->y*other.y + this->z*other.z;
}

// MÉTODO para calcular a norma do vetor.
// Como usar:
//   Vector3 a = Vector3(3, 0, 0);
//   double tamanho = a.norm();
//
// Ao final, tamanho = 3.
double Vector3::norm() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

// MÉTODO que ALTERA o vetor para sua forma normalizada (tamanho=1).
// Como usar:
//   Vector3 a = Vector3(9, 0, 0);
//   a.normalize();
//
// Ao final, a = (1, 0, 0).
void Vector3::normalize() {
    double norm = this->norm();
    if (norm != 0) {
        this->x /= norm;
        this->y /= norm;
        this->z /= norm;
    }
}


// MÉTODO que retorna um novo vetor normalizado, mas sem alterar o vetor original.
// Como usar:
//   Vector3 a = Vector3(9, 0, 0);
//   Vector3 aNormalizado = a.normalized();
//
// Ao final, aNormalizado = (1, 0, 0), mas a continua sendo (9, 0, 0).
Vector3 Vector3::normalized() {
    Vector3 normalized = Vector3(*this);
    normalized.normalize();
    return normalized;
}

// MÉTODO que ALTERA o vetor, fazendo suas componentes (x,y,z) serem truncadas entre 0 e 1.
// Como usar:
//   Vector3 a = Vector3(9, -1.56f, 0.25f);
//   a.truncate();
//
// Ao final, a = (1, -1, 0.25f).
void Vector3::truncate() {
    this->x = fmin(1.0f, fmax(0, this->x));
    this->y = fmin(1.0f, fmax(0, this->y));
    this->z = fmin(1.0f, fmax(0, this->z));
}



string Vector3::printDebugInfo() {
    ostringstream result;
    result << "(" << this->x << ", " << this->y << ", " << this->z << ") ";
    return result.str();
}







/**
 * Aqui começa a implementação dos métodos da classe Vector4.
 * Eles são 100% análogos aos métodos da classe Vector3.
 */
Vector4::Vector4(double x, double y, double z, double w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Vector4::Vector4(double components[4]) {
    this->components[0] = components[0];
    this->components[1] = components[1];
    this->components[2] = components[2];
    this->components[3] = components[3];
}

Vector4 Vector4::add(Vector4& other) {
    return Vector4(this->x + other.x,
                   this->y + other.y,
                   this->z + other.z,
                   this->w + other.w);
}

Vector4 Vector4::add(double num) {
    return Vector4(this->x + num,
                   this->y + num,
                   this->z + num,
                   this->w + num);
}

Vector4 Vector4::diff(Vector4& other) {
    return Vector4(this->x - other.x,
                   this->y - other.y,
                   this->z - other.z,
                   this->w - other.w);
}

Vector4 Vector4::diff(double num) {
    return this->add(-num);
}

double Vector4::dotProduct(Vector4& other) {
    return this->x*other.x + this->y*other.y + this->z*other.z + this->w*other.w;
}

double Vector4::norm() {
    return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) + pow(this->w, 2));
}

void Vector4::normalize() {
    double norm = this->norm();
    this->x /= norm;
    this->y /= norm;
    this->z /= norm;
    this->w /= norm;
}

