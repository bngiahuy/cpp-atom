#include <stdexcept>
#include <cmath>

class Vector3
{
private:
    double x, y, z;

public:
    // Constructor
    Vector3(double x = 0.0, double y = 0.0, double z = 0.0);

    // Getters
    double getX() const;
    double getY() const;
    double getZ() const;

    // Setters
    void setX(double x);
    void setY(double y);
    void setZ(double z);

    // Vector addition
    Vector3 operator+(const Vector3 &other) const;

    // Vector subtraction
    Vector3 operator-(const Vector3 &other) const;

    // Scalar multiplication
    Vector3 operator*(double scalar) const;

    // Scalar division
    Vector3 operator/(double scalar) const;

    // Dot product
    double dot(const Vector3 &other) const;

    // Cross product
    Vector3 cross(const Vector3 &other) const;

    // Magnitude (length) of the vector
    double magnitude() const;

    // Normalize the vector
    Vector3 normalize() const;
};