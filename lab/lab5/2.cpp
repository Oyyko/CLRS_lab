#include <iostream>
#include <string>

using namespace std;
// 时间复杂度O(mn),空间复杂度O(2 * min(m,n)) 求出LCS长度

int LCS_length(string X, string Y)
{
    if (X.size() > Y.size())
    {
        return LCS_length(Y, X);
    }
    int m = X.length(), n = Y.length();

    int curr[n + 1], prev[n + 1]; //仅需保留上一行的信息

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
            {
                curr[j] = 0;
            }
            else
            {
                if (X[i - 1] == Y[j - 1])
                {
                    curr[j] = prev[j - 1] + 1;
                }
                else
                {
                    curr[j] = max(curr[j], curr[j - 1]);
                }
            }
        }
        //更新prev数组，保存上一行信息
        for (int i = 0; i <= n; i++)
        {
            prev[i] = curr[i];
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