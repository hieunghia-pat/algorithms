#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <limits>
#include <algorithm>
#include <utility>

typedef std::uint64_t weight_t;

struct TVertice 
{
    TVertice() {}
    TVertice(TVertice* vertice)
        : label {vertice->label}, adjacent_vertices { vertice->adjacent_vertices }, distance { vertice->distance }
    {}

    TVertice(TVertice& vertice)
        : label {vertice.label}, adjacent_vertices { vertice.adjacent_vertices }, distance { vertice.distance }
    {}

    TVertice(TVertice&& vertice)
        : label {vertice.label}, adjacent_vertices { vertice.adjacent_vertices }, distance { vertice.distance }
    {}

    std::uint64_t label = 0;
    std::vector<std::pair<std::shared_ptr<TVertice>, weight_t>> adjacent_vertices;
    std::uint64_t distance = std::numeric_limits<std::uint64_t>::max(); // distance to the spanning tree T
};

std::pair<std::vector<std::uint64_t>, weight_t> construct_spanning_tree_using_Prim( std::vector<std::shared_ptr<TVertice>>& vertices, 
                                            std::vector<bool>& free)
{
    std::size_t n_vertices = free.size();
    std::vector<std::uint64_t> trace(n_vertices+1, 0); // node 0 is undefined
    weight_t total_weight = 0;
    for (auto& vertice: vertices)
    {
        std::shared_ptr<TVertice> u = std::make_shared<TVertice>(std::min_element(
                                                        vertices.begin(), 
                                                        vertices.end(), 
                                                        [&](std::shared_ptr<TVertice> const& v, std::shared_ptr<TVertice> const& smallest) {
                                                            return free[v->label] && v->distance < smallest->distance;
                                                        })->get());               
        if (u->label == 0)
            return std::make_pair(trace, total_weight); // the graph is not connected
        free[u->label] = false;
        for (auto& adjacent_vertice: u->adjacent_vertices)
        {
            if (adjacent_vertice.first->distance > adjacent_vertice.second) // adjacent_vertice.weight == c[u, v]
            {
                adjacent_vertice.first->distance = adjacent_vertice.second;
                trace[adjacent_vertice.first->label] = u->label;
                total_weight += adjacent_vertice.second;
            }
        }
    }

    return std::make_pair(trace, total_weight);
}

int main()
{
    std::size_t n_vertices = 0;
    std::size_t n_edges = 0;

    std::fstream file;
    file.open("prob_6_prim.in", std::ios_base::in);
    file >> n_vertices >> n_edges;

    std::vector<std::shared_ptr<TVertice>> vertices(n_vertices+1);
    for (std::size_t ith = 0; ith <= n_vertices; ith++)
    {
        vertices[ith] = std::make_shared<TVertice>();
        vertices[ith]->label = ith;
    }
    for (std::size_t ith = 1; ith <= n_edges; ith++)
    {
        std::uint64_t u, v, weight;
        file >> u >> v >> weight;
        vertices[u]->adjacent_vertices.push_back({ vertices[v], weight });
        
        vertices[v]->adjacent_vertices.push_back({ vertices[u], weight });
    }
    
    file.close();

    std::vector<bool> free(n_vertices+1, true); // there is no vertice added to the spanning tree
    vertices[1]->distance = 0; // added 1 as the first node of the spanning tree

    std::vector<std::uint64_t> trace;
    weight_t weight;
    std::tie<std::vector<std::uint64_t>, weight_t>(trace, weight) = construct_spanning_tree_using_Prim(vertices, free);
    file.open("prob_6_prim.out", std::ios_base::out);
    if (weight > 0)
    {
        for (size_t ith = 1; ith <= n_vertices; ith++)
        {
            if (trace[ith] != 0)
                file << "(" << trace[ith] << ", " << ith << ")" << std::endl;
        }
        file << "Minimum weight: " << weight;
        file.close();
    }
    else
        std::cout << "Graph is not connected" << std::endl;

    return 0;
}