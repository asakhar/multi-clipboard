#include "argparse.hpp"

namespace argparse {
Args::Args(int c, char **v) : argv(c) {
  for (int i = 0; i < c; ++i)
    argv[i] = v[i];
}
} // namespace argparse
