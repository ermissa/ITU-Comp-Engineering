
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>


using namespace std;

template <typename type>
class Shop {
public:
	vector<type> products;
	void add(type);
	Shop(){	};
	Shop(type);
	float totalcost=0;
	void setDiscount(int);
	friend ostream &operator<<(ostream &output,Shop &shop){
		cout<<"**********************"<<endl;
		cout<<"Number Of Items:"<<shop.products.size()<<endl;
		for(int i=0	; i<shop.products.size() ; i++) {
			cout<<i+1<<" : ";
			shop.products[i].print();
		}
		cout<<"**********************"<<endl;
		cout<<"Total cost: "<<shop.totalcost<<endl;
		return output;
	}
};

template <typename type>
void Shop<type>::setDiscount(int to_discount) {
	for(int i=0	; i<products.size() ; i++) {
			if(to_discount<0||to_discount>30) throw "Discount rate is out of rage";
			products[i].cost=products[i].cost-products[i].cost*(to_discount/100);
		}
}

template <class type>
Shop<type>::Shop(type dessert) {
	products.push_back(dessert);
	
//	for(int i=0	; i<products.size() ; i++) {
	totalcost=totalcost+products[0].cost*(108/100);
//		}
	

}

template <class type>
void Shop<type>::add(type dessert) {
	products.push_back(dessert);
	for(int i=0	; i<products.size() ; i++) {
		totalcost=totalcost+products[0].cost*(108/100);
	} 
}

