#include <iostream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct Order {
    string order_id;
    time_t timestamp;
};

// Generate random orders using rand()
void generate_sample_orders(vector<Order> &orders, int n) {
    tm base_time{};
    base_time.tm_year = 2025 - 1900;
    base_time.tm_mon = 5; // June
    base_time.tm_mday = 24;
    base_time.tm_hour = 12;
    time_t base = mktime(&base_time);

    orders.resize(n);
    for (int i = 0; i < n; i++) {
        int random_minutes = rand() % 100000; // up to ~70 days
        orders[i].timestamp = base + random_minutes * 60;
        orders[i].order_id = "ORD" + to_string(i + 1);
    }
}

// Merge function for merge sort
void merge(vector<Order> &orders, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Order> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = orders[left + i];
    for (int j = 0; j < n2; j++) R[j] = orders[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].timestamp <= R[j].timestamp)
            orders[k++] = L[i++];
        else
            orders[k++] = R[j++];
    }
    while (i < n1) orders[k++] = L[i++];
    while (j < n2) orders[k++] = R[j++];
}

// Merge sort
void merge_sort(vector<Order> &orders, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(orders, left, mid);
        merge_sort(orders, mid + 1, right);
        merge(orders, left, mid, right);
    }
}

// Print first n orders
void print_first_n_orders(vector<Order> &orders, int n) {
    for (int i = 0; i < n && i < orders.size(); i++) {
        cout << orders[i].order_id << " - " << ctime(&orders[i].timestamp);
    }
}

int main() {
    srand(time(NULL));

    vector<Order> orders;
    cout << "Generating orders..." << endl;
    generate_sample_orders(orders, 10000); // smaller number for testing

    cout << "Sorting orders..." << endl;
    merge_sort(orders, 0, orders.size() - 1);

    cout << "\nFirst 20 sorted orders:\n";
    print_first_n_orders(orders, 20);

    return 0;
}

