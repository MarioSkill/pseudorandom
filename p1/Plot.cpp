#include "Plot.h"
Plot::Plot(){}
Plot::~Plot(){}
void Plot::Graficar(std::vector<float> n,string name){
	//char * commandsForGnuplot[] = {"set title \"Grafica\"", "plot 'pseudonumber'"};
	string commandsForGnuplot[]={"set title \"Grafica\"", "plot '"+name+"'"};
	int xvals[n.size()];
	float yvals[n.size()];

	int i =0;
	for (vector<float>::iterator it=n.begin(); it!=n.end(); ++it){
		xvals[i]=(i+1);
		yvals[i]=*it;
		i++;
	}

	     //= {5.0 ,3.0, 1.0, 3.0, 5.0};
	FILE * temp = fopen(name.c_str(), "w");
	    /*Opens an interface that one can use to send commands as if they were typing into the
	     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
	     *     C program terminates.
	     */
	FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
	//i=0;
	int max= n.size();
	for (i=0; i < max; i++) {
	    	fprintf(temp, "%d %lf \n", xvals[i], yvals[i]); //Write the data to a temporary file
	    }

	    for (i=0; i < NUM_COMMANDS; i++) {
	    	fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i].c_str()); //Send commands to gnuplot one by one.
	    }
	}


void Plot::Graficar(std::vector<int> n, string name){
	//char * commandsForGnuplot[] = {"set title \"Grafica\"", "plot 'pseudonumber'"};
	string commandsForGnuplot[]={"set title \"Grafica\"", "plot '"+name+"'"};
	int xvals[n.size()];
	int yvals[n.size()];

	int i =0;
	for (vector<int>::iterator it=n.begin(); it!=n.end(); ++it){
		xvals[i]=(i+1);
		yvals[i]=*it;
		i++;
	}

	     //= {5.0 ,3.0, 1.0, 3.0, 5.0};
	FILE * temp = fopen(name.c_str(), "w");
	    /*Opens an interface that one can use to send commands as if they were typing into the
	     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
	     *     C program terminates.
	     */
	FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
	//i=0;
	int max= n.size();
	for (i=0; i < max; i++) {
	    	fprintf(temp, "%d %d \n", xvals[i], yvals[i]); //Write the data to a temporary file
	    }

	    for (i=0; i < NUM_COMMANDS; i++) {
	    	fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i].c_str()); //Send commands to gnuplot one by one.
	    }
	}
void Plot::Graficar(std::map <float, float> n,string name){
	//char * commandsForGnuplot[] = {"set title \"Grafica\"", "plot 'pseudonumber'"};
	string commandsForGnuplot[]={"set title \"Grafica\"", "plot '"+name+"'"};
	float xvals[n.size()];
	float yvals[n.size()];

	int i =0;
	for (std::map <float, float>::iterator it=n.begin(); it!=n.end(); ++it){
		 
		
		xvals[i]=it->first;
		yvals[i]=it->second;
		i++;
	}

	     //= {5.0 ,3.0, 1.0, 3.0, 5.0};
	FILE * temp = fopen(name.c_str(), "w");
	    /*Opens an interface that one can use to send commands as if they were typing into the
	     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
	     *     C program terminates.
	     */
	FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
	//i=0;
	i--;
	int max= i;//n.size();
	for (i=0; i < max; i++) {
	    	fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]); //Write the data to a temporary file
	    }

	    for (i=0; i < NUM_COMMANDS; i++) {
	    	fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i].c_str()); //Send commands to gnuplot one by one.
	    }
	}
	
void Plot::Graficar(std::map <float, int> n,string name){
	//char * commandsForGnuplot[] = {"set title \"Grafica\"", "plot 'pseudonumber'"};
	string commandsForGnuplot[]={"set title \"Grafica\"", "plot '"+name+"'"};
	float xvals[n.size()];
	float yvals[n.size()];

	int i =0;
	for (std::map <float, int>::iterator it=n.begin(); it!=n.end(); ++it){
		 
		
		xvals[i]=it->first;
		yvals[i]=it->second;
		i++;
	}

	     //= {5.0 ,3.0, 1.0, 3.0, 5.0};
	FILE * temp = fopen(name.c_str(), "w");
	    /*Opens an interface that one can use to send commands as if they were typing into the
	     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
	     *     C program terminates.
	     */
	FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
	//i=0;
	i--;
	int max= i;//n.size();
	for (i=0; i < max; i++) {
	    	fprintf(temp, "%lf %lf \n", xvals[i], yvals[i]); //Write the data to a temporary file
	    }

	    for (i=0; i < NUM_COMMANDS; i++) {
	    	fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i].c_str()); //Send commands to gnuplot one by one.
	    }
	}