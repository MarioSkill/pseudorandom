#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <math.h>       /* sqrt */
#include <algorithm>    // std::min_element, std::max_element

using namespace std;

class Utils {
public:
	Utils();
	~Utils();
	vector<unsigned long> get_primes(unsigned long max);
	int primesToCSV(vector<float> primes, string file);
	vector<unsigned long> getprimeFactors(int n);
	void saveCSV(string csv, string file);
	vector<float> myRandomsNorm(int a,int m, int n_ran );
	
};