import random 
import sys
import numpy as np

def generate_coords_array(n_tests: int, output_dir):
    
    for test_i in range(n_tests):

        num_triangles = 2 #np.random.randint(3, 10)
        num_points = 3*num_triangles
        num_coords = 3*num_points
        coords = []
        coords = np.random.uniform(-16, 16, num_coords)
        
        with open(f"./{output_dir}/test_{test_i}.txt", "w") as test_file:
            test_file.write(str(num_triangles) + "\n")

            for it in range(0, num_coords, 3):
                test_file.write(f"{round(coords[it], 6)} {round(coords[it+1], 6)} {round(coords[it+2], 6)} ")
            test_file.write("\n")

n_tests: int = int(sys.argv[1])
output_dir = str(sys.argv[2])

generate_coords_array(n_tests, output_dir)

