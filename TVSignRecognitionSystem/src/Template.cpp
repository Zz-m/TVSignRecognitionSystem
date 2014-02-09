#include "Template.h"
#include <boost/filesystem.hpp>

using namespace boost;

void getFiles(const string& path, list<string>& files){
	filesystem::directory_iterator it_end;
	filesystem::directory_iterator it(path);
	for( ; it != it_end; ++it){
		if(filesystem::is_directory(*it) == 0){
			string file;
			file = (*it).path().string();
			files.push_back(file);
		}
	}
}

void getDirs(const string& path, list<string>& dirs){
	filesystem::directory_iterator it_end;
	filesystem::directory_iterator it(path);
	for( ; it != it_end; ++it){
		if(filesystem::is_directory(*it) != 0){
			string file;
			file = (*it).path().string();
			dirs.push_back(file);
		}
	}
}

const string getLastName(const string& src){
	int end = src.find_last_not_of("/");
	const string s(src, 0, end + 1);

	int begin = s.find_last_of("/");
	const string dst(s, begin + 1, s.size() - begin - 1);
	return dst;
}


Template::Template(int top, double threshold)
	: m_top(top), m_threshold(threshold){
	assert(m_threshold >=0 && m_threshold <= 1);
}

Template::~Template(){
}

void Template::setThreshold(double threshold){
	m_threshold = threshold;
	assert(m_threshold >=0 && m_threshold <= 1);
}

void Template::load(const string& pathname){

	int count = 0;

	list<string> dirs;
	getDirs(pathname, dirs);

	list<string>::const_iterator it = dirs.begin();
	for( ; it != dirs.end(); ++it){
		
		list<string> files;
		getFiles(*it, files);
		
		if( getLastName(*it) == "template"){
			continue;
		}
		++count;
			
		list<string>::const_iterator iter = files.begin();
		for( ; iter != files.end(); ++iter){
			
			Mat image = imread(*iter);
			CV_Assert(image.data != NULL);

			m_templates.push_back(image);
			m_names.push_back(getLastName(*it));
		}
	}

	//处理top越界
	if(m_top <= 0){
		m_top = 1;
	}
	else if(m_top > count){
		m_top = count;
	}
	else{
		//Reasonable range
	}
	
}

void Template::load_template(const string& pathname){
	list<string> dirs;
	getDirs(pathname, dirs);

	list<string>::const_iterator it = dirs.begin();
	for( ; it != dirs.end(); ++it){
		
		list<string> files;
		getFiles(*it + "/" + "template", files);
			
		list<string>::const_iterator iter = files.begin();
		for( ; iter != files.end(); ++iter){
			Mat image = imread(*iter);
			CV_Assert(image.data != NULL);

			m_templates.push_back(image);
			m_names.push_back(getLastName(*it));
		}
	}

	//处理top越界
	if(m_top <= 0){
		m_top = 1;
	}
	else if(m_top > dirs.size()){
		m_top = dirs.size();
	}
	else{
		//Reasonable range
	}
}
