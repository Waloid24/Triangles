import Geometry3D as geometry
import sys

def get_coords(file_name):

    numbers = []
    with open(f"{file_name}", "r") as test_file:
        for line in test_file:
            for x in line.split():
                numbers.append(float(x))

    n_triangles = int(numbers[0])
    numbers.pop(0)

    return numbers, n_triangles

def creating_points(numbers, n_triangles):

    n_numbers = n_triangles*9
    points = []

    for i in range(0, n_numbers, 3):
        points.append(geometry.Point(numbers[i], numbers[i+1], numbers[i+2]))

    return points

def creating_triangles(points, n_triangles):

    triangles = []
    n_points = n_triangles*3

    for i in range(0, n_points, 3):
        triangles.append(geometry.ConvexPolygon((points[i], points[i+1], points[i+2])))

    return triangles

def intersecting_triangles(triangles):

    intersecting_indexes = []
    n_intersections = 0

    for i in range(len(triangles) - 1):
        for j in range(i + 1, len(triangles)):   
            if geometry.intersection(triangles[i], triangles[j]):
                if i not in intersecting_indexes:
                    intersecting_indexes.append(i)
                if j not in intersecting_indexes:
                    intersecting_indexes.append(j)
                n_intersections = n_intersections + 1
    return intersecting_indexes, n_intersections

def main():
    
    n_tests = int(sys.argv[1])
    test_folder = sys.argv[2]
    answers_folder = sys.argv[3]

    for it in range(n_tests):

        test_file = f"{test_folder}/test_{it}.txt"
        answers_file = f"{answers_folder}/answer_{it}.txt"
        n_intersections = 0

        numbers, n_triangles = get_coords(test_file)
        points = creating_points(numbers, n_triangles)
        triangles = creating_triangles(points, n_triangles)
        intersecting_indexes, n_intersections = intersecting_triangles(triangles)
        intersecting_indexes.sort()

        with open(answers_file, "w") as ans_file:
            for number in intersecting_indexes:
                ans_file.write(str(number) + '\n')
        
main()
