#include <cstdio>
#include <cstring>
#include <algorithm>

#define MAX_N 100005

int beta;
int alpha;
int k;
int V;

int p[MAX_N];

int LB1() {
	int lamb = (V - k - alpha + 1) / (beta / 2 - 1);
	for (int x = 1; x <= V; ++ x) {
		if (x == 1) p[x] = alpha;
		else if (x <= lamb + 1) p[x] = beta / 2;
		else if (x == lamb + 2) p[x] = V - alpha - beta / 2 * lamb - k + lamb + 2;
		else if (x <= k) p[x] = 1;
		else p[x] = 0;
	}
	int S = 0;
	for (int i = 1; i <= k; i++) 
		S = S + i * p[i];
	return S;
}

int LB2() {
	int lamb;
	int res = (1 + V) * (V) / 2;
	for (p[1] = 1; p[1] <= alpha; p[1]++) {
		int kk = std::min(p[1], beta - p[1]);
		if (kk == 0) {
			lamb = V;
			for (int i = 2; i <= lamb; i++)
				p[i] = kk;
			for (int i = lamb + 1; i <= V; i++)
				p[i] = 0;
		}
		else if (V - p[1] - kk * (k - 2) >= 1) {
			lamb = (V - p[1]) / kk + 1;
			for (int i = 2; i <= lamb; i++)
				p[i] = kk;
			int sum = 0;
			for (int i = 1; i <= lamb; i++)
				sum += p[i];
			p[lamb + 1] = V - sum;
			for (int i = lamb + 2; i <= V; i++)
				p[i] = 0;
		}
		else {
			lamb = (V - p[1] - k + 1) / (kk - 1) + 1;
			for (int i = 2; i <= lamb; i++)
				p[i] = kk;
			p[lamb + 1] = V - p[1] - kk * (lamb - 1) - k + lamb + 1;
			for (int i = lamb + 2; i <= k; i++)
				p[i] = 1;
			for (int i = k + 1; i <= V; i++)
				p[i] = 0;
		}
		int S = 0;
		for (int i = 1; i <= V; i++)
			S = S + i * p[i];
		res = std::min(S, res);
	}
 	return res;
}

int LBMS() {
	int sum = 0, rem = V;
	for (int i = 1; i <= k; i++) {
		if (i * alpha + k - i <= V) sum += i * alpha, rem -= alpha;
		else sum += i * (rem - (k - i)), rem -= (rem - (k - i));
	}
	return sum;
}

int LBOK() {
	return (V - k) + k * (k + 1) / 2;
}

int main() {
	scanf("%d%d%d%d", &V, &alpha, &beta, &k);

	printf("%d %d %d %d\n", LBOK(), LBMS(), LB1(), LB2());
	return 0;
}