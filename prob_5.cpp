//cau5
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

std::vector<std::vector<std::int64_t>> saved_states;

static void scheduleMatches(int N) {
	if (N <= 1)
		return;

	int totalMatches = N * (N - 1) / 2;
	int MAX_MATCHES_IN_DAY = N / 2;
	int days = 0;
	std::vector<std::uint64_t> a{};
	for (int i = 0; i < N - 1; i++)
		a.push_back(i+1);

	while (totalMatches != 0) {
		int j = 0;
		int num = MAX_MATCHES_IN_DAY;
		std::cout<<"\n Day " << (days + 1) << " Matches :";
		while (num != 0) {
			// Check if team j has played all the matches
			if (a[j] < N) {
				int matchnumber = N * (N - 1) / 2 - totalMatches + 1;
				std::cout<<"Match " <<matchnumber <<": " << "Team " <<(j + 1) << " Vs Team " << (a[j] + 1) << " ";
				a[j++] += 1;
				totalMatches--;
				num--;
			}
			else
				j++;
		}
		days++;
	}

	std::cout<<"\n Total Number of Days is " << days;
}
int main()
{
	int n;
	std::cin >> n;
	scheduleMatches(n);
	return 0;
}