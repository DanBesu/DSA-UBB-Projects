import copy
import random


class GraphError(Exception):
    def __init__(self, message):
        self._message = message


class Graph:

    def __init__(self, filename):
        self.__in = {}
        self.__out = {}
        self.edges_cost = {}
        self.__nr_vertices = 0
        self.__nr_edges = 0

        self.read_graph_from_file(filename)

    @property
    def nr_vertices(self):
        return self.__nr_vertices

    @property
    def nr_edges(self):
        return self.__nr_edges

    """""" """ """""" """"""GRAPH RELATED FUNCTIONALITIES"""""" """""" """ """"""

    def init_empty_graph(self):
        """
        Initialise an empty graph
        :return: none
        """
        self.__in.clear()
        self.__out.clear()
        for index in range(self.__nr_vertices):
            self.init_vertex(index)

    def copy_graph(self):
        # Function that returns a deep copy of the with the current state of the current graph
        return copy.deepcopy(self)

    def parse_x(self):
        # returns an iterable structure containing all vertices
        return self.__out.keys()

    def read_graph_from_file(self, name_of_file):
        # read a graph from a file and initialize it
        # read the first line which contains the vertices number and the number of edges
        # iterate through the rest of the file which contain the edges
        file = open(name_of_file, 'r')

        first_line = file.readline()
        first_line = first_line.split()

        number_vertices = int(first_line[0])
        number_edges = int(first_line[1])

        self.__nr_vertices = number_vertices

        for i in range(self.__nr_vertices):
            self.__in[i] = []
            self.__out[i] = []

        # Reading the edges
        file_lines = file.readlines()

        for line in file_lines:
            current_line = line.split()
            self.add_edge(int(current_line[0]), int(current_line[1]), int(current_line[2]))

    def write_graph_to_file(self, name_of_file):
        # Function that write the current graph to a file
        file = open(name_of_file, "w")
        first_line = str(self.__nr_vertices) + ' ' + str(self.__nr_edges) + '\n'
        file.write(first_line)

        for edge in self.edges_cost:
            line = str(edge[0]) + " " + str(edge[1]) + " " + str(self.edges_cost[edge]) + "\n"
            file.write(line)

    def generate_random_graph(self, number_vertices, nr_edges):
        # Function that overwrite the current state of the graph with a random one

        if number_vertices * number_vertices < nr_edges:
            raise GraphError('too many edges, please try again')

        self.__out.clear()
        self.__in.clear()
        self.edges_cost.clear()

        self.__nr_vertices = number_vertices
        self.__nr_edges = nr_edges

        for vertex in range(number_vertices):
            self.__out[vertex] = []
            self.__in[vertex] = []

        for edge in range(nr_edges):

            status = False
            while not status:
                start = random.randint(0, number_vertices)
                end = random.randint(0, number_vertices)

                cost = random.randint(-100, 100)
                status = self.add_edge(start, end, cost)

        self.__nr_edges /= 2
    """""" """ """""" """""" VERTEX RELATED FUNCTIONALITIES """""" """""" """ """"""

    def get_all_vertices(self):
        """
        returns all the vertices from a graph
        """
        vertices = []
        for vertex in self.__in:
            if vertex not in vertices:
                vertices.append(vertex)
        for vertex in self.__out:
            if vertex not in vertices:
                vertices.append(vertex)
        return vertices

    def print_all_vertices(self):
        vertices = self.get_all_vertices()
        for vertex in vertices:
            print(vertex)

    def init_vertex(self, vertex):
        """
        Adds an isolated vertex at a given position
        :param vertex: integer
        :return: none
        """
        self.__in[vertex] = []
        self.__out[vertex] = []

    def existent_vertex(self, vertex):
        """
        Checks if a vertex exists in the graph
        :param vertex: integer, the vertex to be checked
        :return: boolean value regarding the statement
        """
        return vertex in self.__in.keys() or vertex in self.__out.keys()

    def add_vertex(self):
        """
        Adds a new vertex to the graph
        :return: none
        """
        self.init_vertex(self.__nr_vertices)
        self.__nr_vertices += 1
        return self.__nr_vertices - 1

    def remove_vertex(self, vertex):
        """
        Removes a given vertex from the graph
        :return: none
        :raises: GraphError, if the vertex doesn't exist
        """
        if vertex not in self.__out.keys():
            raise GraphError("vertex not found")

        self.__in.pop(vertex, None)
        self.__out.pop(vertex, None)

        copy_dict = self.edges_cost.copy()

        for (v1, v2) in copy_dict.keys():
            if v1 == vertex or v2 == vertex:
                del self.edges_cost[(v1, v2)]

    def in_degree(self, vertex):
        """
        Finds the in degree of a vertex
        :param vertex: integer
        :return: the in degree for the given vertex
        """
        if not self.existent_vertex(vertex):
            raise GraphError('there is no such vertex')

        return len(self.__in[vertex])

    def out_degree(self, vertex):
        """
        Finds the out degree of a vertex
        :param vertex: integer
        :return: the out degree for the given vertex
        """
        if not self.existent_vertex(vertex):
            raise GraphError('there is no such vertex')

        return len(self.__out[vertex])

    def get_all_in_for_vertex(self, vertex):
        if self.existent_vertex(vertex):
            return self.__in[vertex]
        raise GraphError('this vertex doesn"t exist')

    def get_all_out_for_vertex(self, vertex):
        if self.existent_vertex(vertex):
            return self.__out[vertex]
        raise GraphError('this vertex doesn"t exist')

    def print_dict_in_vertex(self, vertex):
        if self.existent_vertex(vertex):
            print(vertex, '<-', self.__in[vertex])
        raise GraphError('this vertex doesn"t exist')

    def print_dict_out_vertex(self, vertex):
        if self.existent_vertex(vertex):
            print(vertex, '->', self.__out[vertex])
        raise GraphError('this vertex doesn"t exist')

    """""" """ """""" """""" EDGE RELATED FUNCTIONALITIES """""" """""" """ """"""

    def print_dict_in(self):
        for vertex in self.__in:
            print(vertex, '<-', self.__in[vertex])

    def print_dict_out(self):
        for vertex in self.__out:
            print(vertex, '<-', self.__out[vertex])

    def print_edges(self):

        for edge in self.edges_cost:
            print(edge, ': ', self.edges_cost[edge])

    def get_all_edges(self):
        return self.edges_cost

    def check_edge(self, src_vertex, dest_vertex):
        """
        check if an edge exists
        :return: boolean value regarding the statement
        """

        return (src_vertex, dest_vertex) in self.edges_cost

    def get_edge_cost(self, v1, v2):
        if v2 not in self.__out[v1]:
            raise GraphError("Edge not existent!")
        return self.edges_cost[(v1, v2)]

    def add_edge(self, src_vertex, dest_vertex, cost):
        """
        Adds a new edge to the graph
        :param src_vertex: int
        :param dest_vertex: int
        :param cost: int
        """
        if not self.existent_vertex(src_vertex) or not self.existent_vertex(dest_vertex):
            return False

        if self.check_edge(src_vertex, dest_vertex):
            return False

        if self.__nr_vertices * (self.__nr_vertices + 1) < self.__nr_edges + 1 and self.__nr_vertices > 1:
            raise GraphError('too many edges, please try add new vertex')

        self.__in[dest_vertex].append(src_vertex)
        self.__out[src_vertex].append(dest_vertex)
        self.edges_cost[(src_vertex, dest_vertex)] = cost
        self.__nr_edges += 1
        return True

    def remove_edge(self, src_vertex, dest_vertex):
        """
        Removes an edge from the graph
        :param src_vertex: int
        :param dest_vertex: int
        :return: none
        :raises: GraphError, if one of the vertices doesn't exist or the edge is already existent
        """
        if not self.existent_vertex(src_vertex) or not self.existent_vertex(dest_vertex):
            raise GraphError("Invalid Vertices")

        self.__in[dest_vertex].remove(src_vertex)
        self.__out[src_vertex].remove(dest_vertex)
        del self.edges_cost[(src_vertex, dest_vertex)]
        self.__nr_edges -= 1
        print(self.__nr_vertices)

    def update_cost(self, v1, v2, new_cost):
        self.check_edge(v1, v2)
        self.edges_cost[(v1, v2)] = new_cost

    def end_point(self, vertex1, vertex2):
        # Returns the endpoint of 2 vertices if there is an edge between them
        if vertex2 in self.__out[vertex1]:
            return vertex2

        elif vertex1 in self.__out[vertex2]:
            return vertex1

        else:
            raise GraphError('no edge between these vertices')
