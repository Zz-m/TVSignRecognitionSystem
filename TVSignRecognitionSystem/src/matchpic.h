/*
 * =====================================================================================
 *
 *       Filename:  matchpic.h
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

#ifndef PICMATCH_H
#define PICMATCH_H

#include "vocabularytree.h"
#define FILTER_NUM 6 

vector<pair<string, double> > matchPic(const char* picname, 
        const char* featureDir, VocabularyTree &vc_tree);
int getMatchNum(IpVec &source_ipts, IpVec &match_ipts);

#endif
