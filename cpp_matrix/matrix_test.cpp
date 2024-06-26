#include "matrix_lib/matrix_lib.hpp"
#include <iostream>

int main() {
  // clang-format off
  matrix::Matrix<int> m{
    {1,  1000},
    {25, 1}
  };
  // clang-format on
  // 2 x 2 matrix.

  std::cout << "Original matrix m =" << std::endl
            << std::string(m) << std::endl;

  // Modify to identity matrix.

  int &entry = m(0, 1);
  entry = 0;
  m(1, 0) = 0;

  std::cout << std::endl
            << "Modified matrix m =" << std::endl
            << std::string(m) << std::endl;

  matrix::Matrix<int> sProdM = 247 * m;
  // Assignment move (C++ <17) or elide copy (for C++ >=17).

  std::cout << std::endl
            << "Scalar multiple 247 * m =" << std::endl
            << std::string(sProdM) << std::endl;

  matrix::Vector<double> v(2);
  v[0] = 0.1;
  v[1] = 1.2;

  std::cout << std::endl
            << "Vector v =" << std::endl
            << std::string(v) << std::endl;

  v[0] = 7.1;

  std::cout << std::endl
            << "Modified vector v =" << std::endl
            << std::string(v) << std::endl;

  matrix::Vector<double> sProdV = 2.0 * v;

  std::cout << std::endl
            << "Vector 2 * v =" << std::endl
            << std::string(sProdV) << std::endl;

  m(0, 0) = 2;
  m(1, 1) = 3;

  std::cout << std::endl
            << "Modified matrix m =" << std::endl
            << std::string(m) << std::endl;

  matrix::Matrix<int> product = m * m;

  std::cout << std::endl
            << "Product m * m =" << std::endl
            << std::string(product) << std::endl;

  matrix::Matrix<int> n{1, 2};
  n(0, 0) = 6;
  n(0, 1) = 42;

  std::cout << std::endl
            << "Matrix n =" << std::endl
            << std::string(n) << std::endl;

  matrix::Matrix<int> prodNM = n * m;

  std::cout << std::endl
            << "Product n * m =" << std::endl
            << std::string(prodNM) << std::endl;

  return EXIT_SUCCESS;
}
