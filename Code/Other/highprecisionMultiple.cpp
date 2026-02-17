#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    string multiply(string num1, string num2)
    {
        int n, m;
        n = num1.size();
        m = num2.size();

        if (num1 == "0" || num2 == "0")
            return "0";

        vector<int> res(n + m, 0);
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = m - 1; j >= 0; j--)
            {
                int pos = i + j + 1;
                int sum = (num1[i] - '0') * (num2[j] - '0') + res[pos];
                res[pos] = sum % 10;
                res[pos - 1] += sum / 10;
            }
        }

        string result;
        bool zero = true;
        for (int i:res)
        {
            if(i==0&&zero)
                continue;
            zero = false;
            result += to_string(i);
        }

        return result.empty()?"0":result;
    }
};
