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
    queue Q{ host_selector{} }; // cpu device.
    //
    // host code.
    // random data generarion for mapping relationship
    matgen( q, nxs, ns, vol, leftCellofFace, rightCellofFace, maps, maps_face );
    //
    buffer dqdx_buf( dqdx );
    {
        Q.submit( [&](handler& h){
            // initiazation for gradient dqdx.
            auto R = range<1>{nTotalCell};
            auto dqdx_acc = dqdx_buf.get_access<access::mode::write>(h);
            h.parallel_for( R, [=](id<1> iCell) {
                dqdx_acc[iCell] = 0.0;
            });
        });
    }
#ifndef REORDERING
    // do not the mesh number reordering(mesh point and surface)
    {
        buffer leftCellofFace_buf( leftCellofFace );
        buffer rightCellofFace_buf( rightCellofFace );
        buffer q_buf( q );
        buffer nxs_buf( nxs );
        buffer ns_buf( ns );
        Q.submit( [&](handler& h){
            auto R = range<1>{nTotalFace};
            auto dqdx_acc = dqdx_buf.get_access<access::mode::write>(h);
            auto left_acc = leftCellofFace_buf.get_access<access::mode::read>(h);
            auto right_acc = rightCellofFace_buf.get_access<access::mode::read>(h);
            auto q_acc = q_buf.get_access<access::mode::read>(h);
            auto nxs_acc = nxs_buf.get_access<access::mode::read>(h);
            auto ns_acc = ns_buf.get_access<access::mode::read>(h);
            h.parallel_for( R, [=](id<1> iFace){
                size_t le = left_acc[iFace];
                size_t re = right_acc[iFace];
                float_type qfc = 0.5 * ( q_acc[le] + q_acc[re] );
                float_type nx = nxs_acc[iFace] * ns_acc[iFace];
                dqdx_acc[le] += qfc * nx;
                dqdx_acc[re] -= qfc * nx;
            });
        });
    }
    //
    // obtain the gradient by dividing the cell volume.
    {
        buffer vol_buf( vol );
        Q.submit( [&](handler& h){
            auto R = range<1>{nTotalCell};
            auto dqdx_acc = dqdx_buf.get_access<access::mode::write>(h);
            auto vol_acc = vol_buf.get_access<access::mode::read>(h);
            h.parallel_for( R, [=](id<1> iCell){
                float_type ovol = 1.0 / vol_acc[iCell];
                dqdx_acc[iCell] *= ovol;
            });
        });
    }
    //
    // print gradient dqdx on host.
    std::cout << "==========================gradient dqdx==============================="<<std::endl;
    for( size_t iCell = 0; iCell < dqdx.size(); ++iCell )
    {
        std::cout<<dqdx[iCell]<<" ";
    }
    std::cout<<std::endl;
#else
    {
        // the reordering is adopted.
        buffer leftCellofFace_buf( leftCellofFace );
        buffer rightCellofFace_buf( rightCellofFace );
        buffer q_buf( q );
        buffer nxs_buf( nxs );
        buffer ns_buf( ns );
        Q.submit( [&](handler& h){
            auto R = range<1>{nTotalFace-2};
            auto dqdx_acc = dqdx_buf.get_access<access::mode::write>(h);
            auto left_acc = leftCellofFace_buf.get_access<access::mode::read>(h);
            auto right_acc = rightCellofFace_buf.get_access<access::mode::read>(h);
            auto q_acc = q_buf.get_access<access::mode::read>(h);
            auto nxs_acc = nxs_buf.get_access<access::mode::read>(h);
            auto ns_acc = ns_buf.get_access<access::mode::read>(h);
            h.parallel_for( R, [=](id<1> iFace){
                size_t le = iFace;
                size_t re = iFace+1;
                float_type qfc = 0.5 * ( q_acc[le] + q_acc[re] );
                float_type nx = nxs_acc[iFace+1] * ns_acc[iFace+1];
                dqdx_acc[le] += qfc * nx;
                dqdx_acc[re] -= qfc * nx;
            });
        });
    }
    //
    //
    // obtain the gradient by dividing the cell volume.
    {
        buffer vol_buf( vol );
        Q.submit( [&](handler& h){
            auto R = range<1>{nTotalCell};
            auto dqdx_acc = dqdx_buf.get_access<access::mode::write>(h);
            auto vol_acc = vol_buf.get_access<access::mode::read>(h);
            h.parallel_for( R, [=](id<1> iCell){
                float_type ovol = 1.0 / vol_acc[iCell];
                dqdx_acc[iCell] *= ovol;
            });
        });
    }
    //
    // print gradient dqdx on host.
    std::cout << "==========================gradient dqdx==============================="<<std::endl;
    for( size_t iCell = 0; iCell < dqdx.size(); ++iCell )
    {
        std::cout<<dqdx[iCell]<<" ";
    }
    std::cout<<std::endl;
#endif
    return 0;
}
