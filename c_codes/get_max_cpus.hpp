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

// inline int get_max_cpus(int user_max_cpus=-114514)
// {
//     int max_cpus=-114514;
//     cpu_set_t cpu_set;
//     CPU_ZERO(&cpu_set);
//     if(sched_getaffinity(0,sizeof(cpu_set),&cpu_set)==0)
//     {
//         int affinity_cpus=CPU_COUNT(&cpu_set);
//         if(affinity_cpus>0)
//         {
//             printf("Affinity CPUs: %d\n",affinity_cpus);
//             max_cpus=affinity_cpus;
//         }
//     }
//     if(max_cpus<=0)
//     {
//         const char *cpus_per_task=getenv("SLURM_CPUS_PER_TASK");
//         if(cpus_per_task)
//         {
//             printf("SLURM_CPUS_PER_TASK: %s\n",cpus_per_task);
//             max_cpus=atoi(cpus_per_task);
//         }
//     }
//     if(max_cpus<=0)
//     {
//         const char *ntasks=getenv("SLURM_NTASKS");
//         if(ntasks)
//         {
//             printf("SLURM_NTASKS: %s\n",ntasks);
//             max_cpus=atoi(ntasks);
//         }
//     }
//     if(max_cpus<=0)
//     {
//         unsigned int cpu_count=thread::hardware_concurrency();
//         if(cpu_count>0)
//         {
//             printf("Hardware concurrency: %u\n",cpu_count);
//             max_cpus=static_cast<int>(cpu_count);
//         }
//     }
//     if (max_cpus<=0)
//         max_cpus=1;
//     if(user_max_cpus>0)
//         max_cpus=min(max_cpus,user_max_cpus);
//     return max_cpus;
// }