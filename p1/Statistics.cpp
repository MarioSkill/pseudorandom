#include "Statistics.h"
Statistics::Statistics(){};
Statistics::~Statistics(){};

struct myclass {
  bool operator() (int i,int j) { return (i<j);}
} myobject;

struct myclassF {
  bool operator() (float i,float j) { return (i<j);}
} myobject_float;

int Statistics::chi2pearson(vector<float> numbers,float alpha, int k){
    float sum=0;
    std::sort(numbers.begin(), numbers.end(), myobject_float);
 

    for (auto& n : numbers)
        sum += (float)n;

    float x=0;
    float acum=0;
 	float e = (float)(numbers.size() / k);
    //cout <<"e "<<e<<"n: "<<numbers.size()<<endl;
	float limClass = (float)1/k; 
	


    for (std::vector<float>::iterator it=numbers.begin(); it!=numbers.end(); ++it){
    	if (*it <limClass ){
    		x++;
    	}else{
    		acum += (float)(pow((x-e),2)/e);
    		x = 1;
    		limClass+=(float)1/k;
    	}

    }

    int oldk=k;
    if (k>30){
	    if (k <46 ){
	    	k =31;
	    }else if (k<56){
	    	k=32;
	    }else if(k<66) {
	    	k=33;
	    }else if (k<76){
	    	k=34;
	    }else if (k<86){
	    	k=35;
	    }else if (k<96){
	    	k=36;
	    }else{
	    	k=37;
	    }
	}
    int kPosition=0;
    if(alpha == .99F){
    	kPosition=1;
    }else if(alpha ==.975F){
    	kPosition=2;
    }else if(alpha ==.95F ){
    	kPosition=3;
    }else if(alpha ==.90F ){
    	kPosition=4;
    }else if(alpha ==.10F ){
    	kPosition=5;
    }else if(alpha == .05F){
    	kPosition=6;
    }else if(alpha ==.025F ){
    	kPosition=7;
    }else if(alpha == .01F){
    	kPosition=8;
    }else if(alpha == .005F){
    	kPosition=9;
    }
	//cout << "sum/k = ei: "<<sum <<"/"<< oldk << "= "<<e<<endl;
    cout << "\t\t\tchi X2: "<<(float)acum <<" > X("<<oldk<<","<<alpha<<") = "<< pearson[k-1][kPosition]<< endl;
    if ((float)acum > pearson[k-1][kPosition] ){
    	cout <<endl << "\t\t\t\033[1;31m======> Hipotesis rechazada, TEST = X\033[0m"<<endl;
        return 0;
    } else{
    	cout <<endl << "\t\t\t\033[1;32m======> No se puede rechazar la Hipotesis, TEST = ok\033[0m"<<endl;
        return 1;
    }



}

