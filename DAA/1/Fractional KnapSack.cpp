#include <bits/stdc++.h>
using namespace std;
struct item
{
    double profit;
    double weight;
    int index;
    bool operator>(item &other)
    {
        return (this->profit / this->weight) > (other.profit / other.weight);
    }
};

void swap(item &x, item &y)
{
    item tmp = x;
    x.index = y.index;
    x.weight = y.weight;
    x.profit = y.profit;

    y.index = tmp.index;
    y.profit = tmp.profit;
    y.weight = tmp.weight;
}

int partition(vector<item> &arr, int low, int high)
{
    item pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] > pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort(vector<item> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}
void solve(std::vector<item> &store, int n, int cap)
{
}

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
        store[i].index = i;
    }
    std::cout << "Using Greedy Technique\n";

    quicksort(store, 0, n - 1);
    cout << "Initial store capacities :\n";
    for (int i = 0; i < n; i++)
    {
        cout << store[i].index << ' ' << store[i].profit << " " << store[i].weight << "\n";
    }
    vector<double> takenFraction(n, 0);
    double profitGain = 0;
    for (int i = 0; i < n; i++)
    {
        bool flag = false;
        if (store[i].weight <= cap)
        {
            takenFraction[store[i].index] = 1;
            cap -= store[i].weight;
            profitGain += store[i].profit;
        }
        else
        {
            profitGain += (cap / store[i].weight) * store[i].profit;
            takenFraction[store[i].index] = (cap / store[i].weight);
            cap = 0;
            flag = true;
        }

        cout << "detail of Fractions of taken items after " << i + 1 << "th iteration\n";
        for (int i = 0; i < n; i++)
        {
            cout << takenFraction[i] << ' ';
        }
        cout << '\n';
        cout << "Current Capacity :" << cap << "\n";

        if (flag)
        {
            break;
        }
    }

    std::cout << "Total Profit Gain :" << profitGain << endl;
    if (cap != 0)
    {
        std::cout << "!!! your bag can still accomodate items...\n";
    }

    return 0;
}
