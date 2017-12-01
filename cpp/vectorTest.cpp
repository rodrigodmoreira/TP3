#include <assert.h>
#include <stdio.h>
#include "vector.h"

void assertSum() {
    Vector3 a(5, 5, 5), b(1,1,1);
    Vector3 c = a.add(b);
    assert(c.x == 6);
    assert(c.y == 6);
    assert(c.z == 6);

    Vector3 d = a.add(20);
    assert(d.x == 25);
    assert(d.y == 25);
    assert(d.z == 25);
}

void assertDiff() {
    Vector3 a(5, 5, 5), b(1, 1, 1);
    Vector3 c = a.diff(b);
    assert(c.x == 4);
    assert(c.y == 4);
    assert(c.z == 4);

    Vector3 d = a.diff(4);
    assert(d.x == 1);
    assert(d.y == 1);
    assert(d.z == 1);
}

void assertCross() {
    Vector3 a(1, 0, 0), b(0, 1, 0);
    Vector3 c = a.cross(b);
    assert(c.x == 0);
    assert(c.y == 0);
    assert(c.z == 1);

    Vector3 d = b.cross(a);
    assert(d.x == 0);
    assert(d.y == 0);
    assert(d.z == -1);
}

void assertDotProduct() {
    Vector3 a(1, 0, 0), b(0, 1, 0);
    double res = a.dotProduct(b);
    assert(res == 0);
}

void assertNorm() {
    Vector3 a(1, 0, 0), b(0, 5, 0);
    assert(a.norm() == 1.0f);
    assert(b.norm() == 5.0f);
}

void assertNormalize() {
    Vector3 a(200, 0, 0);
    a.normalize();
    assert(a.norm() == 1.0f);
}

int mainVector(int argc, char* argv[]) {
    try {
        assertSum();
        assertDiff();
        assertCross();
        assertDotProduct();
        assertNorm();
        assertNormalize();
        return 0;
    } catch (int e) {
        return -1;
    }

    return 0;
}
