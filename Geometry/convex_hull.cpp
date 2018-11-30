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