int Statistics::ks(vector<float> numbers,float alpha,int n){
     
  //vector<float> vnorm;
    vector<float> sn;
    //float max = *std::max_element( numbers.begin(), numbers.end() );
    std::sort(numbers.begin(), numbers.end(), myobject_float);
    int i =1;
    float dmax=-1;
    float dmin=-1;
    float i_n=0;
    float n_i = 0;
    float i_1_n=0;
    for (std::vector<float>::iterator it=numbers.begin(); it!=numbers.end(); ++it){
        i_n = (float)i/n;
        //n_i = (float)*it/max;
	    n_i=*it;
        i_1_n = (float)(i-1);
        i_1_n = (float)i_1_n/n;

        float aux = abs(i_n - n_i);
        float aux2 = abs(n_i - i_1_n);
        //cout<<n_i<< " - "<< i <<" - 1 / n"<<" = "<< i_1_n <<endl; 

        if (aux > dmax)
        	dmax = aux;
        if (aux2 > dmin){
        	dmin= aux2;
        }
        i++;
    }
    ///cout << "dmax " <<dmax << " dmin " << dmin<<endl;
    float abs_max=dmax;
    
    if (dmin > dmax)
    	abs_max = dmin;

    float k_n = 0.0;
    if(alpha == 0.2F){
        k_n = Kolmogorov_Smirnov[0][0]/sqrt(n);
    }else if(alpha ==0.1F){
        k_n = Kolmogorov_Smirnov[0][1]/sqrt(n);
    }else if (alpha ==0.05F){
        k_n = Kolmogorov_Smirnov[0][2]/sqrt(n);
    }else if (alpha == 0.02F){
        k_n = Kolmogorov_Smirnov[0][3]/sqrt(n);
    }else if (alpha == 0.01F){
        k_n = Kolmogorov_Smirnov[0][4]/sqrt(n);
        
    }else{
        cout << "No has puesto un alpha adecuado"<<endl;
    }

    cout<< "\t\t\tD = "<<abs_max<<" < "<< k_n <<"?"<<endl;

    if(abs_max<k_n){
        cout<<endl << "\t\t\t\033[1;32m======> NO hay evidencia de que las muestras NO provengan de una distribución uniforme, TEST = ok\033[0m"<<endl;
        return 1;
    } else{
         cout<<endl << "\t\t\t \033[1;31m======> Si hay evidencia que las muestras NO provengan de una distribución uniforme, TEST = X\033[0m"<<endl;
         return 0;
    }

}
int Statistics::rachas(vector<float> numbers,float alpha,int n){
    int count_rachas=0;
    int sw =0;
    float anterior=-1.0F;
    int isCreciendo=-1;
    for (std::vector<float>::iterator it=numbers.begin(); it!=numbers.end(); ++it){
        if (sw == 0){
            sw =1;
            anterior = *it;
        }else{
            if (anterior > *it){
                if (isCreciendo==0 || isCreciendo ==-1){
                    count_rachas++;
                    isCreciendo=1;
                }
            }else{
                if (isCreciendo==1 || isCreciendo ==-1){
                    count_rachas++;
                    isCreciendo=0;
                }    
            }
            anterior = *it;
        }

    }

//cout<<r<<endl;
    //0.00	0.01	0.02	0.03	0.04	0.05	0.06	0.07	0.08	0.09

    int r = count_rachas;
	float u = (2*n - 1);
	u = (float)u/3;
	float sigma2 = (16*n -29);
	sigma2 = (float)sigma2/90;
	double pmenor = (-r-u);
	pmenor = (double) pmenor/sqrt(sigma2);
	double pmayor = (double)(r-u);
	pmayor = (double )pmayor/sqrt(sigma2);
	
    cout << "\t\t\tNº Rachas en "<<n<<" numeros = " <<r <<endl;
    cout <<"\t\t\tP(Y < -Zn(μ,σ2)) +  P(Y > Zn(μ,σ2)) => P(Y < -Zn("<<u<<","<<sigma2<<")) +  P(Y > Zn("<<u<<","<<sigma2<<"))"<<endl;
    cout <<"\t\t\tP(Y < Zn(μ,σ2)) = "<< pmenor<< " + "<< "P(Y > Zn(μ,σ2)) = "<<pmayor<<endl<<endl;
   
    double proYmen;
    double proYmay;
    if (pmenor<0){
        proYmen = cnd_manual(pmenor);

    }else{
        proYmen = 1 - cnd_manual(pmenor);
    }

    if (pmayor>0){
        proYmay = cnd_manual(pmayor);

    }else{
        proYmay = 1 - cnd_manual(pmayor);
    }

    cout<<"\t\t\tCONCLUSIONS"<<endl;
  
    cout<<"\t\t\tP( Y < abs("<<pmenor<<") = "<< proYmen<< " + P( Y > abs("<<pmayor<<") = "<< proYmay<<endl;
    float total = (proYmen+proYmay);
    cout <<"\t\t\tP(total) = "<< total<<endl;
    if (total> 0.51F){
        cout<<endl<< "\t\t\t\033[1;31m======> Conjunto NO válido...., TEST = X\033[0m"<<endl;
        return 0;
    }else{
        cout<<endl<< "\t\t\t\033[1;32m======> Conjunto válido...., TEST = ok\033[0m"<<endl;
        return 1;
    }

}

double Statistics::cnd_manual(double x) {
  double L, K, w ;
  /* constants */
  double const a1 = 0.31938153, a2 = -0.356563782, a3 = 1.781477937;
  double const a4 = -1.821255978, a5 = 1.330274429;

  L = fabs(x);
  K = 1.0 / (1.0 + 0.2316419 * L);
  w = 1.0 - 1.0 / sqrt(2 * M_PI) * exp(-L *L / 2) * (a1 * K + a2 * K *K + a3 * pow(K,3) + a4 * pow(K,4) + a5 * pow(K,5));

  if (x < 0 ){
    w= 1.0 - w;
  }
  return w;
}