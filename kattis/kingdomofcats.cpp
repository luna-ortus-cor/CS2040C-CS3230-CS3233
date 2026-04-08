#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const ld EPS = 1e-12;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}

    // Basic Vector Operators
    Point operator+(const Point& other) const { return Point(x + other.x, y + other.y); }
    Point operator-(const Point& other) const { return Point(x - other.x, y - other.y); }
    Point operator*(ll scalar) const { return Point(x * scalar, y * scalar); }
    
    // Convert to ld for precision tasks
    ld abs() const { return sqrt((ld)x * x + (ld)y * y); }
    ll norm() const { return x * x + y * y; }
};

// --- Fundamental Vector Operations ---

ll dot(Point a, Point b) { return a.x * b.x + a.y * b.y; }
ll cross(Point a, Point b) { return a.x * b.y - a.y * b.x; }
ld dist(Point a, Point b) { return (a - b).abs(); }

/**
 * Orientation (CCW Test)
 * Returns: 1 if a->b->c is counter-clockwise, -1 if clockwise, 0 if collinear
 */
int ccw(Point a, Point b, Point c) {
    ll res = cross(b - a, c - a);
    if (res > 0) return 1;
    if (res < 0) return -1;
    return 0;
}

// --- Line Structure ---

struct Line {
    Point p1, p2;
    Point v; // Direction vector

    Line(Point p1, Point p2) : p1(p1), p2(p2) {
        v = p2 - p1;
    }

    // Projection of point p onto the infinite line (Requires ld)
    pair<ld, ld> project(Point p) {
        ld t = (ld)dot(p - p1, v) / v.norm();
        return {(ld)p1.x + (ld)v.x * t, (ld)p1.y + (ld)v.y * t};
    }

    // Reflection of point p over the infinite line (Requires ld)
    pair<ld, ld> reflect(Point p) {
        pair<ld, ld> proj = project(p);
        return {proj.first * 2.0 - p.x, proj.second * 2.0 - p.y};
    }

    // Distance from point p to the infinite line
    ld dist_to_line(Point p) {
        return std::abs((ld)cross(v, p - p1)) / v.abs();
    }

    // Distance from point p to the line segment [p1, p2]
    ld dist_to_segment(Point p) {
        if (dot(v, p - p1) < 0) return dist(p, p1);
        if (dot(p1 - p2, p - p2) < 0) return dist(p, p2);
        return dist_to_line(p);
    }
};

// Intersection of two infinite lines
// Returns {true, Point} using long double for coordinate precision
pair<bool, pair<ld, ld>> intersect(Line l1, Line l2) {
    ll d = cross(l1.v, l2.v);
    if (d == 0) return {false, {0, 0}};
    ld t = (ld)cross(l2.p1 - l1.p1, l2.v) / d;
    return {true, {(ld)l1.p1.x + (ld)l1.v.x * t, (ld)l1.p1.y + (ld)l1.v.y * t}};
}

// Intersection of two line segments
// Need to fix the point returned
pair<bool, Point> intersect_segments(Line l1, Line l2) {
    int cp1 = ccw(l1.p1, l1.p2, l2.p1);
    int cp2 = ccw(l1.p1, l1.p2, l2.p2);
    int cp3 = ccw(l2.p1, l2.p2, l1.p1);
    int cp4 = ccw(l2.p1, l2.p2, l1.p2);

    // Strict intersection check
    if (((cp1 > 0 && cp2 < 0) || (cp1 < 0 && cp2 > 0)) &&
        ((cp3 > 0 && cp4 < 0) || (cp3 < 0 && cp4 > 0))) {
        return {true, Point(0,0)};
    }
    return {false, Point(0,0)};
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin>>n;
    while(n){
        int ans=0;
        vector<Point> points;
        for(int i=0;i<n;i++){
            ll x,y;
            cin>>x>>y;
            points.push_back(Point(x,y));
        }
        vector<Line> diagonals;
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                diagonals.push_back(Line(points[i],points[j]));
            }
        }
        for(int i=0;i<diagonals.size();i++){
            for(int j=i+1;j<diagonals.size();j++){
                if(intersect_segments(diagonals[i],diagonals[j]).first)ans++;
            }
        }
        cout<<ans<<"\n";
        cin>>n;
    }
    return 0;
}
