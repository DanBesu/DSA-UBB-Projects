from graph.graph import Graph

"2. Write a program that, given a directed graph and two vertices, " \
"finds a lowest length path between them, " \
"by using a backward breadth-first search from the ending vertex."


def find_accessible_vertices_backwards(graph, destination):
    if destination not in graph.get_all_vertices():
        raise ValueError("The end vertex is not in the graph.")

    visited = []
    queue = []
    next_vertex = {}
    end_distance = {}

    queue.append(destination)
    visited.append(destination)
    end_distance[destination] = 0
    while len(queue) > 0:
        current_vertex = queue[0]
        queue = queue[1:]
        for vertex in graph.get_all_in_for_vertex(current_vertex):
            edge_cost = graph.edges_cost[(vertex, current_vertex)]

            if vertex not in visited:
                visited.append(vertex)
                queue.append(vertex)
                end_distance[vertex] = end_distance[current_vertex] + 1
                next_vertex[vertex] = current_vertex

    return next_vertex


def find_minimum_length_path(graph, start_vertex, destination_vertex):
    next_vertex = find_accessible_vertices_backwards(graph, destination_vertex)

    if start_vertex not in next_vertex.keys():
        raise ValueError("There is no path from " + str(start_vertex) + " to " + str(destination_vertex))

    path = [start_vertex]
    previous_vertex = start_vertex
    reached_end = False
    while not reached_end:
        path.append(next_vertex[previous_vertex])
        previous_vertex = next_vertex[previous_vertex]
        if path[-1] == destination_vertex:
            reached_end = True

    return path


def main():
    new_graph = Graph("graph1k.txt")
    try:
        path = find_minimum_length_path(new_graph, 0, 110)
        print("The lowest path:")
        string_path = ""
        for vertex in path:
            string_path = string_path + str(vertex) + " -> "
        string_path = string_path[:-4]
        print(string_path)
    except ValueError as e:
        print(e)


# main()

g = Graph("input_graph.txt")
print(find_accessible_vertices_backwards(g, 6))
