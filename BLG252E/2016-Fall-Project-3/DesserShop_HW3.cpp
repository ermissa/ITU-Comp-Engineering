// Saim Fatih Ermiþ
//150120144
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <sstream>
#include <fstream>

#include "shop.h"
#include "cookie.cpp"
#include "candy.cpp"
#include "icecream.cpp"

using namespace std;



int main() {
	
	
	Cookie cookie1("Chocolate Chip Cookies",10, 180); //(name, pieces, priceperdozen)
	Cookie cookie2("Cake Mix Cookies", 16, 210);
	
	Shop<Cookie> cookieShop(cookie1);
	cookieShop.add(cookie2);
	cout<<cookieShop<<endl;

	//Catch an exception here while trying to access the element at(2)
//    cout << cookieShop[2] << endl;

	Icecream icecream1("Chocolate ice cream",1.5, 170); //(name, litre, priceperlitre)
	Shop<Icecream> icecreamShop(icecream1); 
	cout<<icecreamShop<<endl;

   
	try{
		icecreamShop.setDiscount(50);
	}
	catch(const char* error) {
		cout<<error<<endl;
	}
	

	Candy candy2("Gummi bears",12,89); //(name, weight, priceperkg)
	Candy candy3("Hanukkah gelt",8,110);

	Shop<Candy> candyShop(candy2);
	candyShop.add(candy3);
    
    try{
	candyShop.setDiscount(15);
	}
	catch(const char* error) {
		cout<<error<<endl;
	}
	
	cout<<candyShop<<endl;

	
	
	///////////////Stoktan okuma iþlemleri
	ifstream stock("stock.txt"); //stoktan okuyoruz.
	string ignore_line; //ilk satýr boþ satýr
	
	getline(stock,ignore_line); //atladýk geçtik
	string dessert_name,dessert_type,dessert_itemcount,dessert_price;
	float f_itemcount,f_price;

	Shop<Cookie> cookie_shop; //dükkanlarýmýz.henüz ürün yok.
	Shop<Candy> candy_shop;
	Shop<Icecream> icecream_shop;
	
	while(!stock.eof()) {
		
		getline(stock,dessert_name,'\t'); //tab'a kadar okuyor.
		getline(stock,dessert_type,'\t');
		getline(stock,dessert_itemcount,'\t');
		getline(stock,dessert_price);
		
		stringstream ss,ss2; //String to float
		ss<<dessert_itemcount;
		ss>>f_itemcount;
			
		ss2<<dessert_price;
		ss2>>f_price;
		
		//Hangi tip tatlý olduðunu seçmek için conditionlarý koyuyoruz.
		if(dessert_type=="1"){
			Cookie cookie(dessert_name,f_itemcount,f_price);
			cookie_shop.add(cookie);			
		}
		
		else if(dessert_type=="2") {
			Candy candy(dessert_name,f_itemcount,f_price);
			candy_shop.add(candy);
		}
		
		else if(dessert_type=="3") {
			Icecream icecream(dessert_name,f_itemcount,f_price);
			icecream_shop.add(icecream);
		}
		
	}
	
	cout<<cookie_shop<<endl<<candy_shop<<endl<<icecream_shop<<endl;
	
	//////////////////// Order okuma ve checkout yazma iþlemleri
	string dessert_name_ordered,dessert_number_ordered;
	float f_number_ordered;
	ifstream order("order2.txt"); //dosya okuma iþlemleri
	ofstream checkout("checkout2.txt");  //dosya yazma iþlemleri
	while(!order.eof()) {
		getline(order,dessert_name_ordered,'\t');
		getline(order,dessert_type,'\t');
		getline(order,dessert_number_ordered);
		
		stringstream ss;
		ss<<dessert_number_ordered;
		ss>>f_number_ordered;
		
		if(dessert_type=="1") {
			for(int i=0	; i<cookie_shop.products.size() ; i++){
				if(cookie_shop.products[i].name==dessert_name_ordered){ //eðer istenen isimde tatlý var ise
					
					if(cookie_shop.products[i].number<f_number_ordered){
						checkout<<"!!!We don't have "<< f_number_ordered-cookie_shop.products[i].number<<"("<<cookie_shop.products[i].name<<")s"<<endl;
					}
					
					else if(cookie_shop.products[i].number>=f_number_ordered){
					}
					
					}
				
				else if(cookie_shop.products[i].name!=dessert_name_ordered){ //istenen isimde tatlý yok ise
					checkout<<"There is no dessert with ("<<dessert_name_ordered<<") name"<<endl;
				}
		}
		
	}
	
	
//	cout<<cookie_shop<<endl;
}
}

