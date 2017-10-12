
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "icecream.h"

using namespace std;

Icecream::Icecream(string nametoadd,float litretoadd,float price) {
	name=nametoadd;
	litre=litretoadd;
	priceperlitre=price;
	cost=litretoadd*price;
}

void Icecream::print() {
	cout<<name<<" #"<<litre<<" Cost:"<<cost<<endl;
}

