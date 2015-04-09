#include "cam.h"

struct Pair {
  cv::Mat R;
  cv::Mat T;
  cv::Mat Q;
  Cam left;
  Cam right;
};

