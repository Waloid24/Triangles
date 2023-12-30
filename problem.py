import Geometry3D as geometry

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

    n_intersections = 0
    n_triangles = 2

    if 0:
        numbers = [29.3505, 805.295, 397.635, -248.565, -404.623, -873.618, -386.796, -76.4378, -878.078,
                    -120.028, -992.064, 12.6612, -729.661, -244.151, -979.961, 997.444, 982.96, -259.114]
    else:
        numbers = [2.93505, 80.5295, 39.7635, -24.8565, -40.4623, -87.3618, -38.6796, -7.64378, -87.8078,
                    -12.0028, -99.2064, 1.26612, -72.9661, -24.4151, -97.9961, 99.7444, 98.296,-25.9114]

    points = creating_points(numbers, n_triangles)
    triangles = creating_triangles(points, n_triangles)
    intersecting_indexes, n_intersections = intersecting_triangles(triangles)

    print(f"n_intersections = {n_intersections}")
        
main()