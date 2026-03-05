#include "tensor.h"
#include <cstdlib>
#include <cstring>
#include <new>

namespace llmpp {

Tensor::Tensor(const std::vector<int>& shape) : shape_(shape), data_(nullptr) {
    size_t total_size = num_elements() * sizeof(float);
    data_ = static_cast<float*>(std::aligned_alloc(32, total_size)); // AVX alignment
    if (!data_) throw std::bad_alloc();
}

Tensor::Tensor(Tensor&& other) noexcept : shape_(std::move(other.shape_)), data_(other.data_) {
    other.data_ = nullptr;
}

Tensor& Tensor::operator=(Tensor&& other) noexcept {
    if (this != &other) {
        std::free(data_);
        shape_ = std::move(other.shape_);
        data_ = other.data_;
        other.data_ = nullptr;
    }
    return *this;
}

Tensor::~Tensor() {
    std::free(data_);
}

size_t Tensor::size() const {
    return shape_.size();
}

size_t Tensor::num_elements() const {
    size_t s = 1;
    for (int dim : shape_) s *= dim;
    return s;
}

Tensor Tensor::matmul(const Tensor& a, const Tensor& b) {
    if (a.shape_.size() != 2 || b.shape_.size() != 2 || a.shape_[1] != b.shape_[0]) {
        throw std::invalid_argument("Invalid shapes for matmul");
    }
    int M = a.shape_[0], K = a.shape_[1], N = b.shape_[1];
    Tensor c({M, N});

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            float sum = 0;
            for (int k = 0; k < K; ++k) {
                sum += a.data_[i * K + k] * b.data_[k * N + j];
            }
            c.data_[i * N + j] = sum;
        }
    }

    return c;
}

} // namespace llmpp