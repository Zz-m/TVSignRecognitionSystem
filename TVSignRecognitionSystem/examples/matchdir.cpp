#include <iostream>
#include "../include/TVSignRecognitionSystem.h"

using namespace std;

int main(int argc, char** argv){
    if (argc < 5 || argc > 6){
        cout << "usage:./MATCH trainDataDir indexPath featureDir matchPathname num" << endl;
        return 0;
    }

    int num = 1;
    if(argc == 6){
        num = atoi(argv[5]);
    }


	//����
	//Ҫ�ṩѵ���õ������ļ���ѵ������Ŀ¼trainDataDir
	TVSignRecognitionSystem t(num);
	t.load(argv[1], argv[2]);


	//�õ�matchPathnameĿ¼�����Ե��ļ������files
	list<string> files;
	getFiles(argv[4], files);

	//����Ŀ¼�е�ÿһ���ļ�Ȼ�����match�ӿڽ���ƥ��
	list<string>::const_iterator it = files.begin();
	for( ; it != files.end(); ++it){
		//ƥ��
		//�ṩͼƬ��ȫ·��������ֵ�ļ�featureDir
		vector<pair<string, double> > result;
		t.match(*it, argv[3], result);

		cout<< *it << " ";
		//��ӡ���
		//pair<string, double> string��ʾ�����double��ʾ����
		vector<pair<string, double> >::const_iterator it = result.begin();
		for( ; it != result.end(); ++it){
			cout<< it->first << " " << it->second <<" ";
		}
        cout<< endl;
	}

    return 0;
}



