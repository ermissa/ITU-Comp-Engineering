#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <stdio.h>
#include <iomanip>
#include <cstring>
#include <string.h>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

static int mode;

class Card{
public:
	Card(string s1,string s2,string s3,string s4,string s5,string s6);
	Card(Card *other);
	Card(){}


	friend bool operator<(const Card &c1,const Card  &c2){
		if (mode ==0){ //FullSort yaparken kullanýlacak kýsým
			
			int condition2=c1.classes.compare(c2.classes);
			if(condition2!=0){
				return condition2<0;
			}

			if(c1.cost.length() == c2.cost.length()) { // 0-9 arasýndaki rakamlarý string olarak direk kýyaslamamýz sýkýntý oluþturmuyor fakat 2 basamaklý olduðu zaman sýkýntý çýkardýðý için uzunluklarýný kontrol etmemiz gerekiyor.
				int condition3=c1.cost.compare(c2.cost);
				if(condition3!=0){
					return condition3<0;
				}
			} else {
				return c1.cost.length() < c2.cost.length();
			}

			int condition1= (c1.name.compare(c2.name));
			if(condition1!=0){
				return condition1<0;
			}
			return false;
		} 
		
		else { // FilterSort yaparken kullanýlacak kýsým
			int condition1=c1.type.compare(c2.type);
			if(condition1!=0){
				return condition1<0;
			}
			return false;
		}
	}

	
	string name;
	string classes;
	string rarity;
	string set;
	string type;
	string cost;
};


Card::Card(Card *other){
	this->name=other->name;
	this->classes=other->classes;
	this->rarity=other->rarity;
	this->set=other->set;
	this->type=other->type;
	this->cost=other->cost;
}

Card::Card(string s1,string s2,string s3,string s4,string s5,string s6) {
	name = s1;
	classes = s2;
	rarity=s3;
	set=s4;
	type=s5;
	cost=s6;
}


class CardManager{
public:
	string filename;
	CardManager(string);
	void writeFile(Card [],int);
	void fullSort(string,string);
	void filterSort(string,string);
	void swap(Card&,Card&);
	void mergeSort(Card [],int,int);
	void merge(Card [],int,int,int);
	
	void printdeck(Card [],int);
};

CardManager::CardManager(string name) {
	filename = name;
}

void CardManager::writeFile(Card deck[],int deck_counter) {
	ofstream myfile;
	myfile.open (this->filename.c_str());
	for(int a=0 ; a<deck_counter-1 ; a++) {
		myfile << deck[a].name <<'\t'<<deck[a].classes<<'\t'<<deck[a].rarity<<'\t'<<deck[a].set<<'\t'<<deck[a].type<<'\t'<<deck[a].cost<<'\n';
	}
	myfile.close();
}



void CardManager::printdeck(Card deck[],int deck_counter) {
	int a=0;
	while(a<deck_counter) {
		cout<<deck[a].name<<"\t"<<deck[a].classes<<"\t"<<deck[a].rarity<<"\t"<<deck[a].set<<"\t"<<deck[a].type<<"\t"<<deck[a].cost<<endl;
		a++;
	}
}

void CardManager::merge(Card deck[],int low,int mid,int high) {
	int i,j,k;
	Card *temp = new Card[high-low+1]; // temp objesini en baþta dinamik deðil statik olarak ayýrmýþ ve hata almýþtým. Statik alýnan deðiþkenlerin output olarak çýkan exe dosyana yazýldýðýný,onun da bir limiti olduðunu farkedince dinamik olarak yer ayýrdým.

	k=0;
	j=mid+1;
	i=low;
	
	while(i<=mid && j<=high) {
		if(deck[i]<deck[j]) {
			temp[k] = deck[i];
			k++;
			i++;
		} else {
			temp[k] = deck[j];
			k++;
			j++;
		}
	}
	
	while(i<=mid) {
		temp[k]=deck[i];
		k++;
		i++;
	}
	
	while(j<=high) {
		temp[k]=deck[j];
		k++;
		j++;
	}
	
	for(i=low ; i<=high ; i++) {
		deck[i]=temp[i-low];
	}
}

void CardManager::mergeSort(Card deck[],int low,int high) {
	int mid;
	if(low<high) {
		int mid = (low+high)/2;
		
		mergeSort(deck,low,mid);
		mergeSort(deck,mid+1,high);
		
		merge(deck,low,mid,high);
	}
	
}

void CardManager::swap(Card &c1,Card &c2) {
	Card temp=c1;
	c1=c2;
	c2=temp;
}


