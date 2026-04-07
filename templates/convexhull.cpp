#include <bits/stdc++.h>
using namespace std;

struct point {
    double x, y;
    point() {}
    point(double _x, double _y) : x(_x), y(_y) {}
    bool operator==(const point &p) const { return x == p.x && y == p.y; }
    bool operator<(const point &p) const { return x < p.x || (x == p.x && y < p.y); }
};

// Cross product (AB x AC)
double cross(point A, point B, point C) {
    return (B.x - A.x)*(C.y - A.y) - (B.y - A.y)*(C.x - A.x);
}

// CCW test: true if counter-clockwise turn
bool ccw(point A, point B, point C) {
    return cross(A, B, C) > 0;
}

// -------- Graham's Scan --------
vector<point> CH_Graham(vector<point> &Pts) {
    vector<point> P(Pts);
    int n = (int)P.size();
    if (n <= 3) {
        if (!(P[0] == P[n-1])) P.push_back(P[0]); // close polygon
        return P;
    }

    // Find P0 = lowest Y (tie: rightmost X)
    int P0 = min_element(P.begin(), P.end(), [](point a, point b){
        return a.y < b.y || (a.y == b.y && a.x > b.x);
    }) - P.begin();
    swap(P[0], P[P0]);

    // Sort points by angle around P0
    sort(P.begin()+1, P.end(), [&](point a, point b) {
        double c = cross(P[0], a, b);
        if (c == 0) return hypot(a.x-P[0].x, a.y-P[0].y) < hypot(b.x-P[0].x, b.y-P[0].y);
        return c > 0;
    });

    vector<point> S({P[n-1], P[0], P[1]});
    int i = 2;
    while (i < n) {
        int j = (int)S.size() - 1;
        if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);
        else S.pop_back();
    }
    return S;
}

// -------- Andrew's Monotone Chain --------
vector<point> CH_Andrew(vector<point> &Pts) {
    int n = (int)Pts.size(), k = 0;
    vector<point> H(2*n);
    sort(Pts.begin(), Pts.end());
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && !ccw(H[k-2], H[k-1], Pts[i])) --k;
        H[k++] = Pts[i];
    }
    for (int i = n-2, t = k+1; i >= 0; --i) {
        while (k >= t && !ccw(H[k-2], H[k-1], Pts[i])) --k;
        H[k++] = Pts[i];
    }
    H.resize(k);
    return H;
}

// -------- Utility to print points --------
void printPolygon(const vector<point> &poly) {
    for (auto &p : poly) cout << "(" << p.x << "," << p.y << ") ";
    cout << endl;
}

// -------- Main Test --------
int main() {
    vector<vector<point>> testCases = {
        { {0,0} },
        { {0,0}, {1,0} },
        { {0,0}, {1,0}, {1,1} },
        { {0,0}, {1,0}, {2,0} },
        { {0,0}, {1,0}, {2,0}, {3,0} }
    };

    for (int i = 0; i < (int)testCases.size(); ++i) {
        cout << "Test case P" << i+1 << ":" << endl;
        cout << "Graham's Scan: ";
        vector<point> hullG = CH_Graham(testCases[i]);
        printPolygon(hullG);

        cout << "Andrew's Monotone Chain: ";
        vector<point> hullA = CH_Andrew(testCases[i]);
        printPolygon(hullA);
        cout << "--------------------------" << endl;
    }

    return 0;
}
