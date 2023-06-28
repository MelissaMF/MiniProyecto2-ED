#include "Quadtree.h"

Quad::Quad()
{
    n = nullptr;
    topLeftTree = nullptr;
    topRightTree = nullptr;
    botLeftTree = nullptr;
    botRightTree = nullptr;
}

Quad::Quad(Point topL, Point botR)
{
    topLeft = topL;
    botRight = botR;
    n = nullptr;
    topLeftTree = nullptr;
    topRightTree = nullptr;
    botLeftTree = nullptr;
    botRightTree = nullptr;
}

Quad::~Quad()
{
    delete n;
    delete topLeftTree;
    delete topRightTree;
    delete botLeftTree;
    delete botRightTree;
}

void Quad::insert(Node* node)
{
    if (!inBoundary(node->pos))
        return;

    if (n == nullptr) {
        n = new Node(node->pos, node->data);
        return;
    }

    double xMid = (topLeft.x + botRight.x) / 2;
    double yMid = (topLeft.y + botRight.y) / 2;

    if (node->pos.x <= xMid && node->pos.y <= yMid) {
        if (topLeftTree == nullptr)
            topLeftTree = new Quad(Point(topLeft.x, topLeft.y), Point(xMid, yMid));
        topLeftTree->insert(node);
    } else if (node->pos.x <= xMid && node->pos.y > yMid) {
        if (botLeftTree == nullptr)
            botLeftTree = new Quad(Point(topLeft.x, yMid), Point(xMid, botRight.y));
        botLeftTree->insert(node);
    } else if (node->pos.x > xMid && node->pos.y <= yMid) {
        if (topRightTree == nullptr)
            topRightTree = new Quad(Point(xMid, topLeft.y), Point(botRight.x, yMid));
        topRightTree->insert(node);
    } else if (node->pos.x > xMid && node->pos.y > yMid) {
        if (botRightTree == nullptr)
            botRightTree = new Quad(Point(xMid, yMid), Point(botRight.x, botRight.y));
        botRightTree->insert(node);
    }
}

Node* Quad::search(Point p)
{
    if (!inBoundary(p))
        return nullptr;

    if (n != nullptr && n->pos.x == p.x && n->pos.y == p.y)
        return n;

    double xMid = (topLeft.x + botRight.x) / 2;
    double yMid = (topLeft.y + botRight.y) / 2;

    if (p.x <= xMid && p.y <= yMid) {
        if (topLeftTree == nullptr)
            return nullptr;
        return topLeftTree->search(p);
    } else if (p.x <= xMid && p.y > yMid) {
        if (botLeftTree == nullptr)
            return nullptr;
        return botLeftTree->search(p);
    } else if (p.x > xMid && p.y <= yMid) {
        if (topRightTree == nullptr)
            return nullptr;
        return topRightTree->search(p);
    } else if (p.x > xMid && p.y > yMid) {
        if (botRightTree == nullptr)
            return nullptr;
        return botRightTree->search(p);
    }

    return nullptr;
}

bool Quad::inBoundary(Point p) const
{
    return (p.x >= topLeft.x && p.x <= botRight.x && p.y >= topLeft.y && p.y <= botRight.y);
}

int Quad::CountRegion(Point p, int d) const
{
    int pointCount = 0;
    CountRegionHelper(p, d, pointCount);
    return pointCount;

}

int Quad::AggregateRegion(Point p, int d) const
{
    int population = 0;
    AggregateRegionHelper(p, d, population);
    return population;
}

void Quad::CountRegionHelper(Point p, int d, int& pointCount) const
{
    if (!inBoundary(p))
        return;

    if (n != nullptr && n->pos.x >= p.x && n->pos.x < (p.x + d) && n->pos.y >= p.y && n->pos.y < (p.y + d)) {
        pointCount++;
    }

    if (topLeftTree != nullptr)
        topLeftTree->CountRegionHelper(p, d, pointCount);
    if (topRightTree != nullptr)
        topRightTree->CountRegionHelper(p, d, pointCount);
    if (botLeftTree != nullptr)
        botLeftTree->CountRegionHelper(p, d, pointCount);
    if (botRightTree != nullptr)
        botRightTree->CountRegionHelper(p, d, pointCount);
}

void Quad::AggregateRegionHelper(Point p, int d, int& population) const
{
    if (!inBoundary(p))
        return;

    if (n != nullptr && n->pos.x >= p.x && n->pos.x < (p.x + d) && n->pos.y >= p.y && n->pos.y < (p.y + d)) {
        population += n->data;
    }

    if (topLeftTree != nullptr)
        topLeftTree->AggregateRegionHelper(p, d, population);
    if (topRightTree != nullptr)
        topRightTree->AggregateRegionHelper(p, d, population);
    if (botLeftTree != nullptr)
        botLeftTree->AggregateRegionHelper(p, d, population);
    if (botRightTree != nullptr)
        botRightTree->AggregateRegionHelper(p, d, population);
}

