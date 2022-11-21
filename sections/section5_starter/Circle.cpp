#include "Circle.h"
using namespace std;
#include "SimpleTest.h"
#include "gmath.h"
#include "strlib.h"

/**
 * TODO: write a method comment
 */
Circle::Circle(double r) {
    radius = r;
}


/**
 * TODO: write a method comment
 */
double Circle::area() const {
    return radius * radius * PI;
}

/**
 * TODO: write a method comment
 */
double Circle::circumference() const{
    return 2 * radius * PI;
}

/**
 * TODO: write a method comment
 */
double Circle::getRadius() const{
    return radius;
}

/**
 * TODO: write a method comment
 */
string Circle::toString() const{
    return string("Circle{radius=") + realToString(radius) + "}";
}

/* Provided Tests Below This Line */

PROVIDED_TEST("Simple Example") {
    Circle c(2.5);
    EXPECT_EQUAL(c.getRadius(), 2.5);
    EXPECT_EQUAL(c.circumference(), 2 * PI * 2.5);
    EXPECT_EQUAL(c.area(), PI * 2.5 * 2.5);
    EXPECT_EQUAL(c.toString(), "Circle{radius=2.5}");
}
