#pragma once

#include <algorithm>
#include <cerrno>
#include <cstring>
#include <limits>
#include <sched.h>
#include <stdexcept>
#include <string>

// 弱引用OpenMP运行库的omp_get_num_procs：进程里有OpenMP运行库时指向它，没有时为nullptr
// 换一个名字声明，是为了不和omp.h里的同名声明冲突
extern "C" int get_max_cpus_omp_get_num_procs(void) __asm__("omp_get_num_procs") __attribute__((weak));

inline int get_max_cpus(int user_max_cpus)
{
    using namespace std;
    if(user_max_cpus<=0)
        throw invalid_argument("user_max_cpus必须是正整数");
    int max_cpus=1;
    // 设置了OMP_PROC_BIND时，OpenMP运行库一启动就把主线程钉到一个核上，这时问Linux只能得到1，所以有OpenMP时问OpenMP
    if(get_max_cpus_omp_get_num_procs!=nullptr)
        max_cpus=max(1,get_max_cpus_omp_get_num_procs());
    else
    {
        // 一个cpu_set_t只能装1024个CPU，逻辑CPU更多的机器上sched_getaffinity会失败
        // 所以把64个cpu_set_t连成一张大清单，能装65536个CPU(8KB)，远超Linux在x86上的上限8192
        cpu_set_t cpu_sets[64];
        if(sched_getaffinity(0,sizeof(cpu_sets),cpu_sets)!=0)
        {
            int error=errno;
            throw runtime_error(string("sched_getaffinity失败: ")+strerror(error));
        }
        max_cpus=max(1,CPU_COUNT_S(sizeof(cpu_sets),cpu_sets));
    }
    return min(max_cpus,user_max_cpus);
}

inline int get_max_cpus()
{
    using namespace std;
    return get_max_cpus(numeric_limits<int>::max());
}
