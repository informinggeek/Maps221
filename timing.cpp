////////////////////////////////////////////////////////////////////////////////
/// @brief Example timing file. Add to this file the functions you want to time
////////////////////////////////////////////////////////////////////////////////

#include <chrono>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>

#include "map.h"

using namespace std;
using namespace chrono;

/// @brief Function to time n inserts on a linear structured tree (worst case)
/// @param n Input size
void insert_n_linear_height_tree(size_t n) {
  using mystl::map;
  // call code to time
  map<int, int> m;
  for(size_t i = 0; i < n; ++i)
    m[i] = i;
}

/// @brief Function to time n inserts on a complete binary tree (best case)
/// @param n Input size
void insert_n_logarithmic_height_tree(size_t n) {
  using mystl::map;
  // call code to time
  map<double, double> m;
  m[0] = 0;
  double incr = 2;
  double low = -1, high = 1;
  double t = low;
  while(m.size() < n) {
    if(t > high) {
      incr /= 2;
      low -= incr/2;
      high += incr/2;
      t = low;
    }
    m[t] = t;
    t += incr;
  }
}

/// @brief Function to time n inserts of random data (avg case)
/// @param n Input size
void insert_n_random(size_t n) {
  using mystl::map;
  // call code to time
  map<int, int> m;
  for(size_t i = 0; i < n; ++i) {
    int j = rand();
    m[j] = j;
  }
}

/// @brief Control timing of a single function
/// @tparam Func Function type
/// @param f Function taking a single size_t parameter
/// @param max_size Maximum size of test. For linear - 2^23 is good, for
///                 quadrati - 2^18 is probably good enough, but its up to you.
/// @param name Name of function for nice output
///
/// Essentially this function outputs timings for powers of 2 from 2 to
/// max_size. For each timing it repeats the test at least 10 times to ensure
/// a good average time.
template<typename Func>
void time_function(Func f, size_t max_size, string name) {
  cout << "Function: " << name << endl;
  cout << setw(15) << "Size" << setw(15) << "Time(sec)" << endl;

  // Loop to control input size
  for(size_t i = 2; i < max_size; i*=2) {
    cout << setw(15) << i;

    // create a clock
    high_resolution_clock::time_point start = high_resolution_clock::now();

    // loop a specific number of times to make the clock tick
    size_t num_itr = max(size_t(10), max_size / i);
    for(size_t j = 0; j < num_itr; ++j)
      f(i);

    // calculate time
    high_resolution_clock::time_point stop = high_resolution_clock::now();
    duration<double> diff = duration_cast<duration<double>>(stop - start);

    cout << setw(15) << diff.count() / num_itr << endl;
  }
}

/// @brief Main function to time all your functions
int main() {
  time_function(insert_n_linear_height_tree, pow(2, 15), "Linear height n inserts");
  time_function(insert_n_logarithmic_height_tree, pow(2, 22), "Logarithmic height n inserts");
  time_function(insert_n_random, pow(2, 20), "Random n inserts");
}
