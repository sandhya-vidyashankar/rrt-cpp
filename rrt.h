#include <vector>
#include <iostream>
#include <random>
#include <unordered_map>
#include <math.h>
#include <algorithm>
using namespace std;

    
/*
Assumptions- map is given as a vector of vector of int, where 0 is free space and 1 is an obstacle

*/
struct Map{
    vector<vector<int>> occupancy_grid;
    int x_size;
    int y_size;
};

struct Point{ //Struct to store information about each point
    int x;
    int y;
    Point(int x_, int y_): x(x_), y(y_){}
    Point() {}
};

class RRT{
    public:
        Map map;
        unordered_map<int, int> parent; //pairs of child and parent 
        vector<Point> tree; // List of all samples
        vector<Point> path; //List of points from start to goal, solution to the planner
        //Params
        double step_size = 1.0; //Size of one step when expanding RRT
        double goal_threshold = 2.0; //If we sample a point within this distance of goal, we check the goal condition
        int num_iters = 10000;
        //Main functions
        bool extend(Point sample);
        void solveRRT(Point start, Point goal);
        void formatSolution();

        //Constructor 
        RRT(Map map_): map(map_) {}

    private:

        Point drawSample(); //Function to get sample
        bool isValidPoint(Point& sample); //Checks if point is in obstacle
        bool isValidEdge(Point& from, Point& to); //Checks if all points between two points are valid
        bool isGoal(Point& point, Point& goal); //Checks for point within goal threshold
        int getNearestPointIndex(Point& sample); //Finds the index of the nearest node to a sample
        

        //Simple helper functions for calculations below
        int getRandomInt(int min, int max){ //Generates a random integer between min and max
            static std::random_device rd;
            static std::mt19937 gen(rd());

            std::uniform_int_distribution<> distr(min, max);
            
            return distr(gen);
        } 

        double euclideanDistance(Point& start, Point& goal){ //Euclidean distance between two points
            return sqrt(pow(start.x - goal.x, 2) + pow(start.y - goal.y, 2));
        }


        int getStepDirection(int& from, int& to){
            int direction; //Returns -1 or 1 based on the direction between two points
            if ((to - from) < 0){
                direction = -1;
            }
            else if ((to - from) > 0) {
                direction = 1;
            }
            else{
                direction = 0;
            }
            return direction;
        }
};