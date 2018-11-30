#include <bits/stdc++.h>
using namespace std;

#define eprint(x) cerr << "[" << __LINE__ << "]\t" << #x " = " << (x) << endl
#ifndef LOCAL
#define cerr if (false) cerr
#endif

#define endl '\n'
using ll = long long;
using ptype = ll;

struct Point {
    ptype x, y;
    
    Point() : x(0), y(0) {}
    
    Point(ptype _x, ptype _y) : x(_x), y(_y) {}
    
    bool operator== (Point b) {
        return x == b.x && y == b.y;
    }
    
    bool operator< (Point b) {
        return x < b.x || (x == b.x && y < b.y);
    }
    
    Point operator- (Point b) {
        return Point(x - b.x, y - b.y);
    }
    
    ptype operator* (Point b) {
        return x * b.y - y * b.x;
    }
    
    long double len() {
        return sqrtl(x * x + y * y);
    }
};

bool ccw(Point a, Point b) {
    return a * b > 0;
}

bool ccw(Point a, Point b, Point c) {
    return ccw(b - a, c - a);
}

vector<Point> convexHull(vector<Point> pts) {
    sort(pts.begin(), pts.end());
    vector<Point> hull;
    for (int phase = 0; phase < 2; phase++) {
        int start = hull.size();
        for (auto pt : pts) {
            while (hull.size() >= start + 2) {
                auto pt1 = hull[hull.size() - 2];
                auto pt2 = hull[hull.size() - 1];
                if (ccw(pt1, pt2, pt))
                    break;
                hull.pop_back();
            }
            hull.push_back(pt);
        }
        hull.pop_back();
        reverse(pts.begin(), pts.end());
    }
    if (hull.size() == 2 && hull[0] == hull[1])
        hull.pop_back();
    return hull;
}

int main() {
    freopen("hullp.in", "r", stdin);
    freopen("hullp.out", "w", stdout);
    
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout << setprecision(20) << fixed;
    
    int n;
    cin >> n;
    vector<Point> pts;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        pts.emplace_back(x, y);
    }
    auto hull = convexHull(pts);
    long double p = 0;
    for (int i = 0; i < hull.size(); i++)
        p += (hull[(i + 1) % hull.size()] - hull[i]).len();
    cout << p << endl;
}