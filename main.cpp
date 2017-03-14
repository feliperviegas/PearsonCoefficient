#include "coef.h"
  
int main(int argc, char** argv) {
    char *dataTrain = NULL;
    int opt, seed = 0;
    double t0, tf, tempo_gasto;
    double utime, stime, total_time;  
    while ((opt = getopt (argc, argv, "d:")) != -1) {
        switch (opt) {
            case 'd': dataTrain = optarg; break;
            case '?':
                if ((optopt == 'd') || (optopt == 't'))
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                std::cerr << "USAGE: " << argv[0] << " -v <val> -i <val>" << std::endl;
                abort ();
				exit(1);
        }
    }

    set<string>vocabulary, classes;
    int Nt;

    map<int, vector<string> > train;
    map<string, int> freq, freqClass;

    readTraining(dataTrain, train, freq, freqClass, Nt, vocabulary, classes);

    for(auto x = vocabulary.begin(); x != vocabulary.end(); ++x){
        for(auto y = vocabulary.begin(); y != vocabulary.end(); ++y){
            cout << *x << " " << *y << " " << Correlation(train, freq, Nt, *x, *y) << endl;
        }
    }
/*
    for(auto x = vocabulary.begin(); x != vocabulary.end(); ++x){
        for(auto y = classes.begin(); y != classes.end(); ++y){
            cout << *x << " " << *y << " " << CorrelationTermClass(train, freq, freqClass, Nt, *x, *y) << endl;
        }
    }
    //cout << "6" << " " << "4" << " " << Correlation(train, freq, Nt, "6", "4") << endl;       
*/  
  return 0;
}

