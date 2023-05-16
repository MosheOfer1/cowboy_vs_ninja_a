#ifndef POINT_HPP
#define POINT_HPP
#include <iostream>
namespace ariel
{
    class Point
    {
    private:
        double x;
        double y;

    public:
        Point() : x(0), y(0) {}
        Point(double x, double y);
        double getX() const;
        double getY() const;
        void print() const
        {
            std::cout << "(" << x << ", " << y << ")" << std::endl;
        }

        double distance(const Point &other) const;
        static Point moveTowards(const Point &src, const Point &dest, double dist);

        friend std::ostream& operator<<(std::ostream& os, const Point& point);
    };
}

#endif // POINT_HPP
