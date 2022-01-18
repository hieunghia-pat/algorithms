#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

std::vector<std::vector<std::int64_t>> saved_states;

std::uint64_t min(std::uint64_t a, std::uint64_t b)
{
	return a < b ? a : b;
}

std::uint64_t matrixChainMemoised(std::vector<std::uint64_t> const& p, std::size_t i, std::size_t j)
{
	if (i == j)
	{
		return 0;
	}

	if (saved_states[i][j] != -1)
	{
		return saved_states[i][j];
	}

	saved_states[i][j] = std::numeric_limits<std::uint64_t>::max();
	for (int k = i; k < j; k++)
	{
		saved_states[i][j] = min(
                                saved_states[i][j], 
                                matrixChainMemoised(p, i, k) + matrixChainMemoised(p, k + 1, j) + p[i - 1] * p[k] * p[j]
                            );
	}

	return saved_states[i][j];
}

int MatrixChainOrder(std::vector<std::uint64_t> const& p, int n)
{
	int i = 1, j = n - 1;
	return matrixChainMemoised(p, i, j);
}

int main()
{
	std::size_t N = 0;
	std::cin >> N;
	std::vector<std::uint64_t> ps(N, 0);

	for (auto& p: ps)
		std::cin >> p;

	saved_states = std::vector<std::vector<std::int64_t>>(N, std::vector<std::int64_t>(N, -1));

	std::cout << "Minimum number of multiplication: " << MatrixChainOrder(ps, N) << std::endl;

    return 0;
}
