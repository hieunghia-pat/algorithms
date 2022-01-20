#include <iostream>
using namespace std;

int sumCI(int a[], int temp[], int start, int mid, int end) {
	int countCI = 0;
	int i = start, k = start, j = mid;
	while (i <= mid - 1 && j <= end) {
		if (a[i] <= a[j]) {
			temp[k++] = a[i++];
		}
		else {
			temp[k++] = a[j++];
			countCI += (mid - i);
		}
	}
	while (i <= mid - 1)
		temp[k++] = a[i++];

	while (j <= end)
		temp[k++] = a[j++];

	for (i = start; i <= end; i++)
		a[i] = temp[i];

	return countCI;
}

int isCI(int a[], int temp[], int start, int end) {
	int mid, countCI = 0;
	if (end > start) {
		mid = (start + end) / 2;
		countCI += isCI(a, temp, start, mid);
		countCI += isCI(a, temp, mid + 1, end);
		countCI += sumCI(a, temp, start, mid + 1, end);
	}
	return countCI;
}

int merge(int a[], int size) {
	int *temp = new int [size];
	return isCI(a, temp, 0, size-1);
}


int main() {
	int n; cin >> n;
	int *a = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int ans = merge(a, n);
	cout << ans;
	return 0;
}