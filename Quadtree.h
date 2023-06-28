#ifndef QUADTREE_H
#define QUADTREE_H
#include<ostream>

struct Point {
    double x;
    double y;
    Point(double _x, double _y)
    {
        x = _x;
        y = _y;
    }
    Point()
    {
        x = 0;
        y = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    }
};

struct Node {
    Point pos;
    int data;
    Node(Point _pos, int _data)
    {
        pos = _pos;
        data = _data;
    }
    Node() { data = 0; }
};

class Quad {
    Point topLeft;
    Point botRight;
    Node* n;
    Quad* topLeftTree;
    Quad* topRightTree;
    Quad* botLeftTree;
    Quad* botRightTree;

public:
    Quad();
    Quad(Point topL, Point botR);
    ~Quad(); // Destructor para liberar la memoria de los subárboles
    void insert(Node* node);
    Node* search(Point p);
    bool inBoundary(Point p) const;
    int CountRegion(Point p, int d) const;
    void CountRegionHelper(Point p, int d, int& pointCount) const;
    int AggregateRegion(Point p, int d) const;
    void AggregateRegionHelper(Point p, int d, int& population) const;
};

#endif
