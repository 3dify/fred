
struct App {
  App(const Params& p);
  void run();
  void printParams();
  void readImages(std::string leftfn, std::string rightfn, cv::Mat &left, cv::Mat &right);
  void remap(Pair campair, cv::Mat &rmap[][2]);
  Pair readProperties(std::string intrinsicfn, std::string extrinsicfn);
private:
  Params p;
  bool running;
};
