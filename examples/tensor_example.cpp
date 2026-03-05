#include "llmpp/tensor.h"
#include <iostream>

int main() {
    llmpp::Tensor a({2, 3});
    llmpp::Tensor b({3, 2});

    // Initialize with some data
    float* data_a = a.data();
    for (int i = 0; i < 6; ++i) data_a[i] = i + 1;

    float* data_b = b.data();
    for (int i = 0; i < 6; ++i) data_b[i] = i + 1;

    llmpp::Tensor c = llmpp::Tensor::matmul(a, b);

    std::cout << "Result shape: " << c.shape()[0] << "x" << c.shape()[1] << std::endl;
    for (int i = 0; i < c.num_elements(); ++i) {
        std::cout << c.data()[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}