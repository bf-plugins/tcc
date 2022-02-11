#if !defined TCC_KERNEL_H
#define TCC_KERNEL_H

#include "external/cuda-wrappers/cu/cu.h"

#include <stdint.h>


namespace tcc {
  class Kernel
  {
    public:
      Kernel(cu::Module &, const char *name);

      virtual uint64_t FLOPS() const = 0;

    protected:
      cu::Module   &module;
      cu::Function function;
  };
}

#endif
