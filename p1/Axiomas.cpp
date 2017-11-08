#include "Axiomas.h"

Axiomas::Axiomas(){}
Axiomas::~Axiomas(){}

BigInteger Axiomas::tercero(int a,int m,vector<unsigned long> p){
	//Periodo m-1, si y solo si m ES PRIMO y cumple:
	// a ^((m-1)/p) != 1 mod m, para todos los factores primos p de m -1

    vector<unsigned long>::iterator it;
    BigInteger r;

    for(it=p.begin(); it < p.end(); it++){
        
        int pp = *it;
        long op = (m-1)/pp;
       // cout << "a : "+to_string(a) +" m: "+to_string(m)+" p: "+to_string(pp) +" (m-1)/p: "+to_string(op) +"\n";
        r= modexp(a,op,m);

        if (r == 1 ){
            break;
        }
    }
    return r;

}


int main(int argc, char const *argv[]){

  if(argc !=  13){
        cout << "USAGE: ./Axiomas -p <1000> -c <50> -n <10> -alpha1 <0.05> -alpha2 <0.09> -alpha3 <0.05>" << endl;
        cout << "e.g. ./Axiomas -p 99000 -c 100 -n 10 -alpha1 0.005 -alpha2 0.09 -alpha3 0.05"<< endl;
        exit (-1);
    }
    std::string::size_type sz;     // alias of size_t

    string param1 = argv[1];
    int numRamdoms = atoi(argv[2]);
    string param2 = argv[3];
    int _class = atoi(argv[4]);
    string param3 = argv[5];
    int numListRamdoms = atoi(argv[6]);
    string param4 = argv[7];
    float alpha_chi = stof ( argv[8]);
    string param5 = argv[9];
    float alpha_norm = stof ( argv[10]);
    string param6 = argv[11];
    float alpha_ks = stof ( argv[12]);
  
    if ( param1.compare("-p") != 0 ){
        cout << "Argument "+param1+"not valid "<< endl << "USAGE: ./Axiomas -p <1000> -c <50>" << endl;
        exit (-1);
    } 
 
    if ( param2.compare("-c") != 0 ){
        cout << "Argument "+param2+"not valid "<< endl << "USAGE: ./Axiomas -p <1000> -c <50>" << endl;
        exit (-1);
    }
 
    if ( param3.compare("-n") != 0 ){
        cout << "Argument "+param4+"not valid "<< endl << "USAGE: ./Axiomas -p <1000> -c <50>" << endl;
        exit (-1);
    }

    if ( param4.compare("-alpha1") != 0 ){
        cout << "Argument "+param4+"not valid "<< endl << "USAGE: ./Axiomas -p <1000> -c <50>" << endl;
        exit (-1);
    }

    if ( param5.compare("-alpha2") != 0 ){
        cout << "Argument "+param5+"not valid "<< endl << "USAGE: ./Axiomas -p <1000> -c <50>" << endl;
        exit (-1);
    }
    if ( param6.compare("-alpha3") != 0 ){
        cout << "Argument "+param6+"not valid "<< endl << "USAGE: ./Axiomas -p <1000> -c <50>" << endl;
        exit (-1);
    }
    if ( numRamdoms  < 0 ){
        cout << "(-p atribute ) Num Ramdom not valid"<< endl << "valid range [1 - inf]" << endl;
        exit (-1);
    }    
  
    if ( _class < 0 ){ 
        cout << "(-c atribute ) Class number not valid"<< endl << "valid range [1 - inf]" << endl;
        exit (-1);
    }

    if ( numListRamdoms < 0 ){
        cout << "(-n atribute )The list number ramdoms is not valid, "<< endl << "valid range [1 - 1000]" << endl;
        exit (-1);
    }
    
    if ( alpha_chi < 0 || alpha_chi > 0.995F ){
        cout << "(-alpha1 atribute )The alpha value is not valid, "<< endl << "valid range [0.995   0.99    0.975   0.95    0.90    0.10    0.05    0.025   0.01    0.005]" << endl;
        exit (-1);
    }  
    if ( alpha_ks < 0 || alpha_ks > 0.995F ){
        cout << "(-alpha1 atribute )The alpha value is not valid, "<< endl << "valid range [0.995   0.99    0.975   0.95    0.90    0.10    0.05    0.025   0.01    0.005]" << endl;
        exit (-1);
    }

    Axiomas axioma;
    vector<unsigned long> primes;
    primes = axioma.utils.get_primes(10000);//10000000
    int primeID = primes.size()-2;
    int m =primes.at(primeID);
    int a =74;
   
   
    cout << "-------- INITIALIZATION VALUES --------" << endl<<endl;
    cout << "\tNumber of pseudorandom numbers to be generated: "<< numRamdoms<< endl;
    cout << "\tNumber of class to be generated: "<< _class<< endl;
    cout << "\tNumber of lists of pseudorandom numbers to generate: "<< numListRamdoms<< endl;
    cout << endl <<"-------- OTHTER VALUES (m,a) --------" << endl;
    cout << "\tInitial m: "<< m<< endl;
    cout << "\tInitial a: "<< a<< endl<<endl;
   

    vector<unsigned long> primeFactorsofM = axioma.utils.getprimeFactors(m-1);
    
    cout <<"-------- Pseudorandom: [m - 1] PERIOD --------"<<endl<<endl;
    int i;
    int tests=0;
    for (i = 0; i < numListRamdoms; ++i) {
         
        while (axioma.tercero(a+=1,m,primeFactorsofM)==1);
        vector<float> result = axioma.utils.myRandomsNorm( a, m, numRamdoms );
        tests=0;
        //call staticst
        cout << "   List of pseudorandom: "<< i << " a: " << a << " m: "<< m << endl;
     
        cout << "\t--------------- Chi2 - Pearson ---------------"<<endl;
        cout << "\t\tK: "<<_class<<" Alpha: "<< alpha_chi <<  endl;
        tests+= axioma.statistical.chi2pearson(result,alpha_chi,_class);
      
        cout << "\t--------------- K-S ---------------"<<endl;
        cout << "\t\tNº "<<numRamdoms<<" alpha = 0.05"  <<endl;
        tests+= axioma.statistical.ks(result,alpha_ks,numRamdoms);
    
        cout << "\t--------------- Rachas ---------------"<<endl; 
        cout << "\t\tN: "<<numRamdoms<<" Alpha: "<< alpha_norm <<  endl;
        tests+= axioma.statistical.rachas(result,alpha_norm,numRamdoms);
       
    
        string file_name ("./Resultados/lista_"+std::to_string(i) +"_a_"+std::to_string(a)+"_m_"+std::to_string(m)+".csv");
        cout<<"File saved: "<<file_name<<endl;
       axioma.utils.primesToCSV(result,file_name);
        cout << "------------------------------ SUMMARY ------------------------------"<<endl<<endl;
        cout << "\tTotal test 3"<<endl;
        cout << "\tTest passed: "<<tests <<"/3"<<endl<<endl;
        cout << "------------------------------ ------- ------------------------------"<<endl<<endl<<endl;
        primeID--; 
        m =primes.at(primeID); 

    }      
      
    cout<<endl <<"-------- Pseudorandom: undefined PERIOD --------"<<endl<<endl;
   
    long aa = 110351; 
    long mm = 429496;  
    i =0;
    vector<float> result = axioma.utils.myRandomsNorm( aa, mm, numRamdoms );
    string file_name ("./Resultados/lista_"+std::to_string(i) +"_a_"+std::to_string(aa)+"_m_"+std::to_string(mm)+".csv");
    cout<<"File saved: "<<file_name<<endl;
    axioma.utils.primesToCSV(result,file_name);

    tests=0;
    //call staticst
    cout << "   List of pseudorandom: "<< i << " a: " << aa << " m: "<< mm << endl;
    cout << "\t--------------- Chi2 - Pearson ---------------"<<endl;
    cout << "\t\tK: "<<_class<<" Alpha: "<< alpha_chi <<  endl;
    tests+= axioma.statistical.chi2pearson(result,alpha_chi,_class);
    cout << "\t--------------- Rachas ---------------"<<endl; 
    cout << "\t\tN: "<<numRamdoms<<" Alpha: "<< alpha_norm <<  endl;
    tests+= axioma.statistical.rachas(result,alpha_norm,numRamdoms);
    cout << "\t--------------- K-S ---------------"<<endl;
    cout << "\t\tNº "<<numRamdoms<<" alpha = 0.05"  <<endl;
    tests+= axioma.statistical.ks(result,alpha_ks,numRamdoms);    
    //axioma.statistical.getX_GD(0.3F);
  // cout << axioma.utils.cnd_manual(0.25)<<endl;
    cout << "------------------------------ SUMMARY ------------------------------"<<endl<<endl;
    cout << "\tTotal test 3"<<endl;
    cout << "\tTest passed: "<<tests <<"/3"<<endl<<endl;
    cout << "------------------------------ ------- ------------------------------"<<endl;
      
    return 0;
}
   