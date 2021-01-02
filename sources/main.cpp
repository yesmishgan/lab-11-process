// Copyright 2020 Your Name dolbnin@protonmail.com

#include <async++.h>
#include <boost/process.hpp>
#include <boost/program_options.hpp>
#include <ctime>
#include <iostream>

namespace po = boost::program_options;
namespace bp = boost::process;

int main(int ac, char** av) {
  po::options_description desc("Usage: builder [options]\nAllowed options");
  int test;
  time_t timeout;
  desc.add_options()("help", "produce help message")(
      "config", po::value<int>(&test),
      "Specify the build configuration (default is Debug)")(
      "install", "Add step of install (to the directory _install)")(
      "pack", "Add step of packing (to the archive tar.gz format)")(
      "timeout", po::value<time_t>(&timeout), "Set a waiting time");

  po::variables_map vm;
  po::store(po::parse_command_line(ac, av, desc), vm);
  bp::child c("ls");
  po::notify(vm);
  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }
  int ret = system("ls");
  std::cout << test << " " << timeout << " " << ret << '\n' << system("ls");
  return 0;
}
