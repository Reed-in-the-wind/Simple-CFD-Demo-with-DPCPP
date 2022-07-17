#include <CL/sycl.hpp>
#include <iostream>
using namespace sycl;

int main() {
    // Create queue to use the host device explicitly
    //queue Q{ host_selector{} };
    queue Q{ };
    std::cout << "Selected device: " <<
        Q.get_device().get_info<info::device::name>() << "\n";
    std::cout << " -> Device vendor: " <<
        Q.get_device().get_info<info::device::vendor>() << "\n";
    return 0;
}
