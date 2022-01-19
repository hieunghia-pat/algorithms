#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <limits>

std::vector<std::vector<std::uint64_t>> Floyd(std::vector<std::vector<std::uint64_t>>& weight_matrix)
{
    std::size_t n_vertices = weight_matrix.size()-1;
    std::vector<std::vector<std::uint64_t>> trace(n_vertices+1, std::vector<std::uint64_t>(n_vertices+1, 0));

    for (std::uint64_t u = 1; u <= n_vertices; u++)
        for (std::uint64_t v = 1; v <= n_vertices; v++)
            trace[u][v] = v;
    
    for (std::uint64_t k = 1; k <= n_vertices; k++)
        for (std::uint64_t u = 1; u <= n_vertices; u++)
            for (std::uint64_t v = 1; v <= n_vertices; v++)
                if (weight_matrix[u][v] > weight_matrix[u][k] + weight_matrix[k][v])
                {
                    weight_matrix[u][v] = weight_matrix[u][k] + weight_matrix[k][v];
                    trace[u][v] = trace[u][k];
                }

    return trace;
}

int main()
{
    std::size_t n_edges = 0;
    std::size_t n_vertices = 0;
    
    std::fstream file;
    file.open("prob_12.in", std::ios_base::in);
    file >> n_vertices >> n_edges;

    std::uint64_t s, f;
    file >> s >> f;

    std::vector<std::vector<std::uint64_t>> weight_matrix(n_vertices+1, std::vector<std::uint64_t>(n_vertices+1, std::numeric_limits<std::int64_t>::max()));
    for (std::uint64_t u = 0; u <= n_vertices; u++)
        weight_matrix[u][u] = 0;
    for (std::size_t ith = 0; ith < n_edges; ith++)
    {
        std::uint64_t u, v;
        file >> u >> v >> weight_matrix[u][v];
    }

    file.close();

    file.open("prob_12.out", std::ios_base::out);
    std::vector<std::vector<std::uint64_t>> trace = Floyd(weight_matrix);

    file << "Distance from " << s << " to " << f << ": " << weight_matrix[s][f] << std::endl;

    if (weight_matrix[s][f] == std::numeric_limits<std::uint64_t>::max())
        std::cout << "There is no path from " << s << " to " << f << std::endl;
    else
        do {
            file << s << "->";
            s = trace[s][f];
        } while (s != f);
    file << f;
 
    file.close();

    return 0;
}