# Bifrost wrapper file
project('tcc', 'cpp', 'cuda', version: '0.0.1',
         default_options : ['cpp_std=c++11', 'optimization=3'])
#add_project_arguments('-O3', language : 'cpp')

cc = meson.get_compiler('cpp')

# CUDA setup
cuda_dep = dependency('cuda', version : '>=10', modules : ['cudart', 'nvrtc', 'cuda'])

# Generate python wrapper from .h file
builddir = meson.project_build_root()

########
## LIBTCC
########
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
              version : '0.0.2', soversion : '0', 
              dependencies: cuda_dep,
              objects: 'libtcc/TCCorrelator.o'
              )

# Executable: Simple example
executable('SimpleExample', 'test/SimpleExample/SimpleExample.cu',
           link_with: lib_tcc, dependencies: cuda_dep)

# Executable: Correlator test
openmp_dep = dependency('openmp')
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

#executable('OpenCLCorrelatorTest', 'test/OpenCLCorrelatorTest/OpenCLCorrelatorTest.cu',
#           link_with: lib_tcc, dependencies: cuda_dep)
