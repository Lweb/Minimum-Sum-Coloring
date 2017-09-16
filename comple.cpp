#include <cstdio>
#include <cstring>

#define MAX_N 1003

int G[MAX_N][MAX_N];
int N, M;
char s[10];
int main(int argc, char *argv[]) {
	freopen("input.txt", "w", stdout);
	freopen(argv[1], "r", stdin);
	scanf("%s%s%d%d", s, s, &N, &M);
	for (int i = 1; i <= M; i++) {
		int a, b;
		scanf("%s%d%d", s, &a, &b);
		G[a][b] = G[b][a] = 1;
	}
	int cnt = 0;
	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
			cnt += (G[i][j] == 0);
	printf("%d %d 1\n", N, cnt);
	for (int i = 1; i <= N; i++)
		for (int j = i + 1; j <= N; j++)
			if (!G[i][j])
				printf("%d %d\n", i, j);
	fclose(stdin);
	fclose(stdout);
	return 0;
}