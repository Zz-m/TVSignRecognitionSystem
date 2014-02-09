/*
 * =====================================================================================
 *
 *       Filename:  testtool.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/23/2013 08:04:32 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liangyao (ly), liangyao.ndsl@gmail.com 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */

#include"testtool.h"

void TestTool::getFilenameList(
        std::list<std::string> &fileNameList, 
        std::string dirname)
{
    DIR *dp;
    struct dirent *dirp;

    std::string filename;
    if (dirname[dirname.size() - 1] != '/')
        dirname += "/";
    
    if ((dp = opendir(dirname.c_str())) == NULL)
    {
        std::cerr << "can't open dir :" << dirname << std::endl;
        exit(-1);
    }  
    
    while ((dirp = readdir(dp)) != NULL)
    {
        filename.clear();
        std::string tempStr = dirp->d_name; 
  
        if (strcmp(tempStr.c_str(),".") == 0 || 
                strcmp(tempStr.c_str(), "..") == 0)
            continue;
        
        filename += dirname;
        filename += tempStr;
        fileNameList.push_back(filename); 
    }    
}

std::string TestTool::getFilename(std::string path)
{
    int begin_pos = path.rfind("/");
    if (begin_pos == -1)
        return path;

    int end_pos = path.size();
    std::string filename = path.substr(begin_pos + 1, 
            end_pos - begin_pos + 1);

    return filename;
}

std::string getPrefix(std::string filename)
{
    int pos = filename.find("_");
    std::string ret = filename.substr(0, pos);
    
    return ret;
}

bool TestTool::samePrefix(std::string path1, std::string path2)
{
    std::string str1,str2;
    str1 = getFilename(path1);
    str2 = getFilename(path2);
    
    std::string prefix1,prefix2;
    prefix1 = getPrefix(str1);
    prefix2 = getPrefix(str2);

    if(prefix1 == prefix2)
        return true;
    else
        return false;
}

void TestTool::setBeginMoment()
{
    gettimeofday(&time_begin, NULL);
}

void TestTool::setEndMoment()
{
    gettimeofday(&time_end, NULL);
}

long TestTool::getTime()
{
    long time = (time_end.tv_sec*1000*1000 + time_end.tv_usec) - 
            (time_begin.tv_sec*1000*1000 + time_begin.tv_usec);
    
    return time/1000;
}
