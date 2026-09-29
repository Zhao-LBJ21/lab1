#include "random_vector.h"

#include <cstdlib>
#include <stdexcept>

RandomVector::RandomVector(int size, double max_val) {
  if (size < 0 || max_val < 0.0) {
    throw std::invalid_argument("size and max_val must be nonnegative");
  }

  // main.cpp sets a fixed seed, so these random values are reproducible.
  for (int i = 0; i < size; ++i) {
    double unit = static_cast<double>(std::rand()) / RAND_MAX;
    vect.push_back(unit * max_val);
  }
}

void RandomVector::print() {
  for (std::size_t i = 0; i < vect.size(); ++i) {
    if (i != 0) std::cout << ' ';
    std::cout << vect[i];
  }
  std::cout << std::endl;
}

double RandomVector::mean() {
  if (vect.empty()) return 0.0;
  double sum = 0.0;
  for (double value : vect) sum += value;
  return sum / vect.size();
}

double RandomVector::max() {
  if (vect.empty()) return 0.0;
  double largest = vect[0];
  for (double value : vect) {
    if (value > largest) largest = value;
  }
  return largest;
}

double RandomVector::min() {
  if (vect.empty()) return 0.0;
  double smallest = vect[0];
  for (double value : vect) {
    if (value < smallest) smallest = value;
  }
  return smallest;
}

void RandomVector::printHistogram(int bins) {
  if (bins <= 0 || vect.empty()) return;

  std::vector<int> counts(bins, 0);
  const double lower = min();
  const double upper = max();

  for (double value : vect) {
    int index = 0;
    if (upper > lower) {
      index = static_cast<int>((value - lower) / (upper - lower) * bins);
      if (index == bins) index = bins - 1; // Put the maximum in the last bin.
    }
    ++counts[index];
  }

  int height = 0;
  for (int count : counts) {
    if (count > height) height = count;
  }
  for (int level = height; level > 0; --level) {
    for (int bin = 0; bin < bins; ++bin) {
      std::cout << (counts[bin] >= level ? "***" : "   ");
      if (bin + 1 < bins) std::cout << ' ';
    }
    std::cout << std::endl;
  }
}
