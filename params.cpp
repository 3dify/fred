#include <string>

#include "params.h"

using namespace std;

Params Params::read(int argc, char** argv) {
  Params p;
  
  for (int i = 1; i < argc; i++) {
    if (string(argv[i]) == "--left") p.left = argv[++i];
    else if (string(argv[i]) == "--right") p.right = argv[++i];
    else if (string(argv[i]) == "--intrinsic") p.intrinsic = argv[++i];
    else if (string(argv[i]) == "--extrinsic") p.extrinsic = argv[++i];
    else if (string(argv[i]) == "--squareSize") p.squareSize = atof(argv[++i]);
    else if (string(argv[i]) == "--boardWidth") p.boardWidth = atof(argv[++i]);
    else if (string(argv[i]) == "--boardHeight") p.boardHeight = atof(argv[++i]);

    else throw runtime_error("unknown key: " + string(argv[i]));
  }

  return p;
}


