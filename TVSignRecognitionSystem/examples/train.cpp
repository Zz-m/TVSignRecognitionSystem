#include <iostream>
#include "../include/TVSignRecognitionSystem.h"

using namespace std;

int main(int argc, char** argv){
    if (argc != 5){
        cout << "usage:./TRAIN trainDataDir tempDir featureDir indexPath" << endl;
        return 0;
    }
	
	//ѵ��
	//��Ҫ�ṩ����·��
	//1. ѵ������Ŀ¼
	//2. ��ʱĿ¼
	//3. ����ֵĿ¼
	//4. �����ļ���ŵ�·���Լ������ļ���
    TVSignRecognitionSystem  t;
    t.train(argv[1], argv[2], argv[3], argv[4]);

    return 0; 
} 
