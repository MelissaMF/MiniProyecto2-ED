#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Quadtree.h"
#include <algorithm>
#include <string>

using namespace std;

vector<Node> readCSV(const string& filename)
{
    vector<Node> nodes;

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo CSV\n";
        return nodes;
    }
    
    string line;
    while (getline(file, line)) {
        stringstream ss(line);

        // Descartar los valores de las columnas 1, 2, 3, 4 y 8
        for (int i = 0; i < 4; i++) {
            string discard;
            getline(ss, discard, ';');
        }
        
        string column5Str, column6Str, column7Str;

        // Extraer los valores de las columnas 5, 6 y 7
        getline(ss, column5Str, ';');
        getline(ss, column6Str, ';');
        getline(ss, column7Str, ';');

        string discard; // Variable adicional para descartar el valor de la columna 8
        getline(ss, discard, ';'); // Descartar el valor de la columna 8

        // Convertir las cadenas a los tipos de datos adecuados
        int column5;
        double column6, column7;
        std::replace(column6Str.begin(), column6Str.end(), ',', '.');
        std::replace(column7Str.begin(), column7Str.end(), ',', '.');
        sscanf(column5Str.c_str(), "%d", &column5);
        sscanf(column6Str.c_str(), "%lf", &column6);
        sscanf(column7Str.c_str(), "%lf", &column7);

        
        column6 += 90.0;  // Sumar 90 a la latitud
        column7 += 180.0;  // Sumar 180 a la longitud

        // Crear el nodo con los valores de las columnas 5, 6 y 7
        Node node(Point(column6, column7), column5);

        // Agregar el nodo al vector
        nodes.push_back(node);
    }

    file.close();
    return nodes;
}
