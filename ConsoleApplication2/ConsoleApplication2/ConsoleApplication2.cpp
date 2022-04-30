#include <iostream>
#include <vector>
#include <clocale>
using namespace std;

int Mod(int b, int m)
{
	int q, r;
	if (b > 0)
	{
		q = (int)b / m;
		r = b - q * m;
	}
	else
	{
		b = abs(b);
		q = b / m;
		r = abs(b) - q * m;
		if (r != 0)
			r = m - r;
	}
	return r;
}

int AlgoritmEvklida(int a, int m)
{
	int znak, m1 = m;
	znak = (a < 0) ? -1 : 1;
	a = abs(a);
	int y0 = 0, y1 = 1, q, r, buf, x0;
	q = m / a;
	r = m - q * a;
	while (r != 0)
	{
		m = a;
		a = r;
		buf = y0 - q * y1;
		y0 = y1;
		y1 = buf;
		q = m / a;
		r = m - q * a;
	}
	x0 = znak * y1;
	r = Mod(x0, m1);
	return r;
}

int S(vector <int>& a, vector <int>& koff, int L, int r)
{
	int j, s = 0;
	for (j = 0; j <= L; j++)
	{
		s += koff[j] * a[r - j - 1];
	}
	return s;
}

void b(vector <int>& kofb, vector <int>& kofv1, int n, int& c, int h)
{
	for (int i = 0; i <= n; i++)//степень должна быть <=n
	{
		kofv1[i] = kofb[i];
	}
	for (int i = 1; i <= n; i++)//степень должна быть <=n
	{
		kofb[i] = Mod(kofv1[i - 1], h);
	}
	kofb[0] = 0;
}

void v(vector <int>& kofv, vector <int>& kofb, int n, int d, int& k)
{
	for (int i = 0; i < n; i++)
	{
		kofv[i + 1] = kofb[i] * d;
	}
	kofv[0] = 0;
}

void buf(vector <int>& kofbuf, vector <int>& kofv, vector <int>& kofv2, int n, int h)
{
	for (int i = 0; i <= n; i++)
	{
		if (kofv[i] != 0)
			kofbuf[i] = Mod(kofv2[i] - kofv[i], h);
		else
			kofbuf[i] = Mod(kofv2[i], h);
	}
}

void F(vector <int>& kofbuf, vector <int>& koff, int n, int h)
{
	for (int i = 0; i <= n; i++)
	{
		koff[i] = Mod(kofbuf[i], h);
	}
}

void F1(vector <int>& kofb, vector <int>& koff, int n, int h)
{
	for (int i = 0; i <= n; i++)
	{
		kofb[i] = Mod(koff[i], h);
	}
}

void v1(vector <int>& kofv1, vector <int>& koff, int l, int n, int h)
{
	for (int i = 0; i <= n; i++)
	{
		kofv1[i] = koff[i] * l;
	}
}

void f1(vector <int>& koff, int obr, int n, int h, int& count)
{
	for (int i = 0; i <= n; i++)
	{
		koff[i] = Mod(obr * koff[i], h);
		count++;
		/*cout << clock() / 1000.0 << " " << count << endl;*/
	}
}

void LinCombination(vector <int>& a, vector <int>& f1, int n, int h)
{
	int k, i, c = n - 1, in = n;
	while (in < 2 * n) {
		k = c;
		a[in] = 0;
		for (i = 0; i < n; i++, k--)
		{
			a[in] += f1[i] * a[k];
		}
		a[in] = Mod((-1) * a[in], h);
		in++;
		c++;
	}
}

int main()
{
	setlocale(0, "Russian");
	int r = 0, L = 0, n, h = 2, A;
	int d, s = 0, j = 1, obr, l = 1, count = 0;
	cout << "Введите n: ";
	cin >> n;
	int c = n, k = n;
	vector <int> a(2 * n + 1);
	vector <int> f(n + 1);
	vector <int> kofb(n + 1, 0);
	vector <int> koff(n + 1, 0);
	vector <int> kofv(n + 1, 0);
	vector <int> kofv1(n + 1, 0);
	vector <int> kofv2(n + 1, 0);
	vector <int> kofbuf(n + 1, 0);
	cout << "Введите a1,...,an: " << endl;
	srand(time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = 0 + rand() % (h - 0 + 1);;
	}
	cout << "Введите f1,...,fn: " << endl;
	for (int i = 0; i < n; i++)
	{

		f[i] = Mod(0 + rand() % (h - 0 + 1), h);
	}
	LinCombination(a, f, n, h);
	kofb[0] = 1;
	koff[0] = 1;
	unsigned int start_time = clock();
	for (int r = 1; r <= 2 * n; r++)
	{
		d = Mod(S(a, koff, L, r), h);
		if (d == 0)
		{
			b(kofb, kofv1, n, c, h);
		}
		else if (d != 0)
		{
			v(kofv, kofb, n, d, k);
			v1(kofv2, koff, l, n, h);
			buf(kofbuf, kofv, kofv2, n, h);
			if (2 * L < r)
			{
				F1(kofb, koff, n, h);
				F(kofbuf, koff, n, h);
				L = r - L;
				l = d;
			}
			else if (2 * L >= r)
			{
				F(kofbuf, koff, n, h);
				b(kofb, kofv1, n, c, h);
			}
		}
	}
	obr = AlgoritmEvklida(koff[0], h);
	f1(koff, obr, n, h, count);
	cout << endl << "Решение системы: " << endl;
	for (int i = 1; i <= L; i++)
	{
		cout << "f" << i << " = " << koff[i] << endl;
	}
	cout << endl << "L=" << L;
	cout << endl << "n = " << n << " count = " << count << " time = " << clock() / 1000.0 << endl; // время работы программы 
	unsigned int end_time = clock(); // конечное время
	unsigned int search_time = end_time - start_time;
	cout << "runtime = " << search_time / 1000.0 << endl;
	return 0;
}
