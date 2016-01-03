//initialize
#include "methods.h"

//random Integers from 0 to 4999
void initialize(){
	for(int i = 0 ; i<1000; i++){
		cylinders[i] = random_at_most(4999);
	}
}
//print out the cylinder array
void print_cylinders(){
  for (int i = 0; i<1000;i++){
    printf("%d    ",i);
    printf("%d\n",cylinders[i]);
  }
}
// Assumes 0 <= max <= RAND_MAX
// Returns in the half-open interval [0, max]
long random_at_most(long max) {
  srand(time(NULL));
  unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;
  long x;
  do {
   x = random();
  }
  // This is carefully written not to overflow
  while (num_rand - defect <= (unsigned long)x);

  // Truncated division is intentional
  return x/bin_size;
}