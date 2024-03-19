#include "rrt.h"
using namespace std;
/*************************MAIN RRT PLANNER FUNCTIONS*****************/
void RRT::solveRRT(Point start, Point goal){
    cout << "Initializing RRT with start ("<< start.x << ", " << start.y << ") and Goal (" << goal.x << ", " << goal.y << ")" << endl;
    //Push back start node and initialize tree
    tree.push_back(start);
    parent[0] = -1; //Parent of start node
    step_size = 3;
    //Enter loop
    for (int iter = 0; iter < num_iters; iter++){
        Point sample = drawSample(); //Draw a random sample within map bounds
        if (iter % 5 == 0){ //Sample the goal every 5 iterations
            sample = goal;
        }
        // cout << "Sample: " << sample.x << " , " << sample.y << endl;
        if (!isValidPoint(sample)){ //Check that sample is valid
            continue;
        }

        if (extend(sample)){ //If we have sucessfully extended
            if (isGoal(tree.back(), goal)){ //Check if the last point in the tree is in the goal region
                tree.push_back(goal); //Add goal to tree
                parent[tree.size() - 1] = tree.size() - 2; //Add the goal parent to parent list
                formatSolution();
                std::cout << "Successfully found path of length: " << path.size() <<" in " << iter << "iterations" << std::endl; 
                return;
            }

        }
    }

   cerr << "Failed to find path" << endl;

}

bool RRT::extend(Point sample){
    
    int nearest_point_index = getNearestPointIndex(sample);
    Point* nearest = &tree[nearest_point_index];
    // cout << "Nearest point: " << nearest->x << " , " << nearest->y << endl;
    Point new_point; //New point in the direction of sample
    // cout <<  nearest->x << ", " << getStepDirection(nearest->x, sample.x) << ", "<< step_size <<endl;
    new_point.x = nearest->x + getStepDirection(nearest->x, sample.x)*step_size;
    new_point.y = nearest->y + getStepDirection(nearest->y, sample.y)*step_size;
    bool temp = isValidPoint(new_point);
    // cout << "New point: " << new_point.x << " , " << new_point.y << "Valid? " << temp << endl;
    if (isValidEdge(tree[nearest_point_index], new_point)){
        tree.push_back(new_point);
        parent[tree.size()-1] =  nearest_point_index;
        // cout << "Moving" << endl;
        
        return true; //Success

    }
    // cout << "Trapped" << endl;
    return false; //Trapped
}

void RRT::formatSolution(){
    int current_index = tree.size() -1 ;
    while (current_index != -1){
        path.push_back(tree[current_index]);
        current_index = parent[current_index];
    }
    reverse(path.begin(), path.end());

}

/*************************HELPER FUNCTIONS*****************/
Point RRT::drawSample(){
    Point sample;
    sample.x = this->getRandomInt(0, map.x_size - 1);
    sample.y = this->getRandomInt(0, map.y_size - 1);
    return sample;
}

int RRT::getNearestPointIndex(Point& sample){
    double min_distance = 10000;
    int nearest_point_index = 0;
    for (int i = 0; i < tree.size(); i++){
        if (euclideanDistance(tree[i], sample) < min_distance){
            min_distance = euclideanDistance(tree[i], sample);
            nearest_point_index = i;
        }
    }
    return nearest_point_index;
}

bool RRT::isValidPoint(Point& sample){
    //Check if within map bounds 
    if (sample.x < 0 || sample.x >= map.x_size || sample.y < 0 || sample.y >= map.y_size){
        cout << "Out of bounds" << endl;
        return false;
    }
    //Check for collision
    if (map.occupancy_grid[sample.x][sample.y] == 1){
        return false;
    }
    else{
        return true;
    }
}

bool RRT::isValidEdge(Point& start, Point& goal){
    if (step_size == 1) { //No need to interpolate 
        if (isValidPoint(goal)){ 
            return true;
        }
        else {
            return false;
        }
    }
    //Interpolate between start and goal, check every point along the way
    int x_direction = getStepDirection(start.x, goal.x);
    int y_direction = getStepDirection(start.y, goal.y);
    for (int i = start.x; i <= goal.x; i+= x_direction){
        for (int j = start.y; j <= goal.y; j+= y_direction){
            Point temp(i, j);
            if (!isValidPoint(temp)){
                return false;
            }
        }
    }
    return true;
}

bool RRT::isGoal(Point& point, Point& goal){
    if ((euclideanDistance(point, goal) < goal_threshold) && isValidEdge(point, goal)){
        return true;
    }
    return false;

}






