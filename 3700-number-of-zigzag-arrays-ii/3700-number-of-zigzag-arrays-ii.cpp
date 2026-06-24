class Solution {
public:
    static const int MOD = 1e9 + 7;

    using Matrix = vector<vector<long long>>;

    Matrix multiply(const Matrix& A, const Matrix& B) {
        int n = A.size();
        Matrix C(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                if (A[i][k] == 0) continue;
                for (int j = 0; j < n; j++) {
                    C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
                }
            }
        }
        return C;
    }

    Matrix power(Matrix base, long long exp) {
        int n = base.size();
        Matrix res(n, vector<long long>(n, 0));

        for (int i = 0; i < n; i++) res[i][i] = 1;

        while (exp) {
            if (exp & 1) res = multiply(res, base);
            base = multiply(base, base);
            exp >>= 1;
        }
        return res;
    }

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;

        Matrix T(2 * m, vector<long long>(2 * m, 0));

        for (int x = 0; x < m; x++) {
            for (int y = x + 1; y < m; y++) {
                T[m + y][x] = 1;
            }
        }

        for (int x = 0; x < m; x++) {
            for (int y = 0; y < x; y++) {
                T[y][m + x] = 1;
            }
        }

        Matrix P = power(T, n - 1);

        vector<long long> init(2 * m, 1);

        long long ans = 0;

        for (int i = 0; i < 2 * m; i++) {
            long long ways = 0;
            for (int j = 0; j < 2 * m; j++) {
                ways = (ways + P[i][j] * init[j]) % MOD;
            }
            ans = (ans + ways) % MOD;
        }

        return (int)ans;
    }
};