#include <iostream>
#include <string>

using namespace std;
// 时间复杂度O(mn),空间复杂度O( min(m,n) ) 求出LCS长度
int LCS_length(string X, string Y)
{
    int m = X.length(), n = Y.length();
    if (n >= m)
    {
        return LCS_length(Y, X);
    }

    int curr[n + 1], prev;

    for (int i = 0; i <= m; i++)
    {
        prev = curr[0];
        for (int j = 0; j <= n; j++)
        {
            //备份
            int backup = curr[j];

            if (i == 0 || j == 0)
            {
                curr[j] = 0;
            }
            else
            {
                if (X[i - 1] == Y[j - 1])
                {
                    curr[j] = prev + 1;
                }
                else
                {
                    curr[j] = max(curr[j], curr[j - 1]);
                }
            }
            //使用备份，维护prev的信息
            prev = backup;
        }
    }

    return curr[n];
}

int main()
{
    string x, y;
    getline(cin, x);
    getline(cin, y);
    cout << LCS_length(x, y);
}