#include "llmpp/tensor.h"
#include "llmpp/cpuinfo.h"
#include <gtest/gtest.h>

TEST(TensorTest, Matmul) {
    llmpp::Tensor a({2, 2});
    llmpp::Tensor b({2, 2});

    a.data()[0] = 1; a.data()[1] = 2;
    a.data()[2] = 3; a.data()[3] = 4;

    b.data()[0] = 5; b.data()[1] = 6;
    b.data()[2] = 7; b.data()[3] = 8;

    llmpp::Tensor c = llmpp::Tensor::matmul(a, b);

    EXPECT_EQ(c.data()[0], 19); // 1*5 + 2*7
    EXPECT_EQ(c.data()[1], 22); // 1*6 + 2*8
    EXPECT_EQ(c.data()[2], 43); // 3*5 + 4*7
    EXPECT_EQ(c.data()[3], 50); // 3*6 + 4*8
}

TEST(CpuInfoTest, DetectFeatures) {
    llmpp::CpuInfo info = llmpp::get_cpu_info();
    EXPECT_GE(info.cores, 1);
}