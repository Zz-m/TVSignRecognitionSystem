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

	//加载
	//要提供训练好的索引文件和训练样本目录trainDataDir
	TVSignRecognitionSystem t(num);
	t.load(argv[1], argv[2]);
	
	//匹配
	//提供图片的全路径和特征值文件featureDir
	vector<pair<string, double> > result;
	t.match(argv[4], argv[3], result);

	//打印结果
	//pair<string, double> string表示结果，double表示概率
	vector<pair<string, double> >::const_iterator it = result.begin();
    cout<< argv[4] << " ";
	for( ; it != result.end(); ++it){
		cout<< it->first<< " " <<it->second << " ";
	}
    cout<<endl;

    return 0;
}


