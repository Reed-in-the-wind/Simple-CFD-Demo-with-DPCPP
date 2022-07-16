#include<vector>
using namespace std;

constexpr size_t nTotalCell = 10;
constexpr size_t nTotalFace = nTotalCell+1;

template<typename T >
int matgen(
        vector<T> &q,
        vector<T> &nxs,
        vector<T> &ns,
        vector<T> &vol,
        vector<size_t> &leftCellofFace,
        vector<size_t> &rightCellofFace,
        vector<size_t> &maps,
        vector<size_t> &maps_face);
