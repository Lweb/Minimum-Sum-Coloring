#include <bits/stdc++.h>

#define MAX_N 555 // maximum number of vertecies

std::vector<int> G[MAX_N]; //input graph stored in an adjacency list, G[u] stores the neighbors of vertex u
std::bitset<MAX_N> bG[MAX_N]; //input graph stored in an adjacency matrix with bitset in order to speed something up 
bool table[MAX_N][MAX_N]; //input graph stored in an adjaceny matrix in a 2-dim bool array
int N; //number of vertices
int M; //number of edges

std::vector<int> X, Y;// the bipartite subgraph is formed as <X, Y>
std::vector<int> bestX, bestY;

int NX[MAX_N], NY[MAX_N]; // if NX[u] > 0, then u is in the neighbor of set X so as NY
bool inX[MAX_N], inY[MAX_N], del[MAX_N];// inX[u] equals true means u belongs to X so as inY. del[u] equals true means u is deleted.

int ans; // current required size of maximum bipartite subgraph
time_t start, end;

int alpha; // the size of maximum independent set

std::vector <int> vexNX, vexNY, vexREST;// seperately denote the neighbor of X, the neighbor of Y, and the set of REST
std::bitset<MAX_N> biNX, biNY, biREST;
std::bitset<MAX_N> biNXREST, biNYREST, biTot;

std::bitset<MAX_N> SS, TT;

inline bool isSubset(std::bitset<MAX_N> &S, std::bitset<MAX_N> &T) { // check wether S is the subset of T
    if ((S & T) == S) return true;
    else return false;
}

inline void insertX(int u) { //insert u into X
	for (auto v : G[u])
		++ NX[v];
	inX[u] = 1;
	X.push_back(u);
}

inline void insertY(int u) { //insert u into Y
	for (auto v : G[u])
		++ NY[v];
	inY[u] = 1;
	Y.push_back(u);
}

inline void deleteX(int u) { //delete u from X
	for (auto v : G[u])
		-- NX[v];
	inX[u] = 0;
	X.pop_back();
}

inline void deleteY(int u) { //delete u from Y
	for (auto v : G[u])
		-- NY[v];
	inY[u] = 0;
	Y.pop_back();
}

std::vector<int> tmp;

int dfsCnt;

inline int degree(int u) { //return the degree of vertex u in NX(NY) union REST
	if (NX[u]) return (bG[u] & biNXREST).count();
	if (NY[u]) return (bG[u] & biNYREST).count();
	return (bG[u] & biTot).count();
}

inline int degreeN(int u) { //return the degree of vertex u in NX(NY) 
	if (NY[u]) return (biNY & bG[u]).count();
	if (NX[u]) return (biNX & bG[u]).count();
}

inline int indep(std::vector <int> &vex) { //return an upper bound of the size of maximum independent set
    return vex.size();
    int ret = 0;
    for (auto u : vex)
        ret = std::max(ret, (int)vex.size() - degreeN(u));
    return ret;
}

inline int bipartite(std::vector <int> &vex) { //return an upper bound of the size of maximum bipartite subgraph
    return vex.size();
}

bool solveNX(int u); //branch a vertex in NX
bool solveNY(int u); //branch a vertex in NY
//bool checkREST(std::vector<int> &vex); 
//std::vector<int> BREST, WREST;

bool dfs() { //searching
    if (time(NULL) - start >= 3 * 3600) { //break out if exceeding the time bound of 3 hours
        printf("-1\n");
        fclose(stdin);
        fclose(stdout);
        exit(0);
    }
    ++ dfsCnt;
    //if (dfsCnt % 1000000 == 0) printf("%d\n", dfsCnt);
	if ((int)X.size() + (int)Y.size() > ans) { //if get a solution better than required size, then return true
        bestX.clear();
        bestY.clear();
        for (auto b : X) bestX.push_back(b);
        for (auto w : Y) bestY.push_back(w);
        return true;
    }
    vexNX.clear();
    vexNY.clear();
    vexREST.clear();
    biNX.reset();
    biNY.reset();
    biREST.reset();
	for (int i = 1; i <= N; i++) {
		if (inX[i] || inY[i] || del[i] || (NY[i] && NX[i]))
            continue;
        if (NX[i]) {
            vexNX.push_back(i);
            biNX.set(i);
        }
        else if (NY[i]) {
            vexNY.push_back(i);
            biNY.set(i);
        }
        else {
            vexREST.push_back(i);
            biREST.set(i);
        }
	}
    biNXREST = biNX | biREST;
    biNYREST = biNY | biREST;
    biTot = biNX | biNY | biREST;
    //if the upper bound estimated by the sum of X.size, Y.size, the upper bound of bipartite subgraph of REST
    //and the upper bound of independent set of NX and NY is smaller than required size, then it is impossible
    //to achieve the required size
	if ((int)X.size() + (int)Y.size() + bipartite(vexREST) + indep(vexNX) + indep(vexNY) <= ans) 
        return false;

    if (vexNX.empty() && vexNY.empty()) {
    	/*
        if (checkREST(vexREST)) {
            if ((int)X.size() + (int)Y.size() + (int)BREST.size() + (int)WREST.size() > ans) return true;
            else return false;
        }
        */

        int u = vexREST[rand() % vexREST.size()]; //pick a vertex with maximum degree in REST
        int w = vexREST[rand() % vexREST.size()]; //pick a vertex with minimum degree in REST
        int du = degree(u); //the degree of vertex u
        int dw = degree(w); //the degree of vertex w
        for (auto v : vexREST) {
            int dv = degree(v);
            if (dv > du) {
                u = v; // 
                du = dv;
            }
            if (dv < dw) {
                w = v;
                dw = dv;
            }
        }

        //reduction rule 2
        if(dw <= 1) {
            insertX(w);
            bool ret = dfs();
            deleteX(w);
            return ret;
        }

        //branching rule 1
        insertX(u);
        bool ret = dfs();
        deleteX(u);
        if (ret) return true;

        del[u] = true;
        ret = dfs();
        del[u] = false;
        return ret;
    }
    //choose a vertex from NX or NY randomly to branch
    if (vexNY.empty() || (vexNX.size() && (rand() & 1))) {
        int u = vexNX[rand() % vexNX.size()];
        for (auto v : vexNX)
            if (degree(v) > degree(u))
                u = v;
        return solveNX(u);
    } else {
        int u = vexNY[rand() % vexNY.size()];
        for (auto v : vexNY)
            if (degree(v) > degree(u))
                u = v;
        return solveNY(u);
    }
}

