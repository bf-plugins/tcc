# Tensor core correlator build script
project('tcc', 'cpp', 'cuda', version: '0.0.1',
         default_options : ['cpp_std=c++11', 'optimization=3'])
cc = meson.get_compiler('cpp')
pkg = import('pkgconfig')
version = '0.5'
build_exe = false

# Dependencies
cuda_dep = dependency('cuda', version : '>=10', modules : ['cudart', 'nvrtc', 'cuda'])
openmp_dep = dependency('openmp', required: false)
opencl_dep = dependency('opencl', required: false)


# Compile libtcc
libtcc_srcs = [
    'util/cu.cc',
	'util/nvrtc.cc',
	'libtcc/CorrelatorKernel.cc',
	'libtcc/Correlator.cc',
	'libtcc/Kernel.cc'
    ]

# libtcc needs libtcc/TCCorrelator.o to be linked 
# I don't like this, but not sure how to do this in meson 
run_command('ld', '-r', '-b', 'binary', '-o', 'libtcc/TCCorrelator.o', 'libtcc/TCCorrelator.cu', check: true)

lib_tcc = library('tcc', libtcc_srcs, 
              version : version, soversion : '0', 
              dependencies: cuda_dep,
              objects: 'libtcc/TCCorrelator.o'
              )

# Create pkgconfig file
pkg.generate(libraries : lib_tcc,
             subdirs : ['libtcc'],
             version : version,
             name : 'libtcc',
             filebase : 'tcc',
             description : 'Tensor core correlator for radio astronomy on NVIDIA GPUs')

# Include dirs -- this is set in case TCC is used as a meson subproject
inc_dirs = [
    '.',
    'util',
    'libtcc',
    'test/Common'
]
subproject_dep = declare_dependency(include_directories: inc_dirs, link_with: lib_tcc)

if build_exe
    # Compile executable: Simple example
    executable('SimpleExample', 'test/SimpleExample/SimpleExample.cu',
            link_with: lib_tcc, dependencies: cuda_dep)

    # Compile executable: Correlator test
    if openmp_dep.found()
        corrtest_srcs = [
            'test/CorrelatorTest/CorrelatorTest.cc',
            'test/CorrelatorTest/Options.cc',
            'test/Common/Record.cc',
            'test/Common/UnitTest.cc',
            ]
        corrtest_inc = [
            'test/Common/ComplexInt4.h', 
            'test/Common/Record.h',
            'test/CorrelatorTest/CorrelatorTest.h'
        ]

        executable('CorrelatorTest', corrtest_srcs,
                link_with: lib_tcc, dependencies: [cuda_dep, openmp_dep])
    else
        warning('OpenMP not found, CorrelatorTest will not be built.')
    endif

    if opencl_dep.found()
        executable('OpenCLCorrelatorTest', 'test/OpenCLCorrelatorTest/OpenCLCorrelatorTest.cc',
            link_with: lib_tcc, 
            include_directories: 'CL',
            dependencies: cuda_dep)
    else
        warning('OpenCL not found, OpenCLCorrelatorTest will not be built.')
    endif
endif