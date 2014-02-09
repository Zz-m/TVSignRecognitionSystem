/*
 * =====================================================================================
 *
 *       Filename:  k_means.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/05/12 00:19:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:   liangyao(ly), liangyao.ndsl@gmail.com 
 *        Company:  NDSL UESTC
 *
 * =====================================================================================
 */

#include"k_means.h"

Kmeans::Kmeans(int branch):m_branch(branch),m_iterTime(ITER_TIMES),
   ipts(NULL) 
{
    m_clusters = new IpVec*[branch];
    memset(m_clusters, 0, branch * sizeof(IpVec*));

    for (int i = 0; i < branch; i++)
        m_clusters[i] = new IpVec;
}

float Kmeans::getDistance(Ipoint &ip1, Ipoint &ip2)  
{
    return  ip1 - ip2;
}

void Kmeans::setData(IpVec *ipts)
{
    this->ipts = ipts;
}

void Kmeans::initCenters()    
{
    m_centers.clear();
    srand((int)time(NULL));
    
    //random_shuffle(ipts->begin(),ipts->end());
    for (int i = 0; i < m_branch; i++)
        m_centers.push_back(ipts->at( rand() % ipts->size()));
}

void Kmeans::assignToClusters()   
{
    for (int i = 0; i < m_branch; i++)
       m_clusters[i]->clear();

    int bestIndex;
    float bestDist, currentDist;
    Ipoint ip;

    for (int i = 0; i < ipts->size(); i++)
    {
        bestDist = FLT_MAX;
        bestIndex = 0;
        ip = ipts->at(i);

        for (int j = 0; j < m_branch; j++)
        {
            currentDist = getDistance(ip, m_centers[j]);
            if (currentDist < bestDist)
            {
                bestDist = currentDist;
                bestIndex = j; 
            }
        } 
        ip.clusterIndex = bestIndex;
        m_clusters[bestIndex]->push_back(ip);
    }
}

void Kmeans::updataCenters()   
{
    int cluster_size;
    double x, y, dx, dy;
    double sum_descriptor[64];

    for (int i = 0; i < m_branch; i++)
    {
        x = y = dx = dy = 0;
        memset(sum_descriptor, 0, sizeof(double) * 64);
        cluster_size = m_clusters[i]->size(); 
        
        if (cluster_size <= 0)
        {   
            continue;
            //cout << "cluster null" << endl;
        }
        
        for (int j = 0; j < cluster_size; j++)
        {
             Ipoint ip = m_clusters[i]->at(j);
             x += ip.x;
             y += ip.y;
             dx += ip.dx;
             dy += ip.dy;
             for (int k = 0; k < 64; k++)
                sum_descriptor[k] += ip.descriptor[k];
        }

        m_centers[i].x = x/cluster_size;
        m_centers[i].y = y/cluster_size;
        m_centers[i].dx = dx/cluster_size;
        m_centers[i].dy = dy/cluster_size;

        for (int k = 0; k < 64; k++)
            m_centers[i].descriptor[k] = sum_descriptor[k]/
                (float)cluster_size;
    }
}

double Kmeans::getSumDistance()   
{
    double sum = 0.0f;
    for (int i = 0; i < m_branch; i++)
        for (int j = 0; j < m_clusters[i]->size(); j++)
            sum += getDistance(m_clusters[i]->at(j), m_centers[i]);

    return sum;
}

void Kmeans::run(IpVec *t_ipts)
{
    int iter_count = 0;
    double E_old, E_new;

    setData(t_ipts);
    assert(ipts->size() >= m_branch);
    
    initCenters();
    assignToClusters();
    E_old = getSumDistance();

    while(1)
    {
       iter_count++;
       updataCenters();
       assignToClusters();
       
       E_new = getSumDistance();
        
       if (fabs(E_old - E_new) < 0.1f || iter_count >= m_iterTime)
           break;
       else
       {
           E_old = E_new;
           E_new = 0.0f;
       }
    }
}

Kmeans::~Kmeans()
{
    for (int i = 0; i < m_branch; i++)
    {
        if (m_clusters[i] != NULL)
        {
            delete m_clusters[i];
            m_clusters[i] = NULL;
        }
    }

    if (m_clusters != NULL)
    {
        delete[] m_clusters;
        m_clusters = NULL;
    }
}
