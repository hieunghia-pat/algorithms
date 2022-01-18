#include <iostream>
#include <vector>
#include <string>
#include <iterator>

std::vector<std::vector<std::uint64_t>> findLongestSequence(std::string const& x, std::string const& y)
{
    std::vector<std::vector<std::uint64_t>> states(x.size()+1, std::vector<std::uint64_t>(y.size()+1, 0));
    for (std::size_t i = 1; i <= x.size(); i++)
        for (std::size_t j = 1; j <= y.size(); j++)
        {
            if (x[i-1] == y[j-1])
                states[i][j] = states[i-1][j-1] + 1;
            else
                states[i][j] = std::max(states[i-1][j], states[i][j-1]);
        }

    return states;
}

int main()
{
    std::string x;
    std::string y;

    std::cin >> x;
    std::cin.ignore(1);
    std::cin >> y;

    std::size_t m = x.size();
    std::size_t n = y.size();

    std::vector<std::vector<std::uint64_t>> states = findLongestSequence(x, y);

    // trace back to find the longest common sequence
    std::string common_seq = "";
    std::size_t i = x.size();
    std::size_t j = y.size();
    while ((i > 0) && (j > 0))
    {
        if (states[i][j] == states[i-1][j-1] + 1)
        {
            common_seq = x[i-1] + common_seq;
            i = i-1;
            j = j-1;
            continue;
        }

        if (states[i][j] == states[i-1][j])
        {
            i = i-1;
            continue;
        }

        if (states[i][j] == states[i][j-1])
        {
            j = j-1;
            continue;
        }
    }

    std::cout << common_seq << std::endl;

    return 0;
}