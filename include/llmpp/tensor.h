#pragma once

#include <vector>
#include <cstddef>
#include <memory>

namespace llmpp {

class Tensor {
public:
    Tensor(const std::vector<int>& shape);
    Tensor(const Tensor&) = delete;
    Tensor& operator=(const Tensor&) = delete;
    Tensor(Tensor&& other) noexcept;
    Tensor& operator=(Tensor&& other) noexcept;
    ~Tensor();

    float* data() { return data_; }
    const float* data() const { return data_; }
    const std::vector<int>& shape() const { return shape_; }
    size_t size() const;
    size_t num_elements() const;

    static Tensor matmul(const Tensor& a, const Tensor& b);

private:
    std::vector<int> shape_;
    float* data_;
};

} // namespace llmpp