
struct App {
  App(const Params& p);
  void run();
  void printParams();
  void readImages(std::string leftfn, std::string rightfn, cv::Mat &left, cv::Mat &right);
  void remapImages(Pair campair, cv::Mat left, cv::Mat right, cv::Mat left_rect, cv::Mat right_rect);
  Pair readProperties(std::string intrinsicfn, std::string extrinsicfn);
private:
  Params p;
  bool running;
};
