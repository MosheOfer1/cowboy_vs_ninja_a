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
    Point Point::moveTowards(const Point &src, const Point &dest, double dist) const
    {
        double d = src.distance(dest);
        if (d == 0)
        {
            return src;
        }
        double ratio = dist / d;
        double newX = src.getX() + (dest.getX() - src.getX()) * ratio;
        double newY = src.getY() + (dest.getY() - src.getY()) * ratio;
        return Point(newX, newY);
    }
}
