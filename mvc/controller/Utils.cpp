
#include "Utils.h"

int Utils::randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

float Utils::distance(float x1, float y1, float x2, float y2) {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

float Utils::my_qDegreesToRadians(float degrees)
{
    return degrees * float(M_PI/180);
}


std::vector<PolarPoint> Utils::cartesianToPolar(std::vector<sf::Vector2f> pntCartesians)
{
    // Helper lambda to calculate the hypotenuse of a point
    auto hypotenuseOfPoint = [](const sf::Vector2f& pnt) -> double {
        return std::sqrt((pnt.x * pnt.x) + (pnt.y * pnt.y));
    };

    // Find the largest hypotenuse
    const double LARGEST_HYP = std::max_element(pntCartesians.begin(), pntCartesians.end(),
                                                [&, hypotenuseOfPoint](const sf::Vector2f& left, const sf::Vector2f& right) {
                                                    return hypotenuseOfPoint(left) < hypotenuseOfPoint(right);
                                                })->x + std::max_element(pntCartesians.begin(), pntCartesians.end(),
                                                  [&, hypotenuseOfPoint](const sf::Vector2f& left, const sf::Vector2f& right) {
                                                      return hypotenuseOfPoint(left) < hypotenuseOfPoint(right);
                                                  })->y;

    // Lambda to convert Cartesian points to Polar
    auto cartToPolarTransform = [&hypotenuseOfPoint, &LARGEST_HYP](const sf::Vector2f& pnt) -> PolarPoint {
        double r = hypotenuseOfPoint(pnt) / LARGEST_HYP;
        double theta = std::atan2(pnt.y, pnt.x);
        return {r, theta};
    };

    // Transform each Cartesian point to a Polar point
    std::vector<PolarPoint> polarPoints;
    for (const auto& point : pntCartesians) {
        polarPoints.push_back(cartToPolarTransform(point));
    }

    return polarPoints;
}
