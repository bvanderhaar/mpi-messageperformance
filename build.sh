if [[ $OSTYPE == darwin* ]]; then
  clang-format -i message-size.cpp message-time.cpp
  mpic++ --std=c++11 message-size.cpp -o mpi-size
  mpic++ --std=c++11 message-time.cpp -o mpi-time
  chmod +x mpi-size
  chmod +x mpi-time
fi
if [[ $OSTYPE == linux* ]]; then
  mpiCC --std=c++11 message-size.cpp -o mpi-size
  mpiCC --std=c++11 message-time.cpp -o mpi-time
  chmod +x mpi-size
  chmod +x mpi-time
fi
