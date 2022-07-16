#include <CL/sycl.hpp>
#include <iostream>
#include <matgen.hpp>
#include <vector>
using namespace cl::sycl;
using float_type = float;

int main(){
    vector<float_type> q(nTotalCell);
    vector<float_type> nxs(nTotalFace);
    vector<float_type> ns(nTotalFace);
    vector<float_type> vol(nTotalCell);
    vector<size_t> leftCellofFace(nTotalFace);
    vector<size_t> rightCellofFace(nTotalFace);
    vector<size_t> maps(nTotalCell);
    vector<size_t> maps_face(nTotalFace);
    vector<float_type> dqdx(nTotalCell);
    //
    // random data generarion for mapping relationship
    matgen( q, nxs, ns, vol, leftCellofFace, rightCellofFace, maps, maps_face );
    //
    // initiazation for gradient dqdx.
    for( size_t iCell=0; iCell < dqdx.size(); ++iCell )
    {
        dqdx[iCell] = 0.0;
    }
    // calculate flux.
    for( size_t iFace=0; iFace < nTotalFace; ++iFace )
    {
        size_t le = leftCellofFace[iFace];
        size_t re = rightCellofFace[iFace];

        float_type qfc = 0.5 * ( q[le] + q[re] );
        float_type nx = nxs[iFace] * ns[iFace];

        dqdx[le] += qfc * nx;
        dqdx[re] -= qfc * nx;
        //cout<<iFace<<","<<le<<","<<re<<","<<qfc<<","<<dqdx[le]<<","<<dqdx[re]<<endl;
    }
    // obtain the gradient by dividing the cell volume.
    for( size_t iCell=0; iCell < nTotalCell; ++iCell )
    {
        float_type ovol = 1.0 / vol[iCell];
        dqdx[iCell] *= ovol;
    }
    //
    // print gradient dqdx.
    std::cout << "==========================gradient dqdx==============================="<<std::endl;
    for( size_t iCell = 0; iCell < dqdx.size(); ++iCell )
    {
        std::cout<<dqdx[iCell]<<" ";
    }
    std::cout<<std::endl;
    return 0;
}
