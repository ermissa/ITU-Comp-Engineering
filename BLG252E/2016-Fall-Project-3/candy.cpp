
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "candy.h"
using namespace std;

Candy::Candy(string nametoadd,float weighttoadd,float price) {
	name=nametoadd;
	weight=weighttoadd;
	priceperkg=price;
	cost=weighttoadd*price;
}

void Candy::print() {
	cout<<name<<" #"<<weight<<" Cost:"<<cost<<endl;
}
