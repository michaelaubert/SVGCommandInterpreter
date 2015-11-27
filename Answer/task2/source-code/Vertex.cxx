#include "Vertex.h"

Vertex::Vertex(int aX, int aY): iX(aX), iY(aY) {
}

Vertex::~Vertex() {
}

int Vertex::SquaredDistanceFrom(const Vertex& aOrigin) const {
    return ((GetX() - aOrigin.GetX()) * (GetX() - aOrigin.GetX())) + ((GetY() - aOrigin.GetY()) * (GetY() - aOrigin.GetY()));
}

inline int Vertex::GetX() const {
    return iX;
}

inline int Vertex::GetY() const {
    return iY;
}