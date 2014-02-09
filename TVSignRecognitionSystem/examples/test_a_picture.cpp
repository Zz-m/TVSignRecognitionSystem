#include <iostream>
#include <fstream>
#include <signal.h>
#include <assert.h>
#include <vector>
#include <list>
#include <string>

#include "../include/TVSignRecognitionSystem.h"

using namespace std;

const string getAns(const string& pathname){
        int begin = pathname.find_last_of("/");
        int end = pathname.find_last_of("-"); 
        assert(begin <= end);
        string s(pathname, begin + 1, end - begin - 1);
        return s;
}

int main(){

	TVSignRecognitionSystem t;
	t.train("./trainDataDir", "./tempDir", 
			"./featureDataDir", "./indexFile");
	
	while(1){
		cout<< "Please input full path of a picture: " <<endl;
		string filename;
		cin>> filename;
			
		vector<pair<string, double> > result;
		t.match(filename, "./featureDataDir", result);

		vector<pair<string, double> >::const_iterator it = result.begin();
		for( ; it != result.end(); ++it){
			cout<< it->first<< " : " <<it->second <<endl;
		}
		cout<< endl;
	}

	return 0;
}

