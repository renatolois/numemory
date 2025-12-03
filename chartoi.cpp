#include "chartoi.hpp"
#include <cstring>


int chartoi(char* str) {
	int n_int = 0;
	for(int i=0; i<strlen(str); i++) {
		n_int = n_int * 10 + str[i] - 48;
	}
	return n_int;
}
