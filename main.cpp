#include <iostream>
#include <vector>
#include <climits>

using TLl = long long;
static const TLl INFINITY = INT_MAX;
static const int NONE = -2;

void solve(const std::vector<std::vector<TLl> >& matrix, int n, int m) {
    std::vector<std::vector<std::pair<TLl, int> > > memo(n, std::vector<std::pair<TLl, int> >(m, std::make_pair(INFINITY, NONE)));
    for (int j = 0; j < m; ++j) {
        memo[0][j] = std::make_pair(matrix[0][j], NONE);
    }

    int directFrom[3] = {-1, 0, 1};
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int d = 0; d < 3; ++d) {
                if (j + directFrom[d] < 0 || j + directFrom[d] >= m) {
                    continue;
                }
                if (memo[i-1][j+directFrom[d]].first + matrix[i][j] < memo[i][j].first) {
                    memo[i][j] = std::make_pair(memo[i-1][j+directFrom[d]].first + matrix[i][j], directFrom[d]);
                }
            }
        }
    }

    TLl minPathVal = INFINITY;
    int minPathValIdx = NONE;
    for (int j = 0; j < m; ++j) {
        if (memo[n-1][j].first < minPathVal) {
            minPathVal = memo[n-1][j].first;
            minPathValIdx = j;
        }
    }

    std::vector<std::pair<int, int> > path;
    int parentDirect = memo[n-1][minPathValIdx].second;
    std::pair<int, int> currPos = std::make_pair(n-1, minPathValIdx);
    while (parentDirect != NONE) {
        path.push_back(currPos);
        parentDirect = memo[currPos.first][currPos.second].second;
        currPos.second += parentDirect;
        currPos.first--;
    }

    std::cout << minPathVal << "\n";
    for (int i = path.size() - 1; i >= 0; --i) {
        std::cout << "(" << path[i].first + 1 << "," << path[i].second + 1 << ") ";
    }
    std::cout << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0); 
    
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<TLl> > matrix(n, std::vector<TLl>(m, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> matrix[i][j];
        }
    }
    solve(matrix, n, m);
    return 0;
}