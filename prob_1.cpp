#include <iostream>
using namespace std;

bool isPS(int c) {
	int k = sqrt(c);
	return k * k == c;
}

void checkallPS(int a[], int start, int end) {
	if (start == end) {
		if (isPS(a[start])) {
			cout << a[start] << " ";
			return;
		}
	}
	int mid = (start + end) / 2;
	checkallPS(a, start, mid);
	checkallPS(a, mid + 1, end);
}

int main() {
	int n; cin >> n;
	int *a = new int [n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	checkallPS(a, 1, n);
	return 0;
}