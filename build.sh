if hash clang-format 2>/dev/null; then
  clang-format -i hello.cpp
fi
if hash clang++ 2>/dev/null; then
  clang++ -std=c++1y hello.cpp -o mpi-comperf
  chmod +x mpi-comperf
fi
if hash mpiCC 2>/dev/null; then
  mpiCC --std=c++11 hello.cpp -o mpi-comperf
  chmod +x mpi-comperf
fi
