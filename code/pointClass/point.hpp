#ifndef POINT_APP
#define POINT_APP

class Point {
    public:
        int x;
        int y;
    
    Point(int x, int y);
    Point();
    bool operator==(const Point& other);
};

#endif