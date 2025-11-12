#include<bits/stdc++.h>
using namespace std;
struct Order
{
	string order_id;
	time_t timestamp;
};
void generateOrders(vector<Order>& orders, int n)	
{
	tm base_time{};
	base_time.tm_year=2025-1900;
	base_time.tm_mon=11;
	base_time.tm_mday=25;
	base_time.tm_hour=12;
	time_t base=mktime(&base_time);
	orders.resize(n);
	for(int i=0;i<n;i++)
	{
		int random_min=rand()%100000;
		orders[i].timestamp=base+random_min*60;
		orders[i].order_id="ORD"+to_string(i+1);
	}
}
void merge(vector<Order> &orders, int low, int mid, int high)
{
	vector<Order> temp;
	int left=low;
	int right=mid+1;
	while(left<=mid && right<=high)
	{
		if(orders[left].timestamp<=orders[right].timestamp){ 
			temp.push_back(orders[left]);
			left++;
		}
		else{
			temp.push_back(orders[right]);	
			right++;
		}
	}

	while(left<=mid)
	{
		temp.push_back(orders[left]);
		left++;
	}
	while(right<=high)
	{
		temp.push_back(orders[right]);
		right++;
	}
	for(int i=low;i<=high;i++)
		orders[i]=temp[i-low];

}
void mergeSort(vector<Order> &orders,int low,int high)
{
	if(low>=high) 
        return;
	int mid=(low+high)/2;
	mergeSort(orders,low,mid);
	mergeSort(orders,mid+1,high);
	merge(orders,low,mid,high);
}
void printOrders(vector<Order> &orders,int n)
{
	for(int i=0;i<n;i++)
	{
		cout<<orders[i].order_id<<ctime(&orders[i].timestamp);
	}
}

int main()
{
    srand(time(NULL));
	vector<Order> orders;
	cout<<"\nGenerating orders:";
	generateOrders(orders,1000000);

	mergeSort(orders,0,orders.size()-1);
	
	printOrders(orders,20);	
	
return 0;
}