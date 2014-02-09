/*
 * =====================================================================================
 *
 *       Filename:  matchpic.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  9/31/13 01:14:15
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liangyao(ly), liangyao.ndsl@gmail.com
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */

#include"matchpic.h"

int getMatchNum(IpVec &source_ipts,IpVec &match_ipts)
{
    int matchedNum = 0;

    for(int i = 0; i < match_ipts.size(); ++i)
    {
        float d1, d2;
        int index1, index2;

        d1 = d2 = 1024;
        index1 = index2 = 0;

        for(int j = 0; j < source_ipts.size(); ++j)
        {
            float dis = 0;

            for(int k = 0; k < 64; ++k)
            {
                dis += pow(source_ipts.at(j).descriptor[k] - 
                        match_ipts.at(i).descriptor[k], 2);
            }

            dis = sqrt(dis);

            if(dis < d1)
            {
                d2 = d1;
                index2 = index1;
                index1 = j;
                d1 = dis;
            }
            else if(dis < d2)
            {
                d2 = dis;
                index2 = j;
            }
        }

        if(d1 / d2  < 0.75)
        {
            ++ matchedNum;
        }
    }

    return matchedNum;
}

vector<pair<string, double> > matchPic(const char* picname, 
        const char* featureDir, VocabularyTree &vc_tree)
{
    int source_size, match_size, num, sumnum = 0, pos;
    string feafileName, resultName;
    IpVec source_ipts, match_ipts;
    Re_index m_result, t_result;
    Re_index::iterator m_iter, t_iter;
    vector<pair<string, double> > ret;
    Mat s_mat = imread(picname);
    IplImage img = s_mat;

    surfDetDes(&img, source_ipts, false, 4, 4, 2, 0.0004f);
        
    if (source_ipts.empty())
        return ret;
    if (vc_tree.matchPic(source_ipts) == -1)
        return ret;

    vc_tree.getResult(m_result);

    for (m_iter = m_result.begin(); m_iter != m_result.end(); m_iter++)
    {
        match_ipts.clear();
        feafileName.clear();

        feafileName += featureDir;
        if (feafileName[feafileName.size() - 1] != '/')
           feafileName += '/'; 
        feafileName += m_iter->first;
        feafileName += ".feature";
        if (access(feafileName.c_str(), F_OK) == -1)
        {
            cout << "can't access file " << feafileName << endl;
            exit(-1);
        }
            
        loadSurf(feafileName.c_str(), match_ipts);
        source_size = source_ipts.size();
        match_size = match_ipts.size();

        if (match_size < source_size)
           num = getMatchNum(source_ipts, match_ipts);
        else
           num = getMatchNum(match_ipts, source_ipts);

        if (num >= FILTER_NUM)
        {
            sumnum += num;
            pos = (m_iter->first).find("-");
            resultName = (m_iter->first).substr(0, pos); 
            t_iter = t_result.find(resultName);
            if (t_iter == t_result.end())
               t_result.insert(pair<string, double>(resultName, num));
            else
               t_iter->second += num; 
        } 
    }

    for (t_iter = t_result.begin(); t_iter != t_result.end(); t_iter++)
    {
        t_iter->second /= sumnum;
        ret.push_back(pair<string, double>(t_iter->first, t_iter->second));
    } 

    sort(ret.begin(), ret.end(), PairCompare());   

    return ret;
}
