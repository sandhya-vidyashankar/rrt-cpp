#include <iostream>
#include <fstream>
#include <cstdlib>
#include "rrt.h"

// Function to load map from a text file
Map loadMapFromFile(const std::string& filename) {
    Map map;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return map;
    }

    // Read map size
    file >> map.x_size >> map.y_size;
    file.ignore(); // Ignore the newline character

    // Resize the map data vector
    map.occupancy_grid.resize(map.x_size, std::vector<int>(map.y_size));

    // Read map data
    for (int i = 0; i < map.x_size; ++i) {
        for (int j = 0; j < map.y_size; ++j) {
            file >> map.occupancy_grid[i][j];
        }
    }

    file.close();
    return map;
}

// Function to write path to a file
void writePathToFile(const std::vector<Point>& path, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    // Write each point in the path to the file
    for (const Point& point : path) {
        file << point.x << " " << point.y << std::endl;
    }

    file.close();
    std::cout << "Path has been written to " << filename << std::endl;
}

int main(int argc, char* argv[]) {
    string map_file = "map1.txt";
    if (argc > 1){
        map_file = argv[1];
    }
    else{
        cout << "No argument for map, using default (map1)" << endl;
    }
    Map testMap = loadMapFromFile(map_file);

    // Define start and goal points
    Point start(200, 200);
    Point goal(300, 300);

    // Create an instance of RRT
    RRT rrt(testMap);

    // Solve RRT
    rrt.solveRRT(start, goal);

    // Output the path
    vector<Point> path = rrt.path;

    writePathToFile(path, "output.txt");

    return 0;
}