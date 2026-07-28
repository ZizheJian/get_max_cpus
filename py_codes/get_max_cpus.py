import os

def get_max_cpus(user_max_cpus:int=None):
    if os.sched_getaffinity(0)!=None and len(os.sched_getaffinity(0))>0:
        max_cpus=len(os.sched_getaffinity(0))
    else:
        max_cpus=1
    if user_max_cpus is not None:
        max_cpus=min(max_cpus,user_max_cpus)
    return max_cpus

if __name__ == "__main__":
    get_max_cpus(None)