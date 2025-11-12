#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>

using namespace std;

struct Item {
    string name;
    double weight;
    double value;
    bool divisible;
    int priority;
    Item(string n, double w, double v, bool d, int p)
        : name(move(n)), weight(w), value(v), divisible(d), priority(p) {}
    double valuePerWeight() const { return (weight > 0.0) ? (value / weight) : 0.0; }
};

double priorityStrictKnapsack(vector<Item>& items, double capacity, double& totalWeightCarried) {
    totalWeightCarried = 0.0;
    double totalValue = 0.0;

    for (int pri = 1; pri <= 3; ++pri) {
        vector<Item> group;
        for ( auto& it : items) if (it.priority == pri) group.push_back(it);

        if (group.empty()) continue;

        sort(group.begin(), group.end(), []( Item& a,  Item& b) {
            return a.valuePerWeight() > b.valuePerWeight();
        });

        cout << "\nProcessing priority " << pri << " items:\n";

        for ( auto& it : group) {
            if (it.weight <= 0.0 || it.value <= 0.0) {
                cout << "  Skipped (invalid item): " << it.name << "\n";
                continue;
            }
            if (!it.divisible && capacity > 0.0) {
                if (it.weight <= capacity) {
                    totalValue += it.value;
                    capacity -= it.weight;
                    totalWeightCarried += it.weight;
                    cout << "  Took (indiv): " << it.name << " (" << it.weight << " kg, value " << it.value << ")\n";
                } else {
                    cout << "  Skipped (indiv, no space): " << it.name << "\n";
                }
            }
        }

        // Then fill remaining with divisible items (fractional)
        for ( auto& it : group) {
            if (capacity <= 0.0) break;
            if (it.divisible) {
                if (it.weight <= 0.0 || it.value <= 0.0) {
                    cout << "  Skipped (invalid item): " << it.name << "\n";
                    continue;
                }
                double take = min(it.weight, capacity);
                double valTaken = it.valuePerWeight() * take;
                totalValue += valTaken;
                capacity -= take;
                totalWeightCarried += take;
                cout << "  Took (frac): " << it.name << " (" << take << " kg, value " << fixed << setprecision(2) << valTaken << ")\n";
            }
        }
    }
    return totalValue;
}

int main() {
    int n;
    cout << "Enter number of relief items: ";
    cin>>n;
    // if (!(cin >> n) || n <= 0) { cerr << "Invalid number.\n"; return 1; }

    vector<Item> items;
    for (int i = 0; i < n; ++i) {
        string name;
        double weight = 0.0, value = 0.0;
        int divisibleInt = 0, priority = 3;

        cout << "\nItem #" << (i + 1) << ":\n";
        cout << "Name: ";
        getline(cin >> ws, name); 
        cout << "Weight (kg): ";
        cin >> weight;
        cout << "Utility value: ";
        cin >> value;
        cout << "Is it divisible? (1 = yes, 0 = no): ";
        cin >> divisibleInt;
        cout << "Priority (1 = High, 2 = Medium, 3 = Low): ";
        cin >> priority;

        items.emplace_back(name, weight, value, divisibleInt == 1, priority);
    }

    double capacity;
    cout << "\nEnter maximum weight capacity of the boat (kg): ";
    cin >> capacity;

    double carriedWeight = 0.0;
    double totalUtility = priorityStrictKnapsack(items, capacity, carriedWeight);

    cout << "\n===== Final Report (Strict Priority) =====\n";
    cout << "Total weight carried: " << fixed << setprecision(2) << carriedWeight << " kg\n";
    cout << "Total utility value: " << fixed << setprecision(2) << totalUtility << " units\n";

    return 0;
}
