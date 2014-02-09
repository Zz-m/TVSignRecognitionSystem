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


	//加载
	//要提供训练好的索引文件和训练样本目录trainDataDir
	TVSignRecognitionSystem t(num);
	t.load(argv[1], argv[2]);


	//得到matchPathname目录下所以的文件存放在files
	list<string> files;
	getFiles(argv[4], files);

	//遍历目录中的每一个文件然后调用match接口进行匹配
	list<string>::const_iterator it = files.begin();
	for( ; it != files.end(); ++it){
		//匹配
		//提供图片的全路径和特征值文件featureDir
		vector<pair<string, double> > result;
		t.match(*it, argv[3], result);

		cout<< *it << " ";
		//打印结果
		//pair<string, double> string表示结果，double表示概率
		vector<pair<string, double> >::const_iterator it = result.begin();
		for( ; it != result.end(); ++it){
			cout<< it->first << " " << it->second <<" ";
		}
        cout<< endl;
	}

    return 0;
}



