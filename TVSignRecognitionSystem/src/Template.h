#ifndef TEMPLATE_H_
#define TEMPLATE_H_

#include "Template.h"
#include <string>
#include <list>
#include <vector>
#include <utility>
#include <algorithm>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void getFiles(const string& path, list<string>& files);
void getDirs(const string& path, list<string>& dirs);
const string getLastName(const string& src);

struct pair_compare_fun_object{
   	bool operator() (const pair<string, double>& left, const pair<string, double>& right){
        return left.second > right.second;
    }
};

class Template{
public:
	Template(int top = 3, double threshold = 0.60);
	~Template();
	
	void setThreshold(double threshold);
	void load(const string& pathname);
	void load_template(const string& pathname);
	void match(const string& pathname, 
				  vector<pair<string, double> >& result){

		vector<pair<string, double> > first_result;
		map<string, double> temp;
		map<string, double>::iterator it;
		
		Mat image;
		image = imread(pathname.c_str());
		CV_Assert(image.data != NULL);
				  
		double* max_value = new double[m_templates.size()];
		int* tag = new int[m_templates.size()];
		CV_Assert(max_value != NULL);
				  
		for(size_t i = 0; i < m_templates.size(); ++i){
			Mat temp;
			cv::matchTemplate(image, m_templates[i], temp, CV_TM_CCOEFF_NORMED);
			cv::minMaxLoc(temp, NULL, &(max_value[i]), NULL, NULL);	
			tag[i] = 0;
		}
				  
		for(size_t t = 0; t < m_top; ++t){
			size_t index = 0;
			double value = 0;
			for(size_t i = 0; i < m_templates.size(); ++i){
				if(tag[i] == 0 && max_value[i] > value){
					value = max_value[i];
					index = i;
				}
			}
				  
			tag[index] = 1;
				  
			if(value >= m_threshold){
				it = temp.find(m_names[index]);
				if(it == temp.end()){
					temp.insert(make_pair(m_names[index], value));
				}
				else{
					it->second += value;
				}
			}
		}

		//对匹配度进行归一化
		double s = 0.0;
		map<string, double>::const_iterator iter = temp.begin();
		for( ; iter != temp.end(); ++iter){
			s += iter->second;
		}

		
		iter = temp.begin();
		for( ; iter != temp.end(); ++iter){
			result.push_back(make_pair(iter->first, iter->second / s));
		}

		
		//对结果进行排序
		sort(result.begin(), result.end(), pair_compare_fun_object());

		delete[] max_value;
		delete[] tag;
	}
	
	
private:
	vector<Mat> m_templates;
	vector<string> m_names;
	double m_threshold;
	int m_top;
};

#endif
