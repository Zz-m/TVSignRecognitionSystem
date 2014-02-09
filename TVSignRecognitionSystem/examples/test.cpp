#include <sys/time.h>
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

	ofstream ff("failed.txt");
	ofstream fe("error.txt");
	ofstream fr("result.txt");
	
	int sss = 0;
	int ok1 = 0;
	int ok2 = 0;
	int fai = 0;
	int err = 0;
	bool tag = false;

	//ÑµÁ·¿ªÊ¼
	//struct timeval train_start;
	//gettimeofday(&train_start, NULL);

	TVSignRecognitionSystem t;
	t.train("./trainDataDir", "./tempDir", 
			"./featureDataDir", "./indexFile");

	//ÑµÁ·½áÊø
	//struct timeval train_end;
	//gettimeofday(&train_end, NULL);

	list<string> files;
	//getFiles("/home/FINAL/SmallTestSet", files);
	getFiles("./TestSet", files);
	list<string>::const_iterator it = files.begin();
	list<string>::const_iterator it_end = files.end();

	//Æ¥Åä¿ªÊ¼
	//struct timeval match_start;
	//gettimeofday(&match_start, NULL);
	
	for( ; it != it_end; ++it){
		cout<< *it <<endl;
		const string ans = getAns(*it);
					
		++sss;
		
		vector<pair<string, double> > result;
		t.match(*it, "./featureDataDir", result);
		if(result.empty() == true){
			++fai;
			ff<< *it <<endl;
			cout<< "[FAILED]" <<endl<<endl;
		}
		else{
			if(result.begin()->first == ans){
				++ok1;
				cout<< "[OK]" << result.begin()->first << " " << result.begin()->second <<endl<<endl;
			}
			else{
				
				tag = false;
				
				for(	vector<pair<string, double> >::iterator j = result.begin(); 
						j != result.end(); ++j){
					if(j->first == ans){
						++ok2;
						cout<< "[OK SECOND]\t" << j->first << " " << j->second <<endl<<endl;
						tag = true;
						break;
					}
				}
						
				if(tag == false){
					++err;
					cout<< "[ERROR]" <<endl<<endl;
					
					fe<< *it <<endl;
					for(	vector<pair<string, double> >::iterator k = result.begin(); 
						k != result.end(); ++k){
						fe<< k->first << "\t" << k->second <<endl<<endl;
					}
					fe<<endl;
				}
			}
		}
	}

	//Æ¥Åä½áÊø
	//struct timeval match_end;
	//gettimeofday(&match_end, NULL);

	fr<< sss <<endl;
	fr<< ok1 <<endl;
	fr<< ok2 <<endl;
	fr<< fai <<endl;
	fr<< err <<endl;

	fr<< (ok1 + ok2) / (float)sss<<endl;
	fr<< fai / (float)sss<<endl;
	fr<< err / (float)sss<<endl;

	//fr<< train_end.tv_sec - train_start.tv_sec <<endl;
	//fr<< match_end.tv_sec - match_start.tv_sec <<endl;
	//fr<< (match_end.tv_sec - match_start.tv_sec) / (float)files.size() <<endl;
	
	return 0;
}

