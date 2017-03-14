#include "coef.h"

void stringTokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters){
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);
    while (std::string::npos != pos || std::string::npos != lastPos){
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}


void readTraining(const char* filename, map<int, vector<string> >& train, map<string, int>& freq, map<string, int>& freqClass, int& Nt, set<string>& vocabulary, set<string>& classes){
    std::ifstream file(filename);
    std::string line;
    Nt = 0;
    if(file){
        while (file >> line){
            vector<std::string>tokens;
            stringTokenize(line, tokens, ";");
            int id = atoi(tokens[0].c_str());
            Nt ++;
            string c = tokens[2];
            classes.insert(c);
            if(freqClass.find(c) == freqClass.end()){
                freqClass[c] =0;
            }
            freqClass[c] ++;
            for(int i = 3; i < tokens.size(); i = i + 2){
                string term = tokens[i];
                int freqTerm = atoi(tokens[i+1].c_str());
                vocabulary.insert(term);
                if(freq.find(term) == freq.end()){
                    freq[term] = 0;
                }
                freq[term] += freqTerm;
            }
            tokens.erase(tokens.begin(), tokens.begin()+2);
            train[id] = tokens;
            //for(int i = 0; i <= tokens.size(); i = i + 2){
            //    cout << tokens[i] << "\t" << tokens[i+1] << "\t";
            //}
            //cout << endl;
        }
        file.close();
    }
    else
	{
		std::cout << "Error while opening vertex file." << std::endl;
        exit(1);
    }
 }

double MeanClass(map<string, int> classFreq, string c, int Nt){
    return ((double) classFreq[c])/Nt;
}

double Mean(map<string, int> freq, string term, int Nt){
    return ((double) freq[term])/Nt;
}

double StandardDerivationClass(map<int, vector<string> > train, map<string, int> freqClass, int Nt, string c){
    string t_class;
    double pos, var = 0.0;
    double mean = MeanClass(freqClass, c, Nt);
    for(auto it = train.begin(); it != train.end(); ++it){
        t_class = it->second[0];
        if(c.compare(t_class) == 0){
            pos = pow(1.0 - mean , 2);      
        }      
        else{
            pos = pow(mean, 2);
        }
        var += pos;
    }
    return sqrt(var/Nt);
}

double StandardDerivation(map<int, vector<string> > train, map<string, int> freq, int Nt, string term){
    string t_term;
    double pos, var = 0.0;
    double mean = Mean(freq, term, Nt);
    for(auto it = train.begin(); it != train.end(); ++it){
        pos = pow(mean, 2);
        for(int i = 1; i < it->second.size(); i = i + 2){
            t_term = it->second[i];
            if(term.compare(t_term) == 0){
                pos = pow( (atoi(it->second[i+1].c_str()) - mean) , 2);
            }
        }
        var += pos;
    }
    return sqrt(var/Nt);
}

double CorrelationTermClass(map<int, vector<string> > train, map<string, int> freq, map<string, int> freqClass, int Nt, string t, string c){
    double mean_t = Mean(freq, t, Nt),
            mean_c = MeanClass(freqClass, c, Nt),
            sd_t = StandardDerivation(train, freq, Nt, t),
            sd_c = StandardDerivationClass(train, freqClass, Nt, c),
            corr = 0.0, pos_t, pos_c;
    string t_term, t_class;
    for(auto it = train.begin(); it != train.end(); ++it){
        pos_t = mean_t;
        t_class = it->second[0];
        if(c.compare(t_class) == 0){
            pos_c = 1 - mean_c;
        }
        else{
            pos_c = mean_c;
        }
        for(int i = 1; i < it->second.size(); i = i + 2){
            t_term = it->second[i];
            if(t.compare(t_term) == 0){
                pos_t = atoi(it->second[i+1].c_str()) - mean_t;
            }
        }
        corr += (pos_t/sd_t)*(pos_c/sd_c);
    }
    return corr/(Nt);       
}

//1/n * sum ((xi - x_b)/sd_x)*((yi - y_b)/sd_y)
double Correlation(map<int, vector<string> > train, map<string, int> freq, int Nt, string x, string y){
    double mean_x = Mean(freq, x, Nt),
            mean_y = Mean(freq, y, Nt),
            sd_x = StandardDerivation(train, freq, Nt, x),
            sd_y = StandardDerivation(train, freq, Nt, y),
            corr = 0.0, pos_x, pos_y;
    string t_term;
    for(auto it = train.begin(); it != train.end(); ++it){
        pos_x = mean_x;
        pos_y = mean_y;
        for(int i = 1; i < it->second.size(); i = i + 2){
            t_term = it->second[i];
            if(x.compare(t_term) == 0){
                pos_x = atoi(it->second[i+1].c_str()) - mean_x;
            }
            if(y.compare(t_term) == 0){
                pos_y = atoi(it->second[i+1].c_str()) - mean_y;
            }
        }
        corr += (pos_x/sd_x)*(pos_y/sd_y);
    }
    return corr/(Nt);       
}
