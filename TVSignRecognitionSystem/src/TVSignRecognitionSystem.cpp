#include <stdlib.h>
#include "TVSignRecognitionSystem.h"

TVSignRecognitionSystem::TVSignRecognitionSystem(int top, double threshold) 
	: m_top(top), m_threshold(threshold){
	m_tvSignMatcher = new TvSignMatcher();
	/*
		Ϊ�����ɹ�����С�����ʣ�һ��ģ��ķ�ֵΪ0.6
	*/
	m_first_index = new Template(m_top, 0.60);
}

TVSignRecognitionSystem::~TVSignRecognitionSystem(){

	map<string, Template*>::iterator it = m_index.begin();
	for( ; it != m_index.end(); ++it){
		if(NULL != it->second){
			delete it->second;
		}
		it->second = NULL;
	}

	if(NULL != m_tvSignMatcher){
		delete m_tvSignMatcher;
	}
	
	if(NULL != m_first_index){
		delete m_first_index;
	}
}

void TVSignRecognitionSystem::train(const string& trainDataDir, const string& tempDir,
				const string& featureDataDir, const string& indexPath){
	//0.1	��������ļ�����ֱ�Ӽ���֮

    if (access(indexPath.c_str(), F_OK) == 0){
        cout << "[INFO]Vocabulary tree already exists......" << endl;
		m_tvSignMatcher->loadIndex(indexPath.c_str());//���شʻ���
		cout<< "[INFO]Vocabulary tree loaded successfully......" <<endl;
		
		loadTemplates(trainDataDir);//����ģ��
		cout<< "[INFO]Templates loaded successfully......" <<endl;

		return;
    }
	
	//0.2 	��ʱĿ¼�������
	//0.3	��ʱĿ¼����Ϊ��
	if(access(tempDir.c_str(), F_OK) != 0){
		cerr<< "[ERROR]Temporary folder must be create by manual." <<endl;
		exit(0);
	}
	
	list<string> test_files;
	getFiles(tempDir, test_files);
	if(test_files.size() != 0){
		cerr<< "[ERROR]Temporary folder could't have any temporary files."<<endl;
		exit(0);
	}
		
	//1. ��trainDataDirѵ���������Ƶ�tempDir
	list<string> dirs;
	getDirs(trainDataDir, dirs);
	list<string>::const_iterator it = dirs.begin();
	for( ; it != dirs.end(); ++it){
		list<string> files;
		getFiles(*it, files);
		list<string>::const_iterator iter = files.begin();
		for( ; iter != files.end(); ++iter){
			int ret = ::system(("cp " + *iter + " " + tempDir).c_str());
			assert(ret != -1);
		}
	}

	//2. ѵ��һ������[�ʻ���]
	m_tvSignMatcher->tvSignTraining(tempDir.c_str(), featureDataDir.c_str(), indexPath.c_str());
	cout<< "[INFO]Vocabulary tree trained successfully......" <<endl;
	cout<< "[INFO]Vocabulary tree loaded successfully......" <<endl;

	//2.1 ����
	//cout<< "[DEBUG]\tm_first_index->load_template(trainDataDir);" <<endl;
	m_first_index->load_template(trainDataDir);

	//3. ���ض�������[ģ��]
	loadTemplates(trainDataDir);
	cout<< "[INFO]Templates loaded successfully......"  <<endl;
}

