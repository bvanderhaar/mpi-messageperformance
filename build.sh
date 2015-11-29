if hash clang-format 2>/dev/null; then
  clang-format -i hello.cpp
fi
if [[ $OSTYPE == darwin* ]]; then
  mpic++ --std=c++11 hello.cpp -o mpi-comperf
  chmod +x mpi-comperf
fi
if [[ $OSTYPE == linux* ]]; then
  mpiCC --std=c++11 hello.cpp -o mpi-comperf
  chmod +x mpi-comperf
fi
