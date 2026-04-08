#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const ld EPS = 1e-9;

struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {}

    // Basic Vector Operators
    Point operator+(const Point& other) const { return Point(x + other.x, y + other.y); }
    Point operator-(const Point& other) const { return Point(x - other.x, y - other.y); }
    Point operator*(ld scalar) const { return Point(x * scalar, y * scalar); }
    Point operator/(ld scalar) const { return Point(x / scalar, y / scalar); }

    // Magnitude and Distance
    ld norm() const { return x * x + y * y; }
    ld abs() const { return sqrt(norm()); }
};

// --- Fundamental Vector Operations ---

ld dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
ld cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
ld dist(Point a, Point b) { return (a - b).abs(); }

/**
 * Orientation (CCW Test)
 * Returns: 1 if a->b->c is counter-clockwise, -1 if clockwise, 0 if collinear
 */
int ccw(Point a, Point b, Point c) {
    ld res = cross(b - a, c - a);
    if (res > EPS) return 1;
    if (res < -EPS) return -1;
    return 0;
}

// --- Line Structure ---

struct Line {
    Point p1, p2;
    Point v; // Direction vector

    Line(Point p1, Point p2) : p1(p1), p2(p2) {
        v = p2 - p1;
    }

    // Projection of point p onto the infinite line
    
    Point project(Point p) {
        ld t = dot(p - p1, v) / v.norm();
        return p1 + v * t;
    }

    // Reflection of point p over the infinite line
    Point reflect(Point p) {
        Point proj = project(p);
        return proj * 2.0 - p;
    }

    // Distance from point p to the infinite line
    ld dist_to_line(Point p) {
        return std::abs(cross(v, p - p1)) / v.abs();
    }

    // Distance from point p to the line segment [p1, p2]
    
    ld dist_to_segment(Point p) {
        if (dot(v, p - p1) < 0) return dist(p, p1);
        if (dot(p1 - p2, p - p2) < 0) return dist(p, p2);
        return dist_to_line(p);
    }
};

// Intersection of two infinite lines
// Returns {true, point} if they intersect, {false, 0} if parallel
pair<bool, Point> intersect(Line l1, Line l2) {
    ld d = cross(l1.v, l2.v);
    if (std::abs(d) < EPS) return {false, Point()};
    ld t = cross(l2.p1 - l1.p1, l2.v) / d;
    return {true, l1.p1 + l1.v * t};
}

// Intersection of two line segments
// Returns {true, point} if they intersect, {false, 0} if they do not
pair<bool, Point> intersect_segments(Line l1, Line l2) {
    ld d = cross(l1.v, l2.v);
    // If d is 0, segments are parallel or collinear
    if (std::abs(d) < EPS) return {false, Point()};
    // t is the parameter for l1, u is the parameter for l2
    // l1.p1 + t*l1.v = l2.p1 + u*l2.v
    ld t = cross(l2.p1 - l1.p1, l2.v) / d;
    ld u = cross(l2.p1 - l1.p1, l1.v) / d;
    // Strict intersection: the point must lie strictly inside both segments.
    // This ensures positive area and handles cases where points just touch.
    if (t > EPS && t < 1.0 - EPS && u > EPS && u < 1.0 - EPS) {
        return {true, l1.p1 + l1.v * t};
    }
    return {false, Point()};
}
