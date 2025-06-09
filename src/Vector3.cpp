#include "Vector3.h"

// Constructor
Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) {}

// Getters
double Vector3::getX() const { return x; }
double Vector3::getY() const { return y; }
double Vector3::getZ() const { return z; }

// Setters
void Vector3::setX(double x) { this->x = x; }
void Vector3::setY(double y) { this->y = y; }
void Vector3::setZ(double z) { this->z = z; }

// Vector addition
Vector3 Vector3::operator+(const Vector3 &other) const
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

// Vector subtraction
Vector3 Vector3::operator-(const Vector3 &other) const
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

// Scalar multiplication
Vector3 Vector3::operator*(double scalar) const
{
    return Vector3(x * scalar, y * scalar, z * scalar);
}

// Scalar division
Vector3 Vector3::operator/(double scalar) const
{
    if (scalar == 0.0)
    {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    return Vector3(x / scalar, y / scalar, z / scalar);
}

// Dot product
double Vector3::dot(const Vector3 &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

// Cross product
Vector3 Vector3::cross(const Vector3 &other) const
{
    return Vector3(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x);
}

// Magnitude (length) of the vector
double Vector3::magnitude() const
{
    return std::sqrt(x * x + y * y + z * z);
}

// Normalize the vector
Vector3 Vector3::normalize() const
{
    double mag = magnitude();
    if (mag == 0.0)
    {
        throw std::invalid_argument("Cannot normalize a zero vector.");
    }
    return Vector3(x / mag, y / mag, z / mag);
}
