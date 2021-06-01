#include <iostream>
#include <string>

using namespace std;
// 时间复杂度O(mn),空间复杂度O(mn),求出LCS及其长度

void reverse(string &x) //反转字符串
{
    int i = 0;
    int j = x.size() - 1;
    while (i <= j)
    {
        swap(x[i], x[j]);
        i++;
        j--;
    }
}

string LCS(string s1, string s2)
{
    if (s1 == "" || s2 == "")
        return "";
    int m = s1.size() + 1;
    int n = s2.size() + 1;
    int lcs[m][n], i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            lcs[i][j] = 0; //初始化表格
    for (i = 1; i < m; i++)
        for (j = 1; j < n; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            else
                lcs[i][j] = max(lcs[i - 1][j], lcs[i][j - 1]);
        } //求解表格
    i = m - 2;
    j = n - 2;
    string ss = ""; //生成lcs串
    while (i != -1 && j != -1)
    {
        if (s1[i] == s2[j])
        {
            ss += s1[i];
            i--;
            j--;
        }
        else
        {
            if (lcs[i + 1][j + 1] == lcs[i][j])
            {
                i--;
                j--;
            }
            else
            {
                if (lcs[i][j + 1] >= lcs[i + 1][j])
                    i--;
                else
                    j--;
            }
        }
    }
    reverse(ss); //反转串
    return ss;
}

int main()
{
    string x, y;
    getline(cin, x);
    getline(cin, y);
    string lcs = LCS(x, y);
    if (lcs.size() == 0)
    {
        cout << 0;
        return 0;
    }
    cout << "LCS: \"" << lcs << "\", length: " << lcs.size();
}