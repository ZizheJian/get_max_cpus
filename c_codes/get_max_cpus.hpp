#pragma once

#include <algorithm>
#include <cstdlib>
#include <sched.h>
#include <thread>
#include <unistd.h>

using namespace std;

inline int get_max_cpus(int user_max_cpus=-114514)
{
    int max_cpus=-114514;
    cpu_set_t cpu_set;
    CPU_ZERO(&cpu_set);
    if(sched_getaffinity(0,sizeof(cpu_set),&cpu_set)==0)
    {
        int affinity_cpus=CPU_COUNT(&cpu_set);
        if(affinity_cpus>0)
            max_cpus=affinity_cpus;
    }
    if (max_cpus<=0)
        max_cpus=1;
    if(user_max_cpus>0)
        max_cpus=min(max_cpus,user_max_cpus);
    return max_cpus;
}
