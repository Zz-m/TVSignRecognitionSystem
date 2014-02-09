/*
 * =====================================================================================
 *
 *       Filename:  interface.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/21/2013 03:37:57 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liangyao(ly), liangyao.ndsl@gmail.com 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */

#include "interface.h"

void TvSignMatcher::tvSignTraining(const char* trainDataDir,
        const char* featureDataDir, const char* indexPath)
{
    if (access(indexPath, F_OK) == 0)
    {
        cout << "index already exsit" << endl;
        return;
    }
    
    m_vcTree.training(trainDataDir, featureDataDir);
    ofstream outFile(indexPath);
    m_vcTree.writeVocabularyTree(outFile);
}

void TvSignMatcher::loadIndex(const char* indexPath)
{
    if (access(indexPath, F_OK) == -1)
    {
        cerr << "index not exist" << endl;
        exit(-1);
    }

    ifstream inFile(indexPath);
    m_vcTree.readVocabularyTree(inFile);
}

void TvSignMatcher::tvSignMatch(const char* matchSignPath, 
        const char* featureDataDir, 
        vector<pair<string, double> > &result)
{
    result.clear(); 
    result = matchPic(matchSignPath, featureDataDir, m_vcTree);
}

void TvSignMatcher::tvSignMatchDir(const char* matchDir,
        const char* featureDataDir,
        vector<pair<string, string> > &resultList)
{
    assert(resultList.empty());
    string fileName, matchName;
    list<string> fileNameList;
    list<string>::iterator iter;
    vector<pair<string, double> > result;

    TestTool::getFilenameList(fileNameList, matchDir);
    for (iter = fileNameList.begin(); iter != fileNameList.end();
            iter++)
    {
        fileName = *iter;
        tvSignMatch(fileName.c_str(), featureDataDir, result);
        if (result.empty())
            matchName = "";
        else
            matchName = result[0].first;
        
        resultList.push_back(pair<string, string> 
                (fileName, matchName));
    }
}
