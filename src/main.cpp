#include <iostream>
#include <matgen.hpp>
#include <vector>
using namespace std;

int main(){
    size_t nTotalCell=10;
    size_t nTotalFace=10;
    size_t nBoundFace=10;
    vector<float> q(nTotalCell);
    vector<float> nxs(nTotalFace);
    vector<float> ns(nTotalFace);
    vector<float> vol(nTotalCell);
    vector<float> leftCellofFace(nTotalFace);
    vector<float> rightCellofFace(nTotalFace);
    matgen( q, nxs, ns, vol, leftCellofFace, rightCellofFace, nTotalCell, nTotalFace, nBoundFace );
    for( size_t i = 0; i < q.size(); ++i )
    {
        cout<<q[i]<<endl;
    }
    return 0;
}
