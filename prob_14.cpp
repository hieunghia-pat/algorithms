#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

int main()
{
    std::fstream file;
    file.open("prob_14.in", std::ios_base::in);

    std::size_t m, n;
    file >> m >> n;

    std::vector<std::vector<std::uint16_t>> map(m, std::vector<std::uint16_t>(n, false));
    for (auto& row: map)
        for (auto& column: row)
            file >> column;

    file.close();

    std::vector<std::vector<std::uint16_t>> table(m+1, std::vector<std::uint16_t>(n+1, 0));
    for (std::size_t x = 1; x <= m; x++)
        for (std::size_t y = 1; y <= n; y++)
            table[x][y] = map[x-1][y-1] + std::max(table[x][y-1], table[x-1][y]);

    file.open("prob_14.out", std::ios_base::out);
    file << "Total points: " << table[m][n] << std::endl;
    // trace back to find the path
    std::size_t x = m;
    std::size_t y = n;
    while (x > 0 && y > 0)
    {
        if (table[x][y] == map[x-1][y-1] + table[x][y-1])
        {
            file << "(" << x << ", " << y << ")" << "<-";
            y = y-1;
            continue;
        }

        if (table[x][y] == map[x-1][y-1] + table[x-1][y])
        {
            file << "(" << x << ", " << y << ")" << "<-";
            x = x-1;
            continue;
        }
    }
    file << "(" << 1 << ", " << 1 << ")";

    file.close();

    return 0;
}