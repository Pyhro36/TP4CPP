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
    Point(int xCoordinate, int yCoordinate);

    Point operator+(Point otherPoint);
    Point operator+=(Point otherPoint);
    Point operator-(Point otherPoint);
    Point operator-=(Point otherPoint);

    int getX() const;
    int getY() const;
};

#endif
