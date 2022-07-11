#include <iostream>
#include <matgen.hpp>
#include <vector>
using namespace std;

int main(){
    vector<float> q(nTotalCell);
    vector<float> nxs(nTotalFace);
    vector<float> ns(nTotalFace);
    vector<float> vol(nTotalCell);
    vector<size_t> leftCellofFace(nTotalFace);
    vector<size_t> rightCellofFace(nTotalFace);
    vector<size_t> maps(nTotalCell);
    vector<size_t> maps_face(nTotalFace);
    vector<float> dqdx(nTotalCell);
    //
    matgen( q, nxs, ns, vol, leftCellofFace, rightCellofFace, maps, maps_face );
    for( size_t i = 0; i < q.size(); ++i )
    {
        cout<<q[i]<<endl;
    }
    return 0;
}
