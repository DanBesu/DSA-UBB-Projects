from graph.graph import Graph, GraphError


class Ui:

    def __init__(self, filename):
        self.__graph = Graph(filename)

    @staticmethod
    def print_menu():
        print("\n1. Exit \n2. Print the number of vertices  \n3. Print the number of Edges"
              "\n4. Print the outgoing edges \n5. Print the incoming edges \n6. Print all edges"
              "\n7. Check if edge exists \n8. Print the out-degree of a vertex \n"
              "9. Print the in-degree of a vertex \n10. Print the endpoint of an edge \n"
              "11. Modify the cost of an edge \n12. Print the cost of an edge \n"
              "13. Remove an edge \n14. Write graph to file \n15. Generate Random graph \n"
              "16. Add an edge\n17. Add a vertex \n18. Delete a vertex"
              "\n19. Print the incoming edges of a vertex \n20. Print the outgoing edges of a vertex\n"
              "21. Print all vertices")

    # def start_searching_path(self):
    #     minimum_length(self.__graph, 0, 6)

    def start(self):

        running = True
        while running is True:
            self.print_menu()
            try:
                command = int(input("< command ..."))
                if command == 1:
                    running = False
                if command == 2:
                    print(self.__graph.nr_vertices)
                elif command == 3:
                    print(self.__graph.nr_edges)
                elif command == 4:
                    self.__graph.print_dict_out()
                elif command == 5:
                    self.__graph.print_dict_in()
                elif command == 6:
                    self.__graph.print_edges()
                elif command == 7:
                    start = int(input("Enter the starting point of the edge ... "))
                    end = int(input("Enter the endpoint of the edge ... "))

                    if self.__graph.check_edge(start, end):
                        print("Edge exists")
                    else:
                        print("Edge does not exists")

                elif command == 8:
                    vertex = int(input("Enter the vertex number ... "))

                    print(self.__graph.out_degree(vertex))

                elif command == 9:
                    vertex = int(input("Enter the vertex number ... "))

                    print(self.__graph.in_degree(vertex))

                elif command == 10:

                    start = int(input("Enter the starting point of the edge ... "))
                    end = int(input("Enter the endpoint of the edge ... "))

                    print(self.__graph.end_point(start, end))

                elif command == 11:
                    start = int(input("Enter the starting point of the edge ... "))
                    end = int(input("Enter the endpoint of the edge ... "))

                    new_cost = int(input("Enter the new cost of the edge ... "))

                    self.__graph.update_cost(start, end, new_cost)

                elif command == 12:
                    start = int(input("Enter the starting point of the edge ... "))
                    end = int(input("Enter the endpoint of the edge ... "))

                    print("The cost is: " + str(self.__graph.get_edge_cost(start, end)))

                elif command == 13:
                    start = int(input("Enter the starting point of the edge ... "))
                    end = int(input("Enter the endpoint of the edge ... "))

                    self.__graph.remove_edge(start, end)

                elif command == 14:
                    self.__graph.write_graph_to_file("output.txt")

                elif command == 15:

                    nr_vertices = int(input("Enter the number of vertices for the random graph ... "))
                    nr_edges = int(input("Enter the number of edges for the random graph ... "))
                    self.__graph.generate_random_graph(nr_vertices, nr_edges)

                elif command == 16:

                    start = int(input("Enter the starting point of the edge ... "))
                    end = int(input("Enter the endpoint of the edge ... "))
                    cost = int(input("Enter the cost of the edge ... "))

                    self.__graph.add_edge(start, end, cost)

                elif command == 17:
                    vertex = self.__graph.add_vertex()
                    print('Vertex added: ', vertex)

                elif command == 18:
                    vertex = int(input("Enter the vertex ... "))
                    self.__graph.remove_vertex(vertex)
                elif command == 19:
                    vertex = int(input("Enter the vertex ... "))
                    self.__graph.print_dict_in_vertex(vertex)
                elif command == 20:
                    vertex = int(input("Enter the vertex ... "))
                    self.__graph.print_dict_out_vertex(vertex)
                elif command == 21:
                    self.__graph.print_all_vertices()

            except GraphError as ge:
                print(ge)
            except ValueError as ve:
                print(ve)
            except TypeError as te:
                print(te)


ui = Ui("input_graph.txt")
ui.start()

# def start_without_ui():
#     graph = Graph("input_graph.txt")
#
#     print(graph.check_edge(2, 7))
#     # True
#     new_graph = graph.copy_graph()
#
#     print(new_graph.check_edge(2,7))
#     # True
#     new_graph.remove_vertex(2)
#
#     print(new_graph.check_edge(2,7))
#     # False
#
#     print(graph.check_edge(2,7))
#     # True

#
# start_without_ui()
