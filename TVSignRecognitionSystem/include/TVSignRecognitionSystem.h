#ifndef TVSIGNRECOGNITIONSYSTEM_H_
#define TVSIGNRECOGNITIONSYSTEM_H_

#include <string>
#include <map>
#include "Template.h"
#include "interface.h"

using namespace std;

class TVSignRecognitionSystem{
public:

	TVSignRecognitionSystem(int top = 1, double threshold = 0.50);

	~TVSignRecognitionSystem();

	void train(const string& trainDataDir, const string& tempDir,
				const string& featureDataDir, const string& indexPath);

	void loadTemplates(const string& trainDataDir);

	void load(const string& trainDataDir, const string& indexPath);

	void match( const string& pathname, const string& featureDataDir,
				  vector<pair<string, double> >& result);

	void print() const{
		cout<< "sum = " << m_sum <<endl;
		cout<< "fail_first_index = " <<  m_fail_first_index <<endl;
		cout<< "fail_second_index = " <<  m_fail_second_index <<endl;
		cout<< "m_fail_first_index_template = " <<  m_fail_first_index_template <<endl;
	}
	
private:
	map<const string, Template*> m_index;
	map<const string, const string> m_invertedIndex;
	Template* m_first_index;
	TvSignMatcher* m_tvSignMatcher;
	double m_threshold;
	int m_top;
	//统计信息
	long m_sum;
	long m_fail_first_index;
	long m_fail_first_index_template;
	long m_fail_second_index;
};

#endif

