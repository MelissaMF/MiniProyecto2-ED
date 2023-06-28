#include <iostream>
#include <vector>
#include "Quadtree.h"
#include "readcsv.cpp"
#include <chrono>

using namespace std;
using namespace std::chrono;

void testInsertion(const vector<Node>& nodes)
{
    Quad center(Point(0, 0), Point(360, 180));

    for (const auto& node : nodes) {
        center.insert(new Node(node.pos, node.data));
    }
}

void testRegionQuery(const Quad& quad, const Point& queryPoint, int area)
{
    int pointCount = quad.CountRegion(queryPoint, area);
    int population = quad.AggregateRegion(queryPoint, area);
}

int main()
{
    vector<Node> nodes = readCSV("worldcitiespop_fixed.csv");

    // Experimento 1: Tiempo de insercion
    std::cout << "Experimento 1: Tiempo de insercion\n";
    vector<int> numCities = {5000, 10000, 25000, 50000, 100000, 150000, 200000, 250000, 300000, 500000};
    for (int num : numCities) {
        vector<Node> subset(nodes.begin(), nodes.begin() + num);
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 20; i++) {
            Quad center(Point(0, 0), Point(360, 180)); // Crear un nuevo Quadtree para cada prueba
            for (const auto& node : subset) {
                center.insert(new Node(node.pos, node.data));
            }            
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "Num Ciudades: " << num << ", Tiempo Promedio: " << duration.count() / 20.0 << " ms\n";
    }

std::cout << "Experimento 2: Tiempo de consulta de region\n";
    vector<int> areas = { 5, 10, 15 };
    Point queryPoint(10, 10);
    Quad center(Point(0, 0), Point(360, 180)); // Crear el Quadtree fuera del bucle
    for (const auto& node : nodes) {
        center.insert(new Node(node.pos, node.data));
        //std::cout << "Nodo creado: " << node.pos << " - " << node.data << std::endl;
    }
    for (const int& area : areas) {
        auto start = high_resolution_clock::now();
        for (int i = 0; i < 20; i++) {
            testRegionQuery(center, queryPoint, area); // Pasar el objeto Quadtree original por referencia constante
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        std::cout << "Dimension area: " << area << ", Tiempo Promedio: " << duration.count() / 20.0 << " ms\n";
    }

    return 0;
}
 


