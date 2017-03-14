#ifndef COEF_H__
#define COEF_H__

#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

void stringTokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters);

void readTraining(const char* filename, map<int, vector<string> >& train, map<string, int>& freq, map<string, int>& freqClass, int& Nt, set<string>& vocabulary, set<string>& classes);

double MeanClass(map<string, int> classFreq, string c, int Nt);

double Mean(map<string, int> freq, string term, int Nt);

double StandardDerivationClass(map<int, vector<string> > train, map<string, int> freqClass, int Nt, string c);

double StandardDerivation(map<int, vector<string> > train, map<string, int> freq, int Nt, string term);

double CorrelationTermClass(map<int, vector<string> > train, map<string, int> freq, map<string, int> freqClass, int Nt, string t, string c);

double Correlation(map<int, vector<string> > train, map<string, int> freq, int Nt, string x, string y);
#endif
