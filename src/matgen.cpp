#include <vector>
#include <iostream>
#include <random>
#include <matgen.hpp>
#include <algorithm>
using namespace std;

template<typename T>
void swap( T &a, T &b  )
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

template<typename T >
int matgen(
        vector<T> &q,
        vector<T> &nxs,
        vector<T> &ns,
        vector<T> &vol,
        vector<size_t> &leftCellofFace,
        vector<size_t> &rightCellofFace,
        vector<size_t> &maps,
        vector<size_t> &maps_face)
{
    vector<T> ori_q(q.size());
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    //
    for( size_t i=0; i<maps.size(); ++i )
    {
        maps[i] = i;
    }
    // generate the random sequence to represent the mapping.
    std::random_shuffle( maps.begin(), maps.end() );
    //
    cout<<"cell maps: original -> new"<<endl;
    for( size_t i=0; i<maps.size(); ++i )
    {
        cout << i << "->" << maps[i] << ", ";
    }
    cout<<endl;
    //
    // for face mapping
    for( size_t i=0; i<maps_face.size(); ++i )
    {
        maps_face[i] = i;
    }
    std::random_shuffle( maps_face.begin(), maps_face.end() );
    //
    cout<<"face maps: original -> new"<<endl;
    for( size_t i=0; i<maps_face.size(); ++i )
    {
        cout << i << "->" << maps_face[i] << ", ";
    }
    cout<<endl;
    //
    cout<<"original q:"<<endl;
    for( size_t i=0; i < nTotalCell; ++i )
    {
        ori_q[i] = dis(gen);
        vol[i] = 1.0;
        cout<<ori_q[i]<<" ";
    }
    cout<<endl;
    //
    // exchange q with the maps orders
    for( size_t i=0; i < nTotalCell; ++i )
    {
        q[maps[i]] = ori_q[i];
    }
    cout<<"permutated q:"<<endl;
    for( size_t i=0; i < nTotalCell; ++i )
    {
        cout<<q[i]<<" ";
    }
    cout<<endl;
    //
    // change the subscript with the maps array.
    
    for( size_t i=0; i < nTotalFace; ++i )
    {
        nxs[i] = 1.0;
        ns[i] = 1.0;
    }
    for( size_t i=0; i < nTotalFace; ++i )
    {
        if ( i == 0 )
        {
            // left boundary face, assume Dirichlet BCs.
            leftCellofFace[maps_face[i]] = maps[i];
            rightCellofFace[maps_face[i]] = maps[i];
        }
        else if ( i == nTotalFace - 1 )
        {
            // right boundary face, assume Dirichlet BCs.
            leftCellofFace[maps_face[i]] = maps[i-1];
            rightCellofFace[maps_face[i]] = maps[i-1];
        }
        else
        {
            leftCellofFace[maps_face[i]] = maps[i-1];
            rightCellofFace[maps_face[i]] = maps[i];
        }
    }
    //
    cout<<"==========================the neighbor cell information==================="<<endl;
    for( size_t i=0; i < nTotalFace; ++i )
    {
        cout << i << "th face: (left, right) cell = " << "(" << leftCellofFace[i] 
            << "," << rightCellofFace[i] << ")" << endl;
    }
    //
    vector<T> ori_dqdx(q.size());
    for( size_t i=0; i < ori_dqdx.size(); ++i )
    {
        if ( i == 0 )
        {
            // left boundary
            ori_dqdx[i] = 0.5* ( ori_q[i+1] + ori_q[i] );
        }
        else if( i == ori_dqdx.size()-1 )
        {
            // right boundary
            ori_dqdx[i] = - 0.5* ( ori_q[i-1] + ori_q[i] );
        }
        else
        {
            ori_dqdx[i] = 0.5* ( ori_q[i+1] + ori_q[i] ) - 0.5 * ( ori_q[i] + ori_q[i-1] );
        }
    }
    cout<<"original dqdx:"<<endl;
    for( size_t i=0; i < ori_dqdx.size(); ++i )
    {
        cout<<ori_dqdx[i]<<" ";
    }
    cout << endl;
    //
    vector<T> perm_dqdx(q.size());
    cout<<"permuted dqdx:"<<endl;
    for( size_t i=0; i < perm_dqdx.size(); ++i )
    {
        perm_dqdx[maps[i]] = ori_dqdx[i];
    }
    for( size_t i=0; i < perm_dqdx.size(); ++i )
    {
        cout<<perm_dqdx[i]<<" ";
    }
    cout << endl;
    cout<<"================================Finish Data Generation======================"<<endl;
    return 0;
}

template int matgen<float>( vector<float> &q,
        vector<float> &nxs,
        vector<float> &ns,
        vector<float> &vol,
        vector<size_t> &leftCellofFace,
        vector<size_t> &rightCellofFace,
        vector<size_t> &maps,
        vector<size_t> &maps_face );
