# 5. Write a program that, given an undirected connected graph,
# constructs a minimal spanning tree using the Kruskal's algorithm.

# A text file containing a detailed manual execution of the algorithm:
# Prim’s or Kruskal’s (see the additional files) for an undirected graph with 8 vertices and 12 edges. Draw the graph and write the input file for it.
# A text file containing the graphical representation,
# the input file for a small graph (6 vertices, 9 edges) and the results: all the minimum spanning trees (drawn) and their cost.

from graph.graph import Graph

graph = Graph("input_graph.txt")


# finds the parent of the set a node is included
def find_parent(parent, v):
    if parent[v] == v:
        return v
    return find_parent(parent, parent[v])


# does the union of two sets
def union(parent, x, y):
    rootx = find_parent(parent, x)
    rooty = find_parent(parent, y)
    parent[rootx] = rooty


def find_min_cost_tree_kruskal():
    sorted_edges = sorted(graph.get_all_edges().items(), key=lambda x: x[1], reverse=False)
    print("Sorted edges:")
    for edge in sorted_edges:
        print(edge)

    result = []

    parent = graph.get_all_vertices()  # parents of each vertex

    edge_index = 0  # the index of the current edge
    nr_edges_used = 0  # counts the current number of edges used

    while nr_edges_used < len(parent) - 1:
        x = sorted_edges[edge_index][0][0]
        y = sorted_edges[edge_index][0][1]
        cost = sorted_edges[edge_index][1]

        rootx = find_parent(parent, x)
        rooty = find_parent(parent, y)

        if rootx != rooty:
            nr_edges_used += 1
            result.append([x, y, cost])
            union(parent, rootx, rooty)
        edge_index += 1

    print("Edges of the Min Spanning Tree:\n ", result)


find_min_cost_tree_kruskal()
