#include <vector>
#include <math.h>       /* sqrt */
#include <cmath>
#include <iostream>
#include "Utils.h"
#include <complex>
#include <map>
#include <string.h>
#include <iostream>
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include "Plot.h"
using namespace std;

class Distributions {

public:
	Distributions();
	~Distributions();
	std::vector<float> boxMuller(std::vector<float> pseudoRandoms);
	std::vector<float> marsaglia(std::vector<float> pseudoRandoms);
	float geometricaInversa(float n);
	float geometrica(float n);
	map <float, int> getFrecuency(vector<float> frec);
	float funDensidad (float n);
	string ReplaceAll(std::string str, const std::string& from, const std::string& to);
	void dataToCSV(string lista,map <float, int> distribution,int fun);
	vector<int> getFrecuencyOfNumbrer(map<float, int> n);
	vector<float> getNumbrerOfDistribution(map<float, int> n);
};
