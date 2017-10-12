
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
}

template <class type>
void Shop<type>::add(type dessert) {
	products.push_back(dessert); 
}
