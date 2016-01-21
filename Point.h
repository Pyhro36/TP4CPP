#ifndef POINT_H
#define POINT_H

/// class point -
class Point {
    // Attributes
private:
    int x;
    int y;
    // Operations

public:
    Point(const int xCoordinate, const int yCoordinate);

    Point(const Point& point);

    Point operator+(const Point &  otherPoint) const;
    Point & operator+=(const Point &  otherPoint);
    Point operator-(const Point &  otherPoint) const;
    Point & operator-=(const Point &  otherPoint);

    int getX() const;
    int getY() const;
};

#endif
