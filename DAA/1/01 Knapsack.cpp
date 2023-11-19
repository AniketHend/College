#include <bits/stdc++.h>
using namespace std;

struct item
{
    double profit;
    double weight;
};

int main()
{
    // std::cout << "Enter number of items and capacity of the bag \n";
    int n, cap;
    std::cin >> n >> cap;
    std::vector<item> store(n);

    // std::cout << "Enter item details \n";
    for (int i = 0; i < n; i++)
    {
        // std::cout << "Enter profit and  weight of " << i + 1 << " item\n";
        std::cin >> store[i].profit >> store[i].weight;
    }

    vector<vector<int>> dp(n + 1, vector<int>(cap + 1, 0));
    vector<int> takenFraction(n, 0);
    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 0; j <= cap; j++)
        {
            if (j < store[i - 1].weight)
            {
                dp[i][j] = dp[i - 1][j];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j - store[i - 1].weight] + (int)store[i - 1].profit, dp[i - 1][j]);
            }
        }
    }

    int i = n;
    int k = cap;

    while (true)
    {
        if (dp[i][k] != dp[i - 1][k])
        {
            k = k - store[i - 1].weight;
            takenFraction[i - 1] = 1;
        }

        i = i - 1;
        if (k <= 0 || i == 0)
        {
            break;
        }
    }
    std::cout << "Total Profit Gain :" << dp[n][cap] << endl;

    for (int i = 0; i < n; i++)
    {
        cout << takenFraction[i] << ' ';
    }
    cout << "\n";
    return 0;
}
