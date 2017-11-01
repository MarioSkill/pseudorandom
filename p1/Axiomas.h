#include "Statistics.h"
#include "Utils.h"
#include <string.h>
#include "../bigint/BigIntegerLibrary.hh"
#include <stdlib.h>
using namespace std;
class Axiomas{
	private:
		int b;
		int m;
		int a;

	public:
		Utils utils;
		Statistics statistical;
		Axiomas();
		~Axiomas();
		void primero();
		void segundo();
		BigInteger tercero(int a,int m,vector<unsigned long> p);
		

}; 