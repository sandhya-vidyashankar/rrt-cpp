import numpy as np
import sys

if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: python generate_map.py <x_size> <y_size> <num_obstacles>")
        sys.exit(1)
    
    x_size = int(sys.argv[1])
    y_size = int(sys.argv[2])
    num_obstacles = int(sys.argv[3])
    
    # Create an empty map
    map_data = np.zeros((x_size, y_size), dtype=int)

    # Define the amount of free space
    num_free_cells = int(0.8 * x_size * y_size)  # 80% of the map will be free space

    # Randomly generate free space
    free_space_indices = np.random.choice(x_size * y_size, num_free_cells, replace=False)
    map_data.flat[free_space_indices] = 0

    # Add some obstacles
    for _ in range(num_obstacles):
        # Randomly select obstacle size
        obstacle_size_x = np.random.randint(5, 20)
        obstacle_size_y = np.random.randint(5, 20)
        # Randomly select obstacle position
        obstacle_x = np.random.randint(0, x_size - obstacle_size_x)
        obstacle_y = np.random.randint(0, y_size - obstacle_size_y)
        # Add obstacle to the map
        map_data[obstacle_x:obstacle_x+obstacle_size_x, obstacle_y:obstacle_y+obstacle_size_y] = 1

    # Save map data to a text file
    with open('random_map.txt', 'w') as file:
        file.write(f"{x_size} {y_size}\n")
        for row in map_data:
            file.write(" ".join(map(str, row)) + "\n")
