#include <stdio.h>
#include <cstdlib>

int main(int argc, char *argv[]) {
  const long long MSGSIZE = 99999999;
  char *message = new char[MSGSIZE];
  for (long long i = 0; i < MSGSIZE; i++) {
    message[i] = 'a' + std::rand() % 26;
  }
}
