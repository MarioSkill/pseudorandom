#include "Utils.h"
	Utils::Utils(){};
	Utils::~Utils(){};
vector<unsigned long> Utils::get_primes(unsigned long max){
    vector<unsigned long> primes;
    char *sieve;
    sieve = new char[max/8+1];
    // Fill sieve with 1  
    memset(sieve, 0xFF, (max/8+1) * sizeof(char));
    for(unsigned long x = 2; x <= max; x++)
        if(sieve[x/8] & (0x01 << (x % 8))){
            primes.push_back(x);
            // Is prime. Mark multiplicates.
            for(unsigned long j = 2*x; j <= max; j += x)
                sieve[j/8] &= ~(0x01 << (j % 8));
        }
    delete[] sieve;
    return primes;
}
int Utils::primesToCSV(vector<float> primes, string file){
	ofstream myfile (file);
	string header ="numero\n";
	vector<float>::iterator it;
	int id =0;
	for(it=primes.begin(); it < primes.end(); it++){
		//cout << *it << " ";
		string n = std::to_string(*it);
		header = header + n+"\n";
		id ++;
	}
	if (myfile.is_open()){
		myfile << header;
		myfile.close();
	}
	return 0;

}

vector<unsigned long> Utils::getprimeFactors(int n) {
    vector<unsigned long> factors;
    // Print the number of 2s that divide n
    int insert =0;

    while (n%2 == 0) {
       // printf("%d ", 2);
        n = n/2;
        if(insert == 0 ){
            factors.push_back(2);
            insert=1;
        }
    }
    
    // n must be odd at this point.  So we can skip 
    // one element (Note i = i +2)
    for (int i = 3; i <= sqrt(n); i = i+2) {
        // While i divides n, print i and divide n
        insert=0;
        while (n%i == 0) {
            //printf("%d ", i);
            n = n/i;
            if(insert == 0 ){
                factors.push_back(i);
                insert=1;
            }
        }
    }
    // This condition is to handle the case when n 
    // is a prime number greater than 2
    if (n > 2)
        factors.push_back(n);
        //printf ("%d ", n);
    //vector<unsigned long>::iterator it;
    //for(it=factors.begin(); it < factors.end(); it++)
      //  cout << *it <<",";
    return factors;
}

 void Utils::saveCSV(string csv, string file){
    ofstream myfile (file);
    if (myfile.is_open()){
        myfile << csv;
        myfile.close();
    }
 }


vector<float> Utils::myRandomsNorm(int a,int m, int n_ran ){

	vector<int> result;
	int r=5;
   // int c = 32768;
	for (int x = 0; x < n_ran; ++x) { 
		r = ( a*r  );
		r = r % m;		
		result.push_back(r);
	}      
	int max=0;
	int min=0;

    vector<float> vnorm;
    max = *std::max_element( result.begin(), result.end() );
    min = *std::min_element( result.begin(), result.end() );
	//cout<< max<<", "<<min<<endl;
	float num =0.0;
	int den = 0;
	float numero = 0.0;
    for (std::vector<int>::iterator it=result.begin(); it!=result.end(); ++it){
	num = (float)(*it - min);
	den= (max - min);
	numero= (float)(num/den);
	
        vnorm.push_back(numero);
    }

	return vnorm;
}


