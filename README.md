# get_max_cpus

**English** | [中文](README_CN.md)

`get_max_cpus` returns the number of CPUs that the current process may use, optionally capped by a given limit. When run directly, this is usually every CPU of the machine. Under Slurm or `taskset`, it is the CPUs allocated to the process. The repository provides a C++ version and a Python version, both for Linux only.

## C++

Add the directory as a CMake subdirectory and link the target:

```cmake
add_subdirectory(third_party/get_max_cpus/c_codes ${CMAKE_BINARY_DIR}/get_max_cpus_build)
target_link_libraries(my_target PRIVATE get_max_cpus::get_max_cpus)
```

```cpp
#include <get_max_cpus.hpp>

int all_cpus=get_max_cpus();
int capped_cpus=get_max_cpus(8);
```

`get_max_cpus()` returns all available CPUs, and `get_max_cpus(8)` returns at most 8. The function throws `std::invalid_argument` when the limit is not positive. The result stays correct when OpenMP thread binding is enabled through `OMP_PROC_BIND` or `OMP_PLACES`, whether or not the calling source file is compiled with `-fopenmp`.

## Python

When the repository is a submodule at `third_party/get_max_cpus`:

```python
from third_party.get_max_cpus.py_codes.get_max_cpus import get_max_cpus

all_cpus=get_max_cpus()
capped_cpus=get_max_cpus(8)
```

The function raises `ValueError` when the limit is not a positive integer. Running `python py_codes/get_max_cpus.py` prints the result.

### Limitation

The Python version does not support being called from a Python process with OpenMP thread binding enabled, for example one that imports PyTorch while `OMP_PROC_BIND` or `OMP_PLACES` is set. In that case it returns 1.
