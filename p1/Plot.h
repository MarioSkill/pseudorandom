#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#define NUM_COMMANDS 2
using namespace std;

class Plot{
public:
	Plot();
	~Plot();
	void Graficar(std::vector<float> n,string name);
	void Graficar(std::vector<int> n,string name);
};

