#include <Vector3.h>
#include <string>

class Particle
{
private:
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
    Vector3 color;
    double mass;
    double radius;
    double charge;
    std::string name;

public:
    // Constructor
    Particle(const Vector3 &position, const Vector3 &velocity, const Vector3 &acceleration,
             const Vector3 &color, double mass, double radius, double charge, const std::string &name);

    // Getters
    Vector3 getPosition() const;
    Vector3 getVelocity() const;
    Vector3 getAcceleration() const;
    Vector3 getColor() const;
    double getMass() const;
    double getRadius() const;
    double getCharge() const;
    std::string getName() const;

    // Setters
    void setPosition(const Vector3 &pos);
    void setVelocity(const Vector3 &vel);
    void setAcceleration(const Vector3 &acc);
    void setColor(const Vector3 &col);
    void setMass(double m);
    void setRadius(double r);
    void setCharge(double c);
    void setName(const std::string &n);

    // Update particle state
    void update(double deltaTime);
};