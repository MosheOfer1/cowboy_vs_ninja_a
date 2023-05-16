#include "Point.hpp"
#include <cmath>

namespace ariel
{
    Point::Point(double x, double y) : x(x), y(y) {}
    double Point::getX() const { return x; }
    double Point::getY() const { return y; }
    double Point::distance(const Point &other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
    Point Point::moveTowards(const Point &src, const Point &dest, double dist)
    {
        if (dist < 0)
        {
            throw std::invalid_argument("Distance cannot be negative!");
        }
        double totalDist = src.distance(dest);
        if (totalDist <= dist)
        {
            return dest;
        }

        double ratio = dist / totalDist;
        double newX = src.x + ratio * (dest.x - src.x);
        double newY = src.y + ratio * (dest.y - src.y);

        return Point(newX, newY);
    }
    std::ostream &operator<<(std::ostream &os, const Point &point)
    {
        os << "(" << point.x << "," << point.y << ")";
        return os;
    }
}
