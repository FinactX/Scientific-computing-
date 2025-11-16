#ifndef ARRAY_H
#define ARRAY_H

#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()

template <class T> class Array {
private:
  int rows;
  int cols;
  T *data;

public:
  Array() : rows(0), cols(0), data(nullptr) {}

  Array(int nrows, int ncols) : rows(nrows), cols(ncols) {
    data = new T[nrows * ncols];
  }

  ~Array() { delete[] data; }

  inline T &operator()(int i, int j) { return data[i * cols + j]; }
  inline const T& operator()(int i, int j) const { return data[i * cols + j]; }

  int nrows() const { return rows; }

  int ncols() const { return cols; }

  void resize(int nrows, int ncols) {
    delete[] data;
    rows = nrows;
    cols = ncols;
    data = new T[nrows * ncols];
  }

  void initrandom(double min, double max) {
    srand(time(nullptr));
    for (int i = 0; i < rows * cols; ++i) {
      data[i] = min + (max - min) * rand() / RAND_MAX;
    }
  }
  void initzeros() {
    for (int i = 0; i < rows * cols; ++i) {
      data[i] = 0;
    }
  }
};

#endif // ARRAY_H

