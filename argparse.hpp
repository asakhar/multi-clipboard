#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace argparse {
// Stores arguments (e.g. command line args)
class Args {
  // Container
  std::vector<std::string> argv;

public:
  // Default constructor
  // @argc - arguments count
  // @argv - arguments array
  Args(int argc, char **argv);

  // Begin const iterator
  auto begin() const { return argv.begin(); }
  // End const iterator
  auto end() const { return argv.end(); }

private:
  // Recursion bottom
  bool option_check(std::string const &option) const {
    return std::find(begin(), end(), option) != end();
  }

  // Recursion bottom
  std::string option_get(std::string const &option) const {
    auto pos = std::find(begin(), end(), option);
    if (pos < end() - 1)
      return *(pos + 1);
    return "";
  }

public:
  // Check if Args has @option or at least one of its @aliases specified
  template <typename... _Ty>
  bool option_check(std::string const &option, _Ty... aliases) const {
    return (std::find(begin(), end(), option) != end()) ||
           option_check(aliases...);
  }

  // Get parameter specified right arter @option or one of its @aliases
  template <typename... _Ty>
  std::string option_get(std::string const &option, _Ty... aliases) const {
    if (option_check(option))
      return option_get(option);
    return option_get(aliases...);
  }
};
} // namespace argparse
