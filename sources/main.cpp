// Copyright 2020 Your Name dolbnin@protonmail.com

#include <async++.h>
#include <boost/process.hpp>
#include <boost/program_options.hpp>
#include <boost/process/child.hpp>
#include <iostream>
#include <boost/filesystem.hpp>
#include <Builder.hpp>

namespace po = boost::program_options;
namespace bp = boost::process;

int main(int argc, char *argv[]) {
  Builder build;
  if (build.initBuild(argc, argv)){
    return EXIT_SUCCESS;
  }
  build.startBuild();
  std::cout << "TEST OUT";
  return 0;
}
