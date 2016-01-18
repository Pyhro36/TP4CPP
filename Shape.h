#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "Point.h"

/// class Shape -
class Shape {
    // Attributes
protected:
    std::string name;
    // Operations
public:
    Shape(const std::string & shapeName);

    virtual bool contain(const Point & point) const = 0;
    virtual void move(const Point & vector) = 0;
    virtual std::string describe() const = 0;
    std::string getName() const;
    virtual void appendToName(const std::string & newNameEnding);
    virtual Shape* clone() const = 0;
};

#endif