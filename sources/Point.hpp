#ifndef POINT_HPP
#define POINT_HPP

namespace ariel {
    class Point {
    private:
        double x;
        double y;
    public:
        Point(double x, double y);
        double getX() const;
        double getY() const;
        double distance(const Point& other) const;
        Point moveTowards(const Point& src, const Point& dest, double dist) const;
    };
}

#endif // POINT_HPP
