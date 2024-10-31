#ifndef POLARPOINT_H
#define POLARPOINT_H

class PolarPoint {
private:
    double r;      // corresponds to the hypotenuse in Cartesian, value between 0 and 1
    double theta;  // degrees in radians, value between 0 and 6.283 (2 * PI)

public:
    // Constructor
    PolarPoint(double radius, double angle) : r(radius), theta(angle) {}

    // Getters and Setters
    double getR() const { return r; }
    void setR(double radius) { r = radius; }

    double getTheta() const { return theta; }
    void setTheta(double angle) { theta = angle; }

    // Overloaded comparison operator for sorting (similar to Java's Comparable interface)
    bool operator<(const PolarPoint& other) const {
        return theta < other.theta;
    }
};

#endif
