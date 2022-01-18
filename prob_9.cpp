#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::int16_t> sequence {};
std::vector<bool> selected;
std::ofstream out_file;
std::vector<std::size_t> selected_ids;

void save_result(std::ofstream& file)
{
    for (std::size_t& idx: selected_ids)
        file << sequence[idx] << " ";
    file << std::endl;
}

void try_with_reserve_order(std::int16_t M, std::size_t start_idx, std::size_t size)
{
    for (std::size_t idx = start_idx; idx < size; idx++)
    {
        if ((M - sequence[idx] < 0) || (selected[idx]))
            continue;
        selected[idx] = true;
        selected_ids.push_back(idx);
        M -= sequence[idx];
        if (M == 0)
            save_result(out_file);
        try_with_reserve_order(M, idx+1, size);
        selected[idx] = false;
        selected_ids.pop_back();
        M += sequence[idx];
    }
}

void try_without_reserve_order(std::int16_t M, std::size_t size)
{
    for (std::size_t idx = 0; idx < size; idx++)
    {
        if ((M - sequence[idx] < 0) || (selected[idx]))
            continue;
        selected[idx] = true;
        selected_ids.push_back(idx);
        M -= sequence[idx];
        if (M == 0)
            save_result(out_file);
        try_without_reserve_order(M, size);
        selected[idx] = false;
        selected_ids.pop_back();
        M += sequence[idx];
    }
}

int main()
{
    std::size_t size = 0;
    std::cin >> size;

    std::int16_t M = 0;
    std::cin >> M;

    for (std::size_t ith = 0; ith < size; ith++)
    {
        std::int16_t value;
        std::cin >> value;
        sequence.push_back(value);
    }

    selected = std::vector<bool>(size, false);

    out_file.open("prob_9_without_reserve_order.out", std::ios_base::out);
    selected_ids = std::vector<std::size_t>();
    try_without_reserve_order(M, size);
    out_file.close();

    out_file.open("prob_9_with_reserve_order.out", std::ios_base::out);
    selected_ids = std::vector<std::size_t>();
    try_with_reserve_order(M, 0, size);
    out_file.close();

    return 0;
}