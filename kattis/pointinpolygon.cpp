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

struct Polygon {
    vector<Point> p;
    int n;

    Polygon(vector<Point> _p) : p(_p), n(_p.size()) {}

    // 1. Perimeter
    ld perimeter() const {
        ld res = 0;
        for (int i = 0; i < n; i++) res += dist(p[i], p[(i + 1) % n]);
        return res;
    }

    // 2. Area using Shoelace Formula
    // Formula: 0.5 * |sum(x_i * y_{i+1} - x_{i+1} * y_i)|
    ld area() const {
        ld res = 0;
        for (int i = 0; i < n; i++) res += cross(p[i], p[(i + 1) % n]);
        return std::abs(res) / 2.0;
    }

    // 3. Convexity Check
    // A polygon is convex if all consecutive cross products have the same sign
    bool is_convex() const {
        bool has_pos = false, has_neg = false;
        for (int i = 0; i < n; i++) {
            ld o = cross(p[(i + 1) % n] - p[i], p[(i + 2) % n] - p[(i + 1) % n]);
            if (o > EPS) has_pos = true;
            if (o < -EPS) has_neg = true;
        }
        return !(has_pos && has_neg);
    }

    // 4. Point in Polygon (PIP) - Ray Casting Algorithm
    // Returns: 1 (Inside), 0 (On Edge), -1 (Outside)
    
    int contains(Point pt) const {
        bool inside = false;
        for (int i = 0; i < n; i++) {
            Point a = p[i], b = p[(i + 1) % n];
            
            // Check if point is on the edge
            if (std::abs(cross(a - pt, b - pt)) < EPS && dot(a - pt, b - pt) < EPS) return 0;
            
            // Ray casting logic
            if (a.y > b.y) swap(a, b);
            if (pt.y > a.y && pt.y <= b.y && cross(b - a, pt - a) > EPS) inside = !inside;
        }
        return inside ? 1 : -1;
    }

    // Returns true if the polygon is convex
    // Works for both CW and CCW vertex ordering
    bool is_convex_alternative(const vector<Point>& p) {
        int n = p.size();
        if (n < 3) return true;
        int first_turn = 0;
        for (int i = 0; i < n; i++) {
            // Points: previous, current, next
            int res = ccw(p[i], p[(i + 1) % n], p[(i + 2) % n]);
            if (res == 0) continue; // Collinear points don't affect convexity
            if (first_turn == 0) first_turn = res;
            else if (res != first_turn) return false;
        }
        return true;
    }

    // Returns the angle AOB
    ld angle(Point a, Point o, Point b) {
        Point oa = a - o, ob = b - o;
        return atan2(cross(oa, ob), dot(oa, ob));
    }
    
    int is_inside_winding(const vector<Point>& p, Point pt) {
        ld total_angle = 0;
        int n = p.size();
        for (int i = 0; i < n; i++) {
            Point a = p[i], b = p[(i + 1) % n];
            // Check if point is on the edge first
            if (abs(cross(a - pt, b - pt)) < EPS && dot(a - pt, b - pt) < EPS) return 0;
            total_angle += angle(a, pt, b);
        }
        // If the sum is roughly 2*PI or -2*PI, it's inside
        return (abs(total_angle) > M_PI) ? 1 : -1;
    }
};

void solve(int n){
    vector<Point> p;
    for(int i=0;i<n;i++){
        ld x,y;
        cin>>x>>y;
        p.push_back(Point(x,y));
    }
    p.push_back(p[0]);
    Polygon poly(p);
    int m;
    cin>>m;
    for(int i=0;i<m;i++){
        ld x,y;
        cin>>x>>y;
        int inside=poly.contains(Point(x,y));
        if(inside==0)cout<<"on\n";
        if(inside==1)cout<<"in\n";
        if(inside==-1)cout<<"out\n";
    }
    return;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    while(n){
        solve(n);
        cin>>n;
    }
    return 0;
}
