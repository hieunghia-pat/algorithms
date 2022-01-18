#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <limits>
#include <algorithm>

typedef std::int64_t TVertice;

struct TEdge {
    TVertice u, v; // the two vertices of the edge
    std::uint64_t weight = 0;
    bool marked = false;
};

TVertice get_root(TVertice v, std::vector<TVertice> const& parent_labels)
{
    while (parent_labels[v] >= 0)
        v = parent_labels[v];
    return v;
}

void merge_trees(TVertice const& u, TVertice const& v, std::vector<TVertice>& parent_labels) // merge the tree of root u with the tree of root v
{
    std::int64_t total_nodes = parent_labels[u] + parent_labels[v];
    if (abs(parent_labels[u]) > abs(parent_labels[v])) // the tree of root u have more nodes than the tree of root v
    {
        parent_labels[u] = v;
        parent_labels[v] = total_nodes;
    }
    else { // the tree of root u have more nodes than the tree of root v
        parent_labels[v] = u;
        parent_labels[u] = total_nodes;
    }
}

std::uint64_t construct_spanning_tree_using_Kruskal(std::vector<TEdge>& edges, std::vector<TVertice>& parent_labels) // return whether the current graph is fully connected or not
{
    std::sort(edges.begin(), edges.end(), [](TEdge const& u, TEdge const& v) {
        return u.weight < v.weight;
    });

    std::size_t total_vertices = parent_labels.size();
    std::size_t total_edges = 0; // initialize spanning tree T has no edge
    std::uint64_t total_weights = 0;

    for (auto& edge: edges)
    {
        if (get_root(edge.u, parent_labels) != get_root(edge.v, parent_labels)) // this edge connecting two different trees
        {
            edge.marked = true; // added this edge to the spanning tree T
            total_edges += 1;
            total_weights += edge.weight;
            if (total_edges == total_vertices - 1) // added n-1 edges to the spanning tree T
                return total_weights;
            merge_trees(edge.u, edge.v, parent_labels);
        }
    }

    return 0;
}

int main()
{
    std::size_t n_vertices = 0;
    std::size_t n_edges = 0;

    std::fstream file;
    file.open("prob_6_kruskal.in", std::ios_base::in);
    file >> n_vertices >> n_edges;

    std::vector<TEdge> edges(n_edges);
    for (auto& edge: edges)
    {
        file >> edge.u >> edge.v >> edge.weight;
        edge.u--;
        edge.v--;
    }
    
    file.close();
    
    std::vector<TVertice> parent_labels(n_vertices, -1); // -1 means (1) each node is a tree and (2) the node is a root itself
    std::uint64_t weight = construct_spanning_tree_using_Kruskal(edges, parent_labels);
    if (weight > 0)
    {
        file.open("prob_6_kruskal.out", std::ios_base::out);
        for (auto const& edge: edges)
            if (edge.marked)
                file << "(" << edge.u+1 << ", " << edge.v+1 << ")" << " = " << edge.weight << std::endl;
        
        file << "Mininum weight: " << weight;
        file.close();
    }
    else
        std::cout << "Graph is not connected" << std::endl;

    return 0;
}