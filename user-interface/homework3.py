from graph.graph import Graph

# 2. Write a program that, given a graph with positive costs and two vertices,
# finds a lowest cost walk between the given vertices,
# using a "backwards" Dijkstra algorithm (Dijkstra algorithm that searches backwards, from the ending vertex).


class PriorityQueue:
    def __init__(self):
        self.__values = {}

    def is_empty(self):
        return len(self.__values) == 0

    def pop(self):
        top_priority = None
        top_object = None

        for obj in self.__values:
            obj_priority = self.__values[obj]
            if top_priority is None or top_priority > obj_priority:
                top_priority = obj_priority
                top_object = obj
        del self.__values[top_object]
        return top_object

    def add(self, obj, priority):
        self.__values[obj] = priority

    def contains(self, val):
        return val in self.__values


def compute_path(prev, starting_vertex, ending_vertex):
    _path = [starting_vertex]
    current_vertex = starting_vertex
    while _path[-1] != ending_vertex:
        _path.append(prev[current_vertex])
        current_vertex = prev[current_vertex]
    return _path


def dijkstra(_graph, start_vertex, destination_vertex):
    prev = {}
    queue = PriorityQueue()
    queue.add(destination_vertex, 0)
    distance = {destination_vertex: 0}
    visited = set()
    visited.add(destination_vertex)

    while not queue.is_empty():

        current_vertex = queue.pop()
        for y in _graph.get_all_in_for_vertex(current_vertex):

            if y not in visited or distance[y] > distance[current_vertex] + _graph.get_edge_cost(y, current_vertex):
                distance[y] = distance[current_vertex] + _graph.get_edge_cost(y, current_vertex)
                visited.add(y)
                queue.add(y, distance[y])
                prev[y] = current_vertex

    _path = compute_path(prev, start_vertex, destination_vertex)
    return _path, distance[start_vertex]


graph = Graph("graph1k.txt")

print('\n ###################################### FROM 1 TO 100 ######################################\n')
for i in range(1, 100):
    print('start: ', i, ' end: ', 100 - i + 1)
    try:
        path, dist = dijkstra(graph, i, 100 - i + 1)
        print("path:", path)
        print("distance to start: ", dist, '\n')
    except KeyError as ke:
        print("vertex not found\n")

print('\n ###################################### FROM 100 TO 1 ######################################\n')
for i in range(100, 1, -1):
    print('start: ', i, ' end: ', 100 - i + 1)
    try:
        path, dist = dijkstra(graph, i, 100 - i + 1)
        print("path:", path)
        print("distance to start: ", dist, '\n')
    except KeyError as ke:
        print("vertex not found\n")
