#if !defined TCC_CORRELATOR_H
#define TCC_CORRELATOR_H

#include "libtcc/CorrelatorKernel.h"
#include "external/cuda-wrappers/cu/cu.h"
#include "external/cuda-wrappers/cu/nvrtc.h"

#include <string>


namespace tcc {
  class Correlator {
    public:
      Correlator(unsigned nrBits,
		 unsigned nrReceivers,
		 unsigned nrChannels,
		 unsigned nrSamplesPerChannel,
		 unsigned nrPolarizations = 2,
		 unsigned nrReceiversPerBlock = 64,
		 const std::string &customStoreVisibility = ""
		); // throw (cu::Error, nvrtc::Error)

      void launchAsync(cu::Stream &, cu::DeviceMemory &visibilities, cu::DeviceMemory &samples); // throw (cu::Error)
      void launchAsync(CUstream, CUdeviceptr visibilities, CUdeviceptr samples); // throw (cu::Error)

      uint64_t FLOPS() const;

    private:
      std::string      findNVRTCincludePath() const;
      cu::Module       compileModule(unsigned nrBits,
				     unsigned nrReceivers,
				     unsigned nrChannels,
				     unsigned nrSamplesPerChannel,
				     unsigned nrPolarizations,
				     unsigned nrReceiversPerBlock,
				     const std::string &customStoreVisibility
				    );

      cu::Module       correlatorModule;
      CorrelatorKernel correlatorKernel;
  };
}

#endif