void TVSignRecognitionSystem::loadTemplates(const string& trainDataDir){
	
	//2.1 ����һ������[ģ��]
	//cout<< "[DEBUG]\tm_first_index->load_template(trainDataDir);" <<endl;
	m_first_index->load_template(trainDataDir);

	list<string> dirs;
	getDirs(trainDataDir, dirs);
	list<string>::const_iterator it = dirs.begin();

	//2.2 ���ض�������[ģ��]

	//cout<< "-------------"<<endl<<endl;;
	//cout<< dirs.size() <<endl;
	//cout<< "-------------"<<endl<<endl;;
	
	for( ; it != dirs.end(); ++it){
		list<string> subDirs;
		getDirs(*it, subDirs);
		//cout<< getLastName(*it) <<endl;
		if(subDirs.size() > 1){
			Template* t = NULL;
			/*
				Ϊ�˼򻯣�����ģ��ֻ����ǰ1�����
			*/
			t = new Template(1, m_threshold);
			t->load(*it);

			//cout<< "=========================="<<endl;
			//cout<< *it <<endl;
			//cout<< "=========================="<<endl;

			m_invertedIndex.insert(make_pair(getLastName(*it), getLastName(*it)));

			list<string>::const_iterator iter = subDirs.begin();
			for( ; iter != subDirs.end(); ++iter){
				//cout<< "\t*iter = "<<*iter <<endl;
				if( getLastName(*iter) == "template"){
					continue;
				}
				//cout<< "\t"<<getLastName(*iter) <<endl;
				m_invertedIndex.insert(make_pair(getLastName(*iter), getLastName(*it)));
			}
			m_index.insert(make_pair(getLastName(*it), t));
		}
	}
}

void TVSignRecognitionSystem::load(const string& trainDataDir, const string& indexPath){
	m_tvSignMatcher->loadIndex(indexPath.c_str());
	loadTemplates(trainDataDir);
}

void TVSignRecognitionSystem::match(  const string& pathname, 
										const string& featureDataDir,
										vector<pair<string, double> >& result){
	//�ж���ӦĿ¼�Ƿ����
	int ret;
	ret = access(pathname.c_str() , F_OK);
	if(ret < 0){
		cerr<< "[ERROR] access error for " << pathname <<endl;
		return;
	}

	vector<pair<string, double> > first_result;
	vector<pair<string, double> > second_result;

	m_tvSignMatcher->tvSignMatch(pathname.c_str(), featureDataDir.c_str(), first_result);

	if(first_result.empty() == true){
		//[�ʻ���]ʧ�ܺ�һ������[ģ��]
		m_first_index->match(pathname, second_result);

		//һ������[ģ��]ʧ��
		if(second_result.empty() == true){
			return ;
		}
	}
	else{
		//�ϲ�[�ʻ���]�����ظ�̨��ĸ���
		map<string, double> temp;
		
		vector<pair<string, double> >::const_iterator i = first_result.begin();
		for( ; i != first_result.end(); ++i){

			map<const string, const string>::const_iterator j;
			j = m_invertedIndex.find(i->first);
			if(j != m_invertedIndex.end()){
				map<string, double>::iterator k;
				k = temp.find(j->second);
				if(k == temp.end()){
					temp.insert(make_pair(j->second, i->second));
				}
				else{
					k->second += i->second;
				}
			}
			else{
				temp.insert(make_pair(i->first, i->second));
			}
		}

		map<string, double>::const_iterator m = temp.begin();
		for( ; m != temp.end(); ++m){
			second_result.push_back(make_pair(m->first, m->second));
			//cout<< m->first << " " << m->second <<endl;
		}
	}
	
	//����
	sort(second_result.begin(), second_result.end(), pair_compare_fun_object());
 
	//�߶�������[ģ��]
	vector<pair<string, double> >::const_iterator it = second_result.begin();
	for( ; it != second_result.end(); ++it){
		map<const string, Template*>::iterator n;
		n = m_index.find(it->first);

		vector<pair<string, double> > third_result;
		if(n != m_index.end()){
			//��, CCTV�Ƶ�CCTV��̨
			n->second->match(pathname, third_result);
			if(third_result.empty() == true){
				//�ʻ�������һ��ģ�巵�صĽ������
			}
			else{
				//ֻ�õ�һ��ȥ�滻
				result.push_back(make_pair(third_result[0].first, it->second));
			}
		}
		else{
			//��, ahnhui ���ö�������[ģ��]����
			result.push_back(make_pair(it->first, it->second));
		}
	}

}
