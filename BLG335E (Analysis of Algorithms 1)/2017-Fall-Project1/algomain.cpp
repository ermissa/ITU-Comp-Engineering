#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include "algoclasses.h"
#include <ctime>

using namespace std;


int main(int argc, char *argv[]) {
	CardManager cardmanager(argv[4]);
	if(strcmp(argv[1],"-full")==0) {
		mode=0;
		cardmanager.fullSort(string(argv[2]),string(argv[3]));
	} else if(argv[1]="filter") {
		mode=1;
		cardmanager.filterSort(string(argv[2]),string(argv[3]));
	}	
	return 0;
}

