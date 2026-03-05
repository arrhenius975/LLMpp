#include "cpuinfo.h"
#include <thread>

#ifdef _MSC_VER
#include <intrin.h>
#else
#include <cpuid.h>
#endif

namespace llmpp {

CpuInfo get_cpu_info() {
    CpuInfo info;
    info.cores = static_cast<int>(std::thread::hardware_concurrency());

#ifdef _MSC_VER
    int cpu_info[4];
    __cpuid(cpu_info, 1);
    if (cpu_info[2] & (1 << 28)) info.has_avx2 = true;
    __cpuid(cpu_info, 7);
    if (cpu_info[1] & (1 << 16)) info.has_avx512 = true;
    if (cpu_info[3] & (1 << 22)) info.has_amx = true;
#else
    unsigned int eax, ebx, ecx, edx;
    __get_cpuid(1, &eax, &ebx, &ecx, &edx);
    if (ecx & (1 << 28)) info.has_avx2 = true;
    __get_cpuid_count(7, 0, &eax, &ebx, &ecx, &edx);
    if (ebx & (1 << 16)) info.has_avx512 = true;
    if (edx & (1 << 22)) info.has_amx = true;
#endif

    return info;
}

} // namespace llmpp