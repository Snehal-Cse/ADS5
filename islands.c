#include <iostream>
#include <vector>

using namespace std;

class DisjointSets {
private:
    vector<int> parent;
public:
    DisjointSets(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void merge(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
            parent[rootX] = rootY;
    }
};

int countIslands(vector<vector<int>>& grid) {
    if (grid.empty() || grid[0].empty())
        return 0;

    int rows = grid.size();
    int cols = grid[0].size();
    DisjointSets ds(rows * cols + 1);
    int numIslands = 0;
    int numZeros = 0;

    // Connect adjacent 1s
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 1) {
                ++numIslands;

                // Check all 8 directions
                if (i > 0 && grid[i - 1][j] == 1)
                    ds.merge(i * cols + j, (i - 1) * cols + j);
                if (i < rows - 1 && grid[i + 1][j] == 1)
                    ds.merge(i * cols + j, (i + 1) * cols + j);
                if (j > 0 && grid[i][j - 1] == 1)
                    ds.merge(i * cols + j, i * cols + j - 1);
                if (j < cols - 1 && grid[i][j + 1] == 1)
                    ds.merge(i * cols + j, i * cols + j + 1);
                if (i > 0 && j > 0 && grid[i - 1][j - 1] == 1)
                    ds.merge(i * cols + j, (i - 1) * cols + j - 1);
                if (i > 0 && j < cols - 1 && grid[i - 1][j + 1] == 1)
                    ds.merge(i * cols + j, (i - 1) * cols + j + 1);
                if (i < rows - 1 && j > 0 && grid[i + 1][j - 1] == 1)
                    ds.merge(i * cols + j, (i + 1) * cols + j - 1);
                if (i < rows - 1 && j < cols - 1 && grid[i + 1][j + 1] == 1)
                    ds.merge(i * cols + j, (i + 1) * cols + j + 1);
            } else {
                ++numZeros;
            }
        }
    }

    // Subtract the number of zeros from the number of islands
    return numIslands - numZeros;
}

int main() {
    vector<vector<int>> grid = {
        {1, 1, 0, 0, 0},
        {0, 1, 0, 0, 1},
        {1, 0, 0, 1, 1},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 0, 1}
    };

    cout << "Number of islands: " << countIslands(grid) << endl;

    return 0;
}
