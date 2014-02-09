#include <iostream>
#include "../include/TVSignRecognitionSystem.h"

using namespace std;

int main(int argc, char** argv){
    if (argc != 5){
        cout << "usage:./TRAIN trainDataDir tempDir featureDir indexPath" << endl;
        return 0;
    }
	
	//训练
	//需要提供以下路径
	//1. 训练样本目录
	//2. 临时目录
	//3. 特征值目录
	//4. 索引文件存放的路径以及索引文件名
    TVSignRecognitionSystem  t;
    t.train(argv[1], argv[2], argv[3], argv[4]);

    return 0; 
} 
