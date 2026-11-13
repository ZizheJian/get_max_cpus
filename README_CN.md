# get_max_cpus

[English](README.md) | **中文**

`get_max_cpus`返回当前进程能用的CPU数量，并可以用给定的上限截断。直接运行时一般是整台机器的CPU数量，在Slurm作业里或被`taskset`限制时是分配给进程的CPU数量。仓库提供C++版和Python版，只支持Linux。

## C++

在CMake里把目录加为子目录，再链接目标：

```cmake
add_subdirectory(third_party/get_max_cpus/c_codes ${CMAKE_BINARY_DIR}/get_max_cpus_build)
target_link_libraries(my_target PRIVATE get_max_cpus)
```

```cpp
#include <get_max_cpus.hpp>

int all_cpus=get_max_cpus();
int capped_cpus=get_max_cpus(8);
```

`get_max_cpus()`返回全部可用的CPU数量，`get_max_cpus(8)`最多返回8。上限不是正数时，函数抛出`std::invalid_argument`。设置了OpenMP线程绑定（`OMP_PROC_BIND`或`OMP_PLACES`）时结果同样正确，与调用它的源文件是否用`-fopenmp`编译无关。

## Python

仓库以子模块形式放在`third_party/get_max_cpus`时：

```python
from third_party.get_max_cpus.py_codes.get_max_cpus import get_max_cpus

all_cpus=get_max_cpus()
capped_cpus=get_max_cpus(8)
```

上限不是正整数时，函数抛出`ValueError`。直接运行`python py_codes/get_max_cpus.py`会打印结果。

### 限制

Python版不支持在开启了OpenMP线程绑定的Python进程里调用（例如导入了PyTorch，又设置了`OMP_PROC_BIND`或`OMP_PLACES`），这时会返回1。
