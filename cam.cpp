#include "fred.h"

using namespace cv;

Cam::Cam(const Mat M, const Mat D, const Mat R, const Mat P)
: M(M), D(D), R(R), P(P) {};
  
