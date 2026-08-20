import os

def get_max_cpus(user_max_cpus:int=None):
    if user_max_cpus is not None and user_max_cpus<=0:
        raise ValueError("user_max_cpus必须是正整数")
    affinity=os.sched_getaffinity(0)
    max_cpus=max(1,len(affinity))
    if user_max_cpus is not None:
        max_cpus=min(max_cpus,user_max_cpus)
    return max_cpus

if __name__ == "__main__":
    get_max_cpus(None)
