#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
public:
    vector<int> parent, rank;
    
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for(int i = 0; i < n; i++)
            parent[i] = i;
    }
    
    int findParent(int x) {
        if(parent[x] == x) return x;
        return parent[x] = findParent(parent[x]); // Path compression
    }
    
    void unionSet(int x, int y) {
        int px = findParent(x);
        int py = findParent(y);
        if(px == py) return;

        if(rank[px] > rank[py])
            parent[py] = px;
        else if(rank[px] < rank[py])
            parent[px] = py;
        else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

int countComponents(int n, vector<vector<int>>& edges) {
    DisjointSet ds(n);
    for(auto &e : edges)
        ds.unionSet(e[0], e[1]);

    unordered_set<int> components;
    for(int i = 0; i < n; i++)
        components.insert(ds.findParent(i));

    return components.size();
}

int main() {
    int n = 6; // nodes 0..5
    vector<vector<int>> edges = {
        {0, 1}, {1, 2}, {3, 4}
    };

    cout << "Number of Connected Components: "
         << countComponents(n, edges) << endl;

    return 0;
}
