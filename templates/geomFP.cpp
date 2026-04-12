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

vector<Point> convex_hull(vector<Point> pts) {
    int n = pts.size(), k = 0;
    if (n <= 2) return pts;
    vector<Point> res(2 * n);
    sort(pts.begin(), pts.end(), [](Point a, Point b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    // Build lower hull
    for (int i = 0; i < n; i++) {
        while (k >= 2 && cross(res[k - 1] - res[k - 2], pts[i] - res[k - 1]) <= 0) k--;
        res[k++] = pts[i];
    }
    // Build upper hull
    for (int i = n - 2, t = k + 1; i >= 0; i--) {
        while (k >= t && cross(res[k - 1] - res[k - 2], pts[i] - res[k - 1]) <= 0) k--;
        res[k++] = pts[i];
    }
    res.resize(k - 1);
    return res;
}

ld polygon_diameter(const vector<Point>& hull) {
    int n = hull.size();
    if (n == 1) return 0;
    if (n == 2) return dist(hull[0], hull[1]);
    
    ld max_d = 0;
    int k = 1;
    // Find initial point k furthest from edge 0-(n-1)
    while (abs(cross(hull[n-1] - hull[0], hull[(k+1)%n] - hull[0])) > 
           abs(cross(hull[n-1] - hull[0], hull[k] - hull[0]))) {
        k = (k + 1) % n;
    }

    int j = k;
    for (int i = 0; i <= k; i++) {
        while (abs(cross(hull[i+1] - hull[i], hull[(j+1)%n] - hull[i])) > 
               abs(cross(hull[i+1] - hull[i], hull[j] - hull[i]))) {
            j = (j + 1) % n;
            max_d = max(max_d, dist(hull[i], hull[j]));
        }
        max_d = max(max_d, dist(hull[i], hull[j]));
    }
    return max_d;
}

// Helper: find intersection of line (a,b) and line (p1,p2)
Point line_intersect(Point a, Point b, Point p1, Point p2) {
    ld c1 = cross(b - a, p1 - a);
    ld c2 = cross(b - a, p2 - a);
    return p1 + (p2 - p1) * (c1 / (c1 - c2));
}

vector<Point> cut_polygon(const vector<Point>& p, Point a, Point b) {
    vector<Point> res;
    int n = p.size();
    for (int i = 0; i < n; i++) {
        Point cur = p[i], next = p[(i + 1) % n];
        int c1 = ccw(a, b, cur);
        int c2 = ccw(a, b, next);
        
        // If current point is to the left, keep it
        if (c1 != -1) res.push_back(cur);
        // If the edge crosses the line, add the intersection point
        if (c1 * c2 == -1) {
            res.push_back(line_intersect(a, b, cur, next));
        }
    }
    return res;
}

// Pre-condition: polygons must be CCW and the first point must be the one with min y (then min x)
vector<Point> minkowski_sum(vector<Point> P1, vector<Point> P2) {
    // Helper to rotate to min-y
    auto rotate_to_min = [](vector<Point>& P) {
        int pos = 0;
        for (int i = 1; i < P.size(); i++)
            if (P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x)) pos = i;
        rotate(P.begin(), P.begin() + pos, P.end());
    };
    rotate_to_min(P1); rotate_to_min(P2);

    int n = P1.size(), m = P2.size();
    int i = 0, j = 0;
    vector<Point> res;
    while (i < n || j < m) {
        res.push_back(P1[i % n] + P2[j % m]);
        ld c = cross(P1[(i + 1) % n] - P1[i % n], P2[(j + 1) % m] - P2[j % m]);
        if (c >= 0 && i < n) i++;
        if (c <= 0 && j < m) j++;
    }
    return res;
}

void polar_sort(vector<Point>& pts, Point center) {
    sort(pts.begin(), pts.end(), [&](Point a, Point b) {
        Point va = a - center, vb = b - center;
        // Check which half-plane (upper vs lower)
        auto half = [](Point p) { return p.y > 0 || (p.y == 0 && p.x > 0); };
        if (half(va) != half(vb)) return half(va);
        return cross(va, vb) > 0; // Standard CCW check
    });
}

ld closest_pair(vector<Point>& pts, int l, int r) {
    if (l >= r) return 1e18;
    int mid = (l + r) / 2;
    ld mid_x = pts[mid].x;
    ld d = min(closest_pair(pts, l, mid), closest_pair(pts, mid + 1, r));
    inplace_merge(pts.begin() + l, pts.begin() + mid + 1, pts.begin() + r + 1, 
                  [](Point a, Point b) { return a.y < b.y; });

    vector<Point> strip;
    for (int i = l; i <= r; i++) {
        if (abs(pts[i].x - mid_x) < d) {
            for (int j = (int)strip.size() - 1; j >= 0 && pts[i].y - strip[j].y < d; j--) {
                d = min(d, dist(pts[i], strip[j]));
            }
            strip.push_back(pts[i]);
        }
    }
    return d;
}

vector<Point> visvalingam_whyatt(const vector<Point>& pts, int target_count) {
    int n = pts.size();
    if (n <= target_count) return pts;

    vector<PolyNode> nodes(n);
    auto get_area = [&](int i) {
        if (nodes[i].prev == -1 || nodes[i].next == -1) return 2e18; // Keep ends
        return (double)abs(cross(nodes[nodes[i].prev].p - nodes[i].p, 
                                 nodes[nodes[i].next].p - nodes[i].p)) * 0.5;
    };

    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<>> pq;
    for (int i = 0; i < n; i++) {
        nodes[i] = {pts[i], i - 1, (i == n - 1 ? -1 : i + 1), 0.0};
    }
    for (int i = 1; i < n - 1; i++) {
        nodes[i].area = get_area(i);
        pq.push({nodes[i].area, i});
    }

    vector<bool> removed(n, false);
    int current_count = n;
    while (current_count > target_count && !pq.empty()) {
        auto [a, i] = pq.top(); pq.pop();
        if (removed[i] || abs(a - nodes[i].area) > EPS) continue;

        removed[i] = true;
        current_count--;

        int pr = nodes[i].prev, nx = nodes[i].next;
        if (pr != -1) nodes[pr].next = nx;
        if (nx != -1) nodes[nx].prev = pr;

        if (pr != -1 && nodes[pr].prev != -1) {
            nodes[pr].area = get_area(pr);
            pq.push({nodes[pr].area, pr});
        }
        if (nx != -1 && nodes[nx].next != -1) {
            nodes[nx].area = get_area(nx);
            pq.push({nodes[nx].area, nx});
        }
    }

    vector<Point> result;
    for (int i = 0; i < n; i++) if (!removed[i]) result.push_back(pts[i]);
    return result;
}

struct Segment {
    Point a, b;
    int id;
    ld get_y(ld x) const {
        if (abs(a.x - b.x) < EPS) return a.y;
        return a.y + (b.y - a.y) * (x - a.x) / (b.x - a.x);
    }
};

ld sweep_x; 
struct SegmentComp {
    bool operator()(const Segment& s1, const Segment& s2) const {
        if (s1.id == s2.id) return false;
        ld y1 = s1.get_y(sweep_x), y2 = s2.get_y(sweep_x);
        if (abs(y1 - y2) > EPS) return y1 < y2;
        return s1.id < s2.id;
    }
};

struct Event {
    ld x; int type, id; // type: 0 = left, 1 = right
    bool operator>(const Event& other) const { return x > other.x; }
};

vector<Point> find_all_intersections(vector<Segment>& segs) {
    priority_queue<Event, vector<Event>, greater<>> pq;
    for (auto& s : segs) {
        if (s.a.x > s.b.x) swap(s.a, s.b);
        pq.push({s.a.x, 0, s.id});
        pq.push({s.b.x, 1, s.id});
    }

    set<Segment, SegmentComp> active;
    vector<Point> intersections;

    auto check = [&](int id1, int id2) {
        auto res = intersect(Line(segs[id1].a, segs[id1].b), Line(segs[id2].a, segs[id2].b));
        if (res.first) {
            // Validate point is actually on both segments
            Point p = res.second;
            if (p.x >= max(segs[id1].a.x, segs[id2].a.x) - EPS && 
                p.x <= min(segs[id1].b.x, segs[id2].b.x) + EPS)
                intersections.push_back(p);
        }
    };

    while (!pq.empty()) {
        Event e = pq.top(); pq.pop();
        sweep_x = e.x;
        if (e.type == 0) { // Left endpoint
            auto it = active.insert(segs[e.id]).first;
            auto nxt = next(it), prv = (it == active.begin() ? active.end() : prev(it));
            if (nxt != active.end()) check(e.id, nxt->id);
            if (prv != active.end()) check(e.id, prv->id);
        } else { // Right endpoint
            auto it = active.find(segs[e.id]);
            if (it != active.end()) {
                auto nxt = next(it), prv = (it == active.begin() ? active.end() : prev(it));
                if (nxt != active.end() && prv != active.end()) check(nxt->id, prv->id);
                active.erase(it);
            }
        }
    }
    return intersections;
}

struct Triangle {
    int p[3];
    Point circum_center;
    ld circum_radius_sq;

    Triangle(int i, int j, int k, const vector<Point>& pts) {
        p[0] = i; p[1] = j; p[2] = k;
        // Circumcenter formula for a triangle
        ld D = 2 * (pts[i].x * (pts[j].y - pts[k].y) + pts[j].x * (pts[k].y - pts[i].y) + pts[k].x * (pts[i].y - pts[j].y));
        circum_center.x = ((pts[i].norm()) * (pts[j].y - pts[k].y) + (pts[j].norm()) * (pts[k].y - pts[i].y) + (pts[k].norm()) * (pts[i].y - pts[j].y)) / D;
        circum_center.y = ((pts[i].norm()) * (pts[k].x - pts[j].x) + (pts[j].norm()) * (pts[i].x - pts[k].x) + (pts[k].norm()) * (pts[j].x - pts[i].x)) / D;
        circum_radius_sq = dist(pts[i], circum_center);
        circum_radius_sq *= circum_radius_sq;
    }
};

vector<Triangle> delaunay(vector<Point> pts) {
    // 1. Create a "Super-Triangle" that contains all points
    pts.push_back({-10000, -10000});
    pts.push_back({10000, -10000});
    pts.push_back({0, 10000});
    
    vector<Triangle> triangulation;
    triangulation.push_back(Triangle(pts.size()-3, pts.size()-2, pts.size()-1, pts));

    for (int i = 0; i < (int)pts.size() - 3; i++) {
        vector<pair<int, int>> polygon;
        vector<int> bad_triangles;

        for (int j = 0; j < triangulation.size(); j++) {
            if (dist(pts[i], triangulation[j].circum_center) * dist(pts[i], triangulation[j].circum_center) < triangulation[j].circum_radius_sq + EPS) {
                bad_triangles.push_back(j);
                for (int e = 0; e < 3; e++) {
                    int u = triangulation[j].p[e], v = triangulation[j].p[(e + 1) % 3];
                    polygon.push_back({u, v});
                }
            }
        }

        // Keep only edges that are not shared by another bad triangle
        vector<pair<int, int>> unique_edges;
        for (int e = 0; e < polygon.size(); e++) {
            bool shared = false;
            for (int f = 0; f < polygon.size(); f++) {
                if (e != f && ((polygon[e].first == polygon[f].second && polygon[e].second == polygon[f].first))) {
                    shared = true; break;
                }
            }
            if (!shared) unique_edges.push_back(polygon[e]);
        }

        // Remove bad triangles (backwards to maintain indices)
        sort(bad_triangles.rbegin(), bad_triangles.rend());
        for (int idx : bad_triangles) triangulation.erase(triangulation.begin() + idx);

        for (auto& edge : unique_edges) triangulation.push_back(Triangle(edge.first, edge.second, i, pts));
    }
    // Final step: remove triangles connected to the super-triangle...
    return triangulation;
}

struct VoronoiDiagram {
    struct VEdge { Point from, to; };
    vector<Point> vertices; // Voronoi vertices (circumcenters)
    vector<VEdge> edges;    // Voronoi edges

    void build(const vector<Point>& pts, const vector<Triangle>& del_triangles) {
        // 1. Map each Delaunay edge to the triangle(s) it belongs to
        // edge (u, v) -> list of triangle indices
        map<pair<int, int>, vector<int>> edge_to_tri;
        
        for (int i = 0; i < del_triangles.size(); i++) {
            vertices.push_back(del_triangles[i].circum_center);
            for (int j = 0; j < 3; j++) {
                int u = del_triangles[i].p[j];
                int v = del_triangles[i].p[(j + 1) % 3];
                if (u > v) swap(u, v);
                edge_to_tri[{u, v}].push_back(i);
            }
        }

        // 2. Connect circumcenters of triangles that share an edge
        for (auto const& [edge, tri_list] : edge_to_tri) {
            if (tri_list.size() == 2) {
                edges.push_back({vertices[tri_list[0]], vertices[tri_list[1]]});
            }
            // Note: If size == 1, it's a boundary edge. 
            // The Voronoi edge would be a ray extending to infinity.
        }
    }
};

struct TriangleMetrics {
    Point A, B, C;
    ld a, b, c, s, area;

    TriangleMetrics(Point p1, Point p2, Point p3) : A(p1), B(p2), C(p3) {
        a = dist(B, C);
        b = dist(A, C);
        c = dist(A, B);
        s = (a + b + c) / 2.0;
        area = abs(cross(B - A, C - A)) / 2.0;
    }

    ld circumradius() { return (a * b * c) / (4.0 * area); }

    Point circumcenter() {
        ld D = 2 * (A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y));
        ld ux = ((A.norm()) * (B.y - C.y) + (B.norm()) * (C.y - A.y) + (C.norm()) * (A.y - B.y)) / D;
        ld uy = ((A.norm()) * (C.x - B.x) + (B.norm()) * (A.x - C.x) + (C.norm()) * (B.x - A.x)) / D;
        return Point(ux, uy);
    }

    ld inradius() { return area / s; }

    Point incenter() {
        return (A * a + B * b + C * c) / (a + b + c);
    }
};
