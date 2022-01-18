#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

std::vector<std::uint16_t> states {20, 0};

std::ofstream filestream {"prob_7.out", std::ios_base::out};

const std::size_t SIZE = 8;

bool is_valid(std::uint16_t x, std::uint16_t y)
{
    for (std::uint16_t row = 1; row < x; row++)
        if(states[row] == y || abs(row-x) == abs(states[row] - y) )
            return false;
    return true;
}
 
void save_states()
{
    for(std::uint16_t ith = 1;ith <= SIZE; ith++)
        filestream << states[ith] << " ";
    filestream << std::endl;
}
 
void try_for(std::uint16_t row)
{
    for(std::uint16_t col = 1; col <= SIZE; col++)
    {
        if(is_valid(row, col)){
            states[row] = col;
            if(row == SIZE) 
                save_states();
            try_for(row+1);
        }
    }
}
 
int main()
{
    try_for(1);

    filestream.close();

    return 0;
}