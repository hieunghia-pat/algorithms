#include <iostream>
using namespace std;

bool isPerfectSquare(int c) {
	int k = sqrt(c);
	if (int(k * k) == c) {
		return true;
	}
	else return false;
}

void checkPerfectSquares(int a[], int start, int end) {
	if (start == end) {
		if (isPerfectSquare(a[start])) {
			cout << a[start] << " ";
			return;
		}
	}
	else {
		int mid = (start + end) / 2;
		checkPerfectSquares(a, start, mid);
		checkPerfectSquares(a, mid + 1, end);
	}
}

int main() {
	int n; cin >> n;
	int *a = new int [n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	checkPerfectSquares(a, 0, n);
	return 0;
}