void CardManager::filterSort(string sortType,string FileName) {
	if(sortType=="-i") {
		ifstream record_book(FileName.c_str());
		string str1,str2,str3,str4,str5,str6;
		int row_ctr = 0;
		
		while(!record_book.eof()) { 
			getline(record_book,str1 , '\n');
			row_ctr++;
		}
			
		record_book.clear(); // eof'ye ulaþtýktan sonra tekrar baþa dönüyoruz.
		record_book.seekg(record_book.beg);
		
		Card *deck = new Card[row_ctr];
		//Card deck[row_ctr];
		int deck_counter = 0;
		
		while(!record_book.eof()) { 
			getline(record_book,str1 , '\t');		
			getline(record_book,str2 , '\t');		
			getline(record_book,str3 , '\t');		
			getline(record_book,str4 , '\t');		
			getline(record_book,str5 , '\t');		
			getline(record_book,str6 , '\n');
			deck[deck_counter] = Card(str1,str2,str3,str4,str5,str6); // Her satýr 1 karti ifade ettiði için her satýrdan sonra o kartýn objesini oluþturuyoruz.
			deck_counter++;	
		}
		int back;
		
		clock_t  clock1,clock2;
		clock1 = clock();
		
		for(int current=1 ; current<deck_counter ; current++) {
			back=current-1;
			//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			//Card *key = new Card(deck[current]);
			Card key = deck[current];
			while(key<deck[back] && back>=0) {
				swap(deck[back],deck[back+1]);
				if(back==0)
				    break;
				else 
			        back = back-1;				
			}
		}
		clock2 = clock();
		
		cout<< "Sort time "<< (float)(clock2 - clock1)/ CLOCKS_PER_SEC << " "<<endl;
		writeFile(deck,deck_counter);	
	} else if(sortType=="-m") { // MERGE SORT
		
		ifstream record_book(FileName.c_str());
		string str1,str2,str3,str4,str5,str6;
		int row_ctr = 0;
	
		while(!record_book.eof()) { 
			getline(record_book,str1 , '\n');
			row_ctr++;
		}
			
		record_book.clear(); // eof'ye ulaþtýktan sonra tekrar baþa dönüyoruz.
		record_book.seekg(record_book.beg);
		
		Card *deck = new Card[row_ctr];	
		//Card deck[row_ctr];
		int deck_counter = 0;
		
		while(!record_book.eof()) { 
			getline(record_book,str1 , '\t');		
			getline(record_book,str2 , '\t');		
			getline(record_book,str3 , '\t');		
			getline(record_book,str4 , '\t');		
			getline(record_book,str5 , '\t');		
			getline(record_book,str6 , '\n');
			deck[deck_counter] = Card(str1,str2,str3,str4,str5,str6); // Her satýr 1 karti ifade ettiði için her satýrdan sonra o kartýn objesini oluþturuyoruz.
			deck_counter++;	
		}
		
		clock_t  clock1,clock2;
		clock1 = clock();
		
		mergeSort(deck,0,deck_counter-2); // Son okumadan sonra 1 tane daha arttýðý için 2 eksilttik.
		clock2 = clock();
		cout<< "Sort time "<< (float)(clock2 - clock1)/ CLOCKS_PER_SEC << " "<<endl;
		
		writeFile(deck,deck_counter);
	}
}




void CardManager::fullSort(string sortType,string FileName) {
	if(sortType=="-i") {
		ifstream record_book(FileName.c_str());
		string str1,str2,str3,str4,str5,str6;
		int row_ctr = 0;
	
		while(!record_book.eof()) { 
			getline(record_book,str1 , '\n');
			row_ctr++;
		}

		record_book.clear(); // eof'ye ulaþtýktan sonra tekrar baþa dönüyoruz.
		record_book.seekg(record_book.beg);
			
		//Card deck[row_ctr];
		Card *deck = new Card[row_ctr];
		int deck_counter = 0;
		while(!record_book.eof()) { 
			getline(record_book,str1 , '\t');		
			getline(record_book,str2 , '\t');		
			getline(record_book,str3 , '\t');		
			getline(record_book,str4 , '\t');		
			getline(record_book,str5 , '\t');		
			getline(record_book,str6 , '\n');
			deck[deck_counter] = Card(str1,str2,str3,str4,str5,str6); // Her satýr 1 karti ifade ettiði için her satýrdan sonra o kartýn objesini oluþturuyoruz.
			deck_counter++;	
		}

		int back;
		
		clock_t  clock1,clock2;
		clock1 = clock();
	    
	    for(int current=1 ; current<deck_counter ; current++) {
			back=current-1;
			//Card *key = new Card(deck[current]);
			Card key = deck[current];
			while(key<deck[back] && back>=0) {
				swap(deck[back],deck[back+1]);
				if(back==0)
				    break;
				else 
			        back = back-1;				
			}
		}
		clock2 = clock();
		
		cout<< "Sort time "<< (float)(clock2 - clock1)/ CLOCKS_PER_SEC << " "<<endl;
		writeFile(deck,deck_counter);
		
	} else if(sortType=="-m") { // MERGE SORT
		
		ifstream record_book(FileName.c_str());
		string str1,str2,str3,str4,str5,str6;
		int row_ctr = 0;
	
		while(!record_book.eof()) { 
			getline(record_book,str1 , '\n');
			row_ctr++;
		}
			
		record_book.clear(); // eof'ye ulaþtýktan sonra tekrar baþa dönüyoruz.
		record_book.seekg(record_book.beg);
		
	
		Card *deck = new Card[row_ctr];
		int deck_counter = 0;
		
		while(!record_book.eof()) { 
			getline(record_book,str1 , '\t');		
			getline(record_book,str2 , '\t');		
			getline(record_book,str3 , '\t');		
			getline(record_book,str4 , '\t');		
			getline(record_book,str5 , '\t');		
			getline(record_book,str6 , '\n');
			deck[deck_counter] = Card(str1,str2,str3,str4,str5,str6); // Her satýr 1 karti ifade ettiði için her satýrdan sonra o kartýn objesini oluþturuyoruz.
			deck_counter++;	
		}
				
		clock_t  clock1,clock2;
		clock1 = clock();
		
		mergeSort(deck,0,deck_counter-2); // Son okumadan sonra 1 tane daha arttýðý için 2 eksilttik.
		
		clock2 = clock();
		
		cout<< "Sort time "<< (float)(clock2 - clock1)/ CLOCKS_PER_SEC << " "<<endl;
		
		writeFile(deck,deck_counter);
	}


}





