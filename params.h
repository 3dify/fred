
struct Params {
  static Params read(int argc, char** argv);
  static Params printHelp();
  std::string left;
  std::string right;
  std::string output;
  std::string squareSize;
  std::string boardWidth;
  std::string boardHeight;
  
  std::string intrinsic;
  std::string extrinsic;
  

};


