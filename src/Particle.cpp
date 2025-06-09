#include "Particle.h"

// Constructor
Particle::Particle(const Vector3 &position, const Vector3 &velocity, const Vector3 &acceleration,
                   const Vector3 &color, double mass, double radius, double charge, const std::string &name)
    : position(position), velocity(velocity), acceleration(acceleration),
      color(color), mass(mass), radius(radius), charge(charge), name(name) {}

// Getters
Vector3 Particle::getPosition() const { return position; }
Vector3 Particle::getVelocity() const { return velocity; }
Vector3 Particle::getAcceleration() const { return acceleration; }
Vector3 Particle::getColor() const { return color; }
double Particle::getMass() const { return mass; }
double Particle::getRadius() const { return radius; }
double Particle::getCharge() const { return charge; }
std::string Particle::getName() const { return name; }

// Setters
void Particle::setPosition(const Vector3 &pos) { position = pos; }
void Particle::setVelocity(const Vector3 &vel) { velocity = vel; }
void Particle::setAcceleration(const Vector3 &acc) { acceleration = acc; }
void Particle::setColor(const Vector3 &col) { color = col; }
void Particle::setMass(double m) { mass = m; }
void Particle::setRadius(double r) { radius = r; }
void Particle::setCharge(double c) { charge = c; }
void Particle::setName(const std::string &n) { name = n; }

// Update particle state
void Particle::update(double deltaTime)
{
    position = position + velocity * deltaTime;
    velocity = velocity + acceleration * deltaTime;
}
