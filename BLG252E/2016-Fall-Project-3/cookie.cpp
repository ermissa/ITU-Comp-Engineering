
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "cookie.h"
using namespace std;

void Cookie::print() {
	cout<<name<<" #"<<number<<" Cost:"<<cost<<endl;
}

Cookie::Cookie(string nametoadd,float numbertoadd,float price) {
	name=nametoadd;
	number=numbertoadd;
	priceperdozen=price;
	cost=(numbertoadd/12)*price;
}

