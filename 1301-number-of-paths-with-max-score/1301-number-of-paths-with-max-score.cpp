class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
          const int MOD = 1e9 + 7;
        int n = board.size();

        vector<vector<int>> dp(n, vector<int>(n, -1));
        vector<vector<int>> ways(n, vector<int>(n, 0));

        dp[0][0] = 0;
        ways[0][0] = 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board[i][j] == 'X') continue;
                if (i == 0 && j == 0) continue;

                int best = -1;
                long long cnt = 0;

                vector<pair<int, int>> prev = {
                    {i - 1, j},
                    {i, j - 1},
                    {i - 1, j - 1}
                };

                for (auto [x, y] : prev) {
                    if (x >= 0 && y >= 0 && ways[x][y] > 0) {
                        if (dp[x][y] > best) {
                            best = dp[x][y];
                            cnt = ways[x][y];
                        } else if (dp[x][y] == best) {
                            cnt = (cnt + ways[x][y]) % MOD;
                        }
                    }
                }

                if (best == -1) continue;

                int val = 0;
                if (board[i][j] >= '1' && board[i][j] <= '9')
                    val = board[i][j] - '0';

                dp[i][j] = best + val;
                ways[i][j] = cnt % MOD;
            }
        }

        if (ways[n - 1][n - 1] == 0) return {0, 0};
        return {dp[n - 1][n - 1], ways[n - 1][n - 1]};
    }
};