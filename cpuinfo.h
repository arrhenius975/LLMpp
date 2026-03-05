#pragma once

#include <cstdint>

namespace llmpp {

struct CpuInfo {
    bool has_avx2 = false;
    bool has_avx512 = false;
    bool has_amx = false;
    int cores = 0;
};

CpuInfo get_cpu_info();

} // namespace llmpp