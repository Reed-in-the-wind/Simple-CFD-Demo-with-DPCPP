#include <vector>
#include <iostream>
#include <random>
#include <matgen.hpp>
using namespace std;

template<typename T >
int matgen(
        vector<T> &q,
        vector<T> &nxs,
        vector<T> &ns,
        vector<T> &vol,
        vector<T> &leftCellofFace,
        vector<T> &rightCellofFace,
        size_t nTotalCell,
        size_t nTotalFace,
        size_t nBoundFace )
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for( size_t i=0; i < nTotalCell; ++i )
    {
        q[i] = dis(gen);
        vol[i] = dis(gen);
        cout<<q[i]<<endl;
    }
    for( size_t i=0; i < nTotalFace; ++i )
    {
        nxs[i] = dis(gen);
        ns[i] = dis(gen);
        leftCellofFace[i] = dis(gen);
        rightCellofFace[i] = dis(gen);
    }
    return 0;
}

template int matgen<float>( vector<float> &q,
        vector<float> &nxs,
        vector<float> &ns,
        vector<float> &vol,
        vector<float> &leftCellofFace,
        vector<float> &rightCellofFace,
        size_t nTotalCell,
        size_t nTotalFace,
        size_t nBoundFace );
