#include <iostream>
#include "../include/TVSignRecognitionSystem.h"

using namespace std;

int main(int argc, char** argv){
    if (argc < 5 || argc > 6){
        cout << "usage:./MATCH trainDataDir indexPath featureDir matchFilePath num" << endl;
        return 0;
    }

    int num = 1;;
    if(argc == 6){
        num = atoi(argv[5]);
    }

	//����
	//Ҫ�ṩѵ���õ������ļ���ѵ������Ŀ¼trainDataDir
	TVSignRecognitionSystem t(num);
	t.load(argv[1], argv[2]);
	
	//ƥ��
	//�ṩͼƬ��ȫ·��������ֵ�ļ�featureDir
	vector<pair<string, double> > result;
	t.match(argv[4], argv[3], result);

	//��ӡ���
	//pair<string, double> string��ʾ�����double��ʾ����
	vector<pair<string, double> >::const_iterator it = result.begin();
    cout<< argv[4] << " ";
	for( ; it != result.end(); ++it){
		cout<< it->first<< " " <<it->second << " ";
	}
    cout<<endl;

    return 0;
}


