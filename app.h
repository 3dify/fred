
struct App {
  App(const Params& p);
  void run();
  void printParams();
  Pair readProperties(std::string intrinsicfn, std::string extrinsicfn);
private:
  Params p;
  bool running;
};
