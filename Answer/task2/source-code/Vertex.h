#pragma once

/**
 * A simple class for a Vertex (aka Point)
 * The only real logic is for calculating the square of the distance between two points
 * No need to involve square roots or floats in this program since we only need to compare distances
 * and squaring preserve order
 */

class Vertex {
public:
    Vertex(int aX, int aY);
    ~Vertex();
public:
    int SquaredDistanceFrom(const Vertex& aOrigin) const;
    int GetX() const;
    int GetY() const;
private:
    int iX;
    int iY;
};