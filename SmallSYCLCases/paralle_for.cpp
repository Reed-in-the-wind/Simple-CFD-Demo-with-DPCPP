#include <CL/sycl.hpp>
#include <iostream>
constexpr int num=16;
using namespace cl::sycl;

int main() {
    auto R = range<1>{ num };
    auto R1 = range<2>{ num, num };
    buffer<int> A{ R };
    buffer<int, 2> B{ R1 };
    queue{}.submit([&](handler& h) {
      auto out =
        A.get_access<access::mode::write>(h);
        h.parallel_for(R, [=](id<1> idx) {
                out[idx] = idx[0]; }); 

        });

    auto result =
        A.get_access<access::mode::read>();
    for (int i=0; i<num; ++i)
        std::cout << result[i] << "\n";

    // chooses. Implicit use of the default_selector.
    queue Q;
    std::cout << "Selected device: " << Q.get_device().get_info<info::device::name>() << "\n";
    return 0;
}
