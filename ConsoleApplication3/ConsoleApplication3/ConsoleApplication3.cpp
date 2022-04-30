
#include <iostream>
#include <string>
#include <vector>
#include <numeric> 
#include <algorithm>
#include <time.h>
using namespace std;
int Sravnenie(int a, int m) {
	int y0 = 0, y1 = 1, q, r, buf, x0;
	int zn;
	if (a > 0) zn = 1;
	else zn = -1;
	a = abs(a);
	q = m / a;
	r = m - q * a;
	while (r != 0) {
		m = a;
		a = r;
		buf = y0 - q * y1;
		y0 = y1;
		y1 = buf;
		q = m / a;
		r = m - q * a;
	}
	x0 = zn * y1;
	return x0;
}
int BinAlgEuclid(int a, int b) {

	if (a == 0 && b == 0)
		return -1;
	a = abs(a);
	b = abs(b);
	int d = 1;
	if (a == 0 || b == 0)
		return a + b;
	while (!(a & 1) && !(b & 1)) {
		a = a >> 1;
		b = b >> 1;
		d = d * 2;
	}
	while (!(a & 1)) {
		a = a >> 1;
	}
	while (!(b & 1)) {
		b = b >> 1;
	}
	while (a != 0 && b != 0) {
		while (!(a & 1)) {
			a = a >> 1;
		}
		while (!(b & 1)) {
			b = b >> 1;
		}
		if (a >= b) a = (a - b) >> 1;
		else b = (b - a) >> 1;
	}
	return((a + b) * d);
}
int obratnoe(int a, int m) {
	int d, x0, k = 0;
	d = BinAlgEuclid(a, m); //находим нод 
	if (1 % d != 0) {
		return -1; //решений нет
	}
	x0 = Sravnenie(a, m);
	if (x0 > 0) x0 = x0 % m;
	else {
		int f = (x0 / m) * (-1) + 1;
		x0 = f * m + x0;
	}
	return x0;
}

int main() {
	setlocale(LC_ALL, "Russian");
	int m, n;
	cout << "Enter field: ";
	cin >> m;
	cout << "Enter the number of members of the sequence: ";
	cin >> n;
	int l = n - 1;
	int r = 0, L = 0, d = 0, k = 0, obr;
	vector<int> a(2 * n, 0);
	srand(time(NULL));
	m--;
	for (int i = 0; i < n; i++) {
		a[i] = 0 + rand() % (m - 0 + 1);
	}
	vector<int> f_answer(n, 0);
	for (int i = 0; i < n; i++) {
		f_answer[i] = 0 + rand() % (m - 0 + 1);
	}
	n = 2 * n;
	int g = 0;
	m++;
	for (int i = n / 2; i < n; i++) {
		for (int j = 0; j < n / 2; j++) {
			a[i] += a[l - j + g] * f_answer[j];
		}
		a[i] = ((a[i] % m) - m) % m;
		a[i] = -a[i];
		g++;
	}
	cout << "a" << endl;
	//for (int i = 0; i < n; i++) {
	//	cout << a[i] << " ";
	//}
	//cout << endl;
	//cout << "f_ans" << endl;
	//for (int i = 0; i <= l; i++) {
	//	cout << f_answer[i] << " ";
	//}
	cout << endl;
	vector<int> f(n, 0);
	vector<int> b(n, 0);
	vector<int> buf(n, 0);
	unsigned int start_time = clock();
	f[0] = b[0] = buf[0] = 1;
	for (r = 0; r < n; r++) {
		int k = 0;
		for (int i = 1; i < L + 1; i++)
			k += f[i] * a[r - i];
		d = (f[0] * a[r] + k) % m;

		if (d == 0) {
			for (int i = n - 1; i > 0; i--)
				b[i] = b[i - 1];
			b[0] = 0;
		}
		else {
			buf[0] = f[0];
			for (int i = 1; i < n; i++) {
				buf[i] = (f[i] - d * b[i - 1]) % m;
				if (buf[i] < 0) buf[i] += m;
			}

			if (2 * L < r + 1) {
				obr = obratnoe(d, m);
				for (int i = 0; i < n; i++) {
					b[i] = (obr * f[i]) % m;
					f[i] = buf[i];
					if (b[i] < 0) b[i] += m;
				}
				L = r - L + 1;
			}
			else {
				for (int i = n - 1; i > 0; i--) {
					b[i] = b[i - 1];
					f[i] = buf[i];
				}
				f[0] = buf[0];
				b[0] = 0;
			}
		}
	}
	cout << "f" << endl;
	int i = n - 1;
	while (f[i] == 0 && i >= 0) {
		i--;
	}
	for (; i > 0; i--) {
		cout << "f[" << i << "] = " << f[i] << endl;
	}
	unsigned int end_time = clock(); // конечное время
	unsigned int search_time = end_time - start_time;
	cout << "runtime = " << search_time / 1000.0 << endl;

}
