#ifndef TVSIGNRECOGNITIONSYSTEM_H_
#define TVSIGNRECOGNITIONSYSTEM_H_

#include <string>
#include <map>
#include "Template.h"
#include "interface.h"

using namespace std;

class TVSignRecognitionSystem{
public:

	TVSignRecognitionSystem(int top = 1, double threshold = 0.10);

	~TVSignRecognitionSystem();

	void train(const string& trainDataDir, const string& tempDir,
				const string& featureDataDir, const string& indexPath);

	

	void load(const string& trainDataDir, const string& indexPath);

	void match( const string& pathname, const string& featureDataDir,
				  vector<pair<string, double> >& result);
	
private:
	void loadTemplates(const string& trainDataDir);
	
	map<const string, Template*> m_index;
	map<const string, const string> m_invertedIndex;
	Template* m_first_index;
	TvSignMatcher* m_tvSignMatcher;
	double m_threshold;
	int m_top;
};

#endif

