import os

def get_max_cpus(user_max_cpus:int|None=None):
    # bool是int的子类，用type而不是isinstance，才能把True和False也拦下
    if user_max_cpus is not None and (type(user_max_cpus) is not int or user_max_cpus<=0):
        raise ValueError("user_max_cpus必须是正整数")
    affinity=os.sched_getaffinity(0)
    max_cpus=max(1,len(affinity))
    if user_max_cpus is not None:
        max_cpus=min(max_cpus,user_max_cpus)
    return max_cpus

if __name__=="__main__":
    print(get_max_cpus())
