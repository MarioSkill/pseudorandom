#include "Distributions.h"


	struct myclassF {
	  bool operator() (float i,float j) { return (i<j);}
	} myobject_float;

	Distributions::Distributions(){};
	Distributions::~Distributions(){};
	vector<float> Distributions::boxMuller(vector<float> pseudoRandoms){
	///	cout << "-------- INITIALIZATION VALUES --------" << endl;
	//	cout << "-------------- BOX-MULLER --------------" << endl;
	//	cout <<"u1: "<<u1<< " u2: "<<u2<<endl;

	float u1,u2;
	float  R;
	float  teta;
	float  X;
	float  Y;
	vector<float> bm;
	for (vector<float>::iterator it=pseudoRandoms.begin(); it!=pseudoRandoms.end(); ++it){
		u1 = *it; ++it;
		u2 = *it;
		R  = sqrt((-2.0*log(u1)));
		teta = 2*M_PI*u2;
		X = R*cos (teta); 
		Y = R*sin (teta);
		bm.push_back(roundf(X * 100) / 100);
		bm.push_back(roundf(Y * 100) / 100);
	}
 
    return bm;
	}


	vector<float> Distributions::marsaglia(vector<float> pseudoRandoms){
		//cout << "-------- INITIALIZATION VALUES --------" << endl;
		//cout << "-------------- MARSAGLIA --------------" << endl;
		//cout <<"u1: "<<u1<< " u2: "<<u2<<endl;
		
		vector<float> ms;
		float u1,u2;
		for (vector<float>::iterator it=pseudoRandoms.begin(); it!=pseudoRandoms.end(); ++it){
			u1 = *it; ++it;
			u2 = *it;
			double v1 = (2*u1) - 1 ;
			double v2 = (2*u2) - 1 ;

			double S = pow(v1,2)+pow(v2,2);

			if (S<=1 ){
				float X1 = v1*sqrt(float(-2.0*log(S)/S));
				float X2 = v2*sqrt(float(-2.0*log(S)/S));
				ms.push_back(roundf(X1 * 100) / 100);
				ms.push_back(roundf(X2 * 100) / 100);
				
			}
		}
		return ms;
	}
	/*utils .. */
	map <float, int> Distributions::getFrecuency(vector<float> frec){
		
		sort(frec.begin(), frec.end(), myobject_float);
		map <float, int> distribution;
		for (vector<float>::iterator it=frec.begin(); it!=frec.end(); ++it){
			pair<map<float,int>::iterator,bool> ret;
			ret = distribution.insert ( pair<float,int>(*it,1) );
			if (ret.second==false) {
				map<float, int>::iterator ti = distribution.find(*it); 
				if (ti !=distribution.end())
				ti->second = ti->second+1;
			}
		}
       return distribution;
	}
	string Distributions::ReplaceAll(std::string str, const std::string& from, const std::string& to) {
	    size_t start_pos = 0;
	    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
	        str.replace(start_pos, from.length(), to);
	        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	    }
	    return str;
	}

	float Distributions::funDensidad(float n){
		float sigma2 = 1;
		float mu =0;
		return  (1/ ( sqrt(2*M_PI*sigma2) ) ) * exp ( -0.5 * pow( ( (n-mu)/sigma2 ),2)  );
	}

	float Distributions::geometrica(float n){
		float p = 0.3F;
		return p*pow((1-p),n)   ;
	}
	float Distributions::geometricaInversa(float r){
		float p =0.3F;
		float n = (float)(1 + ( log(r)/ log(1-p) ) );
		//cout << std::to_string(n)<<endl;
		return roundf(n* 100)/ 100;
	}

	void Distributions::dataToCSV(string lista,map <float, int> distribution,int fun){
	
		string file_name ("./Graficos/"+lista+".csv");
		cout<<"File saved: "<<file_name<<endl;
		ofstream myfile (file_name);
		string header =lista+";FRECUENCIA;DENSIDAD\n";

		 for (std::map<float,int>::iterator it=distribution.begin(); it!=distribution.end(); ++it){

		        stringstream key;
				stringstream value;
				key << fixed << setprecision(2) << it->first;
				value << fixed << setprecision(2) << it->second;
				if (fun ==0){
					header = header + 
					key.str() +";"+ 
					value.str()+";"+ 
					std::to_string(funDensidad( it->first))
					+"\n";
				}else{
					header = header + 
					key.str() +";"+ 
					value.str()+";"+ 
					std::to_string(geometrica( it->first))
					+"\n";
				}

			}		

		header = ReplaceAll(header, std::string("."), std::string(","));

		if (myfile.is_open()){
		myfile << header;
		myfile.close();
		}
		
	}

