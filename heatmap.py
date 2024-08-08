import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as mcolors

# Step 1: Read the numbers from the file and reshape into an 800x600 array
file_path = 'timedatafile.txt'
with open(file_path, 'r') as file:
    times = [int(line.strip()) for line in file]

# Assuming the file has 480,000 numbers (800*600)
times_array = np.array(times).reshape((600, 800))

# Step 2: Normalize the time values using a logarithmic scale
# Avoid taking log(0) by adding 1 to each time value
normalized_times = np.log(times_array + 1)

# Step 3: Map the normalized values to colors using a colormap
# Use a colormap such as 'viridis' (green to yellow to blue) or 'hot' (black to red to yellow to white)
cmap = plt.get_cmap('hot')
norm = mcolors.Normalize(vmin=np.min(normalized_times), vmax=np.max(normalized_times))

# Create the heatmap
plt.figure(figsize=(10, 6))
plt.imshow(normalized_times, cmap=cmap, norm=norm)
plt.colorbar(label='Logarithm of Render Time (ns)')
plt.title('Render Time Heatmap')
plt.xlabel('Pixel X')
plt.ylabel('Pixel Y')
plt.show()
