#pragma once

#include <algorithm>
#include <cstdlib>
#include <limits>
#include <sched.h>
#include <stdexcept>
#include <thread>
#include <unistd.h>
#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

inline int get_max_cpus(int user_max_cpus)
{
    if(user_max_cpus<=0)
        throw invalid_argument("user_max_cpus必须是正整数");
    int max_cpus=1;
#ifdef _OPENMP
    max_cpus=max(1,omp_get_num_procs());
#else
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    if(sched_getaffinity(0,sizeof(cpu_set),&cpu_set)==0)
    {
        int affinity_cpus=CPU_COUNT(&cpu_set);
        if(affinity_cpus>0)
            max_cpus=affinity_cpus;
    }
#endif
    return min(max_cpus,user_max_cpus);
}

inline int get_max_cpus()
{
    return get_max_cpus(numeric_limits<int>::max());
}
