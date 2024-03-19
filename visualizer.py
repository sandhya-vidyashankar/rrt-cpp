import numpy as np
import matplotlib.pyplot as plt

# Function to read path from a text file
def read_path_from_file(filename):
    path = []
    with open(filename, 'r') as file:
        for line in file:
            x, y = map(int, line.split())
            path.append((x, y))
    return path

map_file = "map4.txt"
# Read map data from file
with open(map_file, 'r') as f:
    x_size, y_size = map(int, f.readline().split())
    map_data = [[int(num) for num in line.split()] for line in f]

# Read path from file
path_data = read_path_from_file('output.txt')

# Convert map data to numpy array for visualization
map_array = np.array(map_data)

# Visualize the map
plt.figure(figsize=(10, 10))
plt.imshow(map_array, cmap='gray', origin='lower')

# Plot the path
path_x = [point[1] for point in path_data]
path_y = [point[0] for point in path_data]
plt.plot(path_x, path_y, marker='o', color='red')

plt.title('Path Planning Visualization')
plt.xlabel('X')
plt.ylabel('Y')
plt.grid(True)
plt.show()
