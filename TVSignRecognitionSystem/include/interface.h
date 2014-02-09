/*
 * =====================================================================================
 *
 *       Filename:  interface.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/21/2013 03:20:11 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  liangyao (ly), liangyao.ndsl@gmail.com 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */
#ifndef INTERFACE_H
#define INTERFACE_H

#include "matchpic.h"
#include "testtool.h"

class TvSignMatcher
{
public:
    TvSignMatcher(){}
    
    /* *
     * @brief  台标训练 
     *
     * @param trainDataDir 存放训练样本台标的文件夹（全）路径
     * @param featureDataDir 存放样本台标特征数据的文件夹（全）路径
     * @param indexPath 存放索引文件的（全）路径 
     *
     * @return  
     *      - 
     * */ 
    void tvSignTraining(const char* trainDataDir, 
            const char* featureDataDir, const char* indexPath);
    
    /* *
     * @brief  加载索引 
     *
     * @param indexPath 存放索引文件的（全）路径 
     *
     * @return  
     *      - 
     * */ 
    void loadIndex(const char* indexPath);
    
    /* *
     * @brief  台标匹配(单张) 
     *
     * @param matchSignPath 待匹配台标的（全）路径 
     * @param featureDataDir 存放样本台标特征数据的文件夹（全）路径
     * @param result 存放匹配结果的容器(容器中每一项表示匹配到的台标
     * 名称和对应的匹配程度)
     *
     * @return  
     *      - 
     * */ 
    void tvSignMatch(const char* matchSignPath,
            const char* featureDataDir,
            vector<pair<string, double> > &result);
    
    /* *
     * @brief  台标匹配(批量)
     *
     * @param matchDir 待匹配台标的文件夹（全）路径 
     * @param featureDataDir 存放样本台标特征数据的文件夹（全）路径
     * @param resultList 存放匹配结果的容器(容器中每一项表示待匹配
     * 图片的全路径和匹配到的台标名称) 
     *
     * @return  
     *      - 
     * */ 
    void tvSignMatchDir(const char* matchDir,
            const char* featureDataDir,
            vector<pair<string, string> > &resultList);

private:
    TvSignMatcher(const TvSignMatcher &);
    TvSignMatcher& operator = (const TvSignMatcher &);

private:
    VocabularyTree m_vcTree;
};

#endif