vector<int> Distributions::getFrecuencyOfNumbrer(map<float, int> n){
	vector<int> t;
		
		for (map<float, int>::iterator it=n.begin(); it!=n.end(); ++it){
			t.push_back(it->second);
			//Graficar
		}
	return t;
}

vector<float> Distributions::getNumbrerOfDistribution(map<float, int> n){
	vector<float> t;
		
		for (map<float, int>::iterator it=n.begin(); it!=n.end(); ++it){
			t.push_back(it->first);
			//Graficar
		}
	return t;
}

int main(int argc, char const *argv[]){
  	if(argc !=  7){
        cout << "USAGE: ./Distributions -a <4664> -m <50> -n <10>" << endl;
        cout << "e.g. ./Distributions -a 2037 -m 99871 -n 99000"<< endl;
        exit (-1);
    }
    string param1 = argv[1];
    int a = atoi(argv[2]);
    string param2 = argv[3];
    int m = atoi(argv[4]);
    string param3 = argv[5];
    int n_ran = atoi(argv[6]);

    if ( param1.compare("-a") != 0 ){
        cout << "Argument "+param1+"not valid "<< endl << "USAGE: ./Distributions -a <4664> -m <50> -n <10>" << endl;
        exit (-1);
    } 
    if ( param2.compare("-m") != 0 ){
        cout << "Argument "+param2+"not valid "<< endl << "USAGE: ./Distributions -a <4664> -m <50> -n <10>" << endl;
        exit (-1);
    }
     if ( param3.compare("-n") != 0 ){
        cout << "Argument "+param3+"not valid "<< endl << "USAGE: ./Distributions -a <4664> -m <50> -n <10>" << endl;
        exit (-1);
    }  


  	cout << "-------- INITIALIZATION VALUES --------" << endl<<endl;
  	cout << "\tInitial m: "<< m<< endl;
    cout << "\tInitial a: "<< a<< endl;
    cout << "\tNumber of pseudorandom numbers to be generated: "<< n_ran<< endl;
    cout << "-------- -------------------- --------" << endl<<endl;

	Distributions dist;
	Utils u;
	Plot p;
	

	vector<float> pseudoRandoms = u.myRandomsNorm( a, m, n_ran );
	

	cout << "-------------- BOX-MULLER --------------" << endl;
	 

 
	map <float, int> bm = dist.getFrecuency( dist.boxMuller(pseudoRandoms) );
	
	p.Graficar(dist.getFrecuencyOfNumbrer(bm),"./Graficos/BOXMULLER");
	vector<float> gauss;
	for (map <float, int>::iterator it=bm.begin(); it!=bm.end(); ++it){
	    gauss.push_back(dist.funDensidad(it->first));
	}

	p.Graficar(gauss,"./Graficos/Normal-BM");


	dist.dataToCSV  ("BOXMULLER",bm,0);

	cout << "-------------- MARSAGLIA --------------" << endl;

	map <float, int> ms =dist.getFrecuency( dist.marsaglia(pseudoRandoms) );
	dist.dataToCSV  ("MARSAGLIA",ms,0);

	p.Graficar(dist.getFrecuencyOfNumbrer(ms),"./Graficos/MARSAGLIA");
	
	vector<float> gauss2;
	for (map <float, int>::iterator it=ms.begin(); it!=ms.end(); ++it){
		gauss2.push_back(dist.funDensidad(it->first));
	}

	p.Graficar(gauss,"./Graficos/Normal-MS");
	vector<float> inve_gm;
	for (vector<float>::iterator it=pseudoRandoms.begin(); it!=pseudoRandoms.end(); ++it){
		inve_gm.push_back(dist.geometricaInversa(*it));
 

	} 



	map <float, int> Invgm = dist.getFrecuency(inve_gm);

	p.Graficar(dist.getFrecuencyOfNumbrer(Invgm),"./Graficos/INV_GEOMETRICA");

	std::vector<float> geometrica=dist.getNumbrerOfDistribution(Invgm);
	std::vector<float> gm;
	for (vector<float>::iterator it=geometrica.begin(); it!=geometrica.end(); ++it){
		gm.push_back( dist.geometrica(*it) );
	} 

	p.Graficar(gm,"./Graficos/GEOMETRICA");

	dist.dataToCSV  ("./Graficos/GEOMETRICA",Invgm,1);
	
 
}
