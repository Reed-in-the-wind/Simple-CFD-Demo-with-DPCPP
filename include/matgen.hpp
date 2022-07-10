#include<vector>
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
        size_t nBoundFace );