bool solveNX(int u) {
    tmp.clear();
    for (auto v : G[u])
        if (!del[v] && NY[v] == 0 && inX[v] == 0 && inY[v] == 0) {
            tmp.push_back(v);
            if (tmp.size() == 3) break;
        }
    //reduction rule 3
    if (tmp.size() <= 1) {
        insertY(u);
        bool ret = dfs();
        deleteY(u);
        return ret;
    }
    if (tmp.size() == 2) {
        int u1 = tmp[0], u2 = tmp[1];
        insertY(u);
        bool ret = dfs();
        deleteY(u);

        //reduction rule 4
        if (table[u1][u2]) return ret;
        if (ret) return true;

        //branching rule 2
        insertY(u1);
        insertY(u2);
        del[u] = true;
        ret = dfs();
        deleteY(u1);
        deleteY(u2);
        del[u] = false;
        return ret;
    }
    //branching rule 3
    insertY(u);
    bool ret = dfs();
    deleteY(u);
    if (ret) return true;
    del[u] = true;
    ret = dfs();
    del[u] = false;
    return ret;
}

//symmetrical to NX
bool solveNY(int u) {
    tmp.clear();
    for (auto v : G[u])
        if (!del[v] && NX[v] == 0 && inX[v] == 0 && inY[v] == 0) {
            tmp.push_back(v);
            if (tmp.size() == 3) break;
        }
    if (tmp.size() <= 1) {
        insertX(u);
        bool ret = dfs();
        deleteX(u);
        return ret;
    }
    if (tmp.size() == 2) {
        int u1 = tmp[0], u2 = tmp[1];
        insertX(u);
        bool ret = dfs();
        deleteX(u);

        if (table[u1][u2]) return ret;
        if (ret) return true;

        insertX(u1);
        insertX(u2);
        del[u] = true;
        ret = dfs();
        deleteX(u1);
        deleteX(u2);
        del[u] = false;
        return ret;
    }
    insertX(u);
    bool ret = dfs();
    deleteX(u);
    if (ret) return true;
    del[u] = true;
    ret = dfs();
    del[u] = false;
    return ret;
}
/*
bool checkREST(std::vector<int> &vex) {
    ++ nowInRestTime;
    BREST.clear();
    WREST.clear();
    while (queREST.size()) queREST.pop();

    for (auto u : vex) inRest[u] = nowInRestTime;
    for (auto u : vex) colorREST[u] = -1;

    for (auto u : vex)  
        if (colorREST[u] == -1)
            if (!bfs(u)) 
                return false;
    return true;
}
*/

std::pair <int, int> E[MAX_N * MAX_N / 2]; //all edges

void readData() {
    char s[100];
	scanf("%s%s%d%d", s, s, &N, &M);
	for (int i = 0; i < M; ++ i)
        scanf("%s%d%d", s, &E[i].first, &E[i].second);
}

//first argument should be the input file containing the size of maximum independent set of the corresponding graph
//second argument should be the input file of the graph in DIMACS format
//third argument should be the output file
int main(int argc, char *argv[]) {
    freopen(argv[1], "r", stdin);
    scanf("%d", &alpha);
    fclose(stdin);

    freopen(argv[2], "r", stdin);
    freopen(argv[3], "w", stdout);

    srand(time(0));
    readData();
	start = time(NULL);

    for (int i = 0; i < M; ++ i) {
        int u = E[i].first, v = E[i].second;
        G[u].push_back(v);
        G[v].push_back(u);
        bG[u].set(v);
        bG[v].set(u);
        table[u][v] = table[v][u] = true;
    }
    //binary search
	int low = 1, high = alpha * 2;
	while (low <= high) {
        int m = (low + high) >> 1;
        ans = m - 1;
        if (dfs()) {
            low = m + 1;
        } else {
            high = m - 1;
        }
	}
	end = time(NULL);
    printf("%d\n", bestX.size());
    for (auto b : bestX) 
        printf("%d ", b);
    printf("\n");
    printf("%d\n", bestY.size());
    for (auto w : bestY)
        printf("%d ", w);
    printf("\n");
    printf("%d\n", (int)end - (int)start);

    fclose(stdin);
    fclose(stdout);

	return 0;
}
