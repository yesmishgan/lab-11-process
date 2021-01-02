// Copyright 2020 Your Name dolbnin@protonmail.com

#include <async++.h>
#include <boost/process.hpp>
#include <boost/program_options.hpp>
#include <boost/process/child.hpp>
#include <iostream>
#include <Builder.hpp>

namespace po = boost::program_options;
namespace bp = boost::process;

bp::child hello(){
  std::cout << "d";
  return bp::child(0);
}

int main(int argc, char *argv[]) {
  Builder build;
  if (build.initBuild(argc, argv)){
    return EXIT_SUCCESS;
  }
  bp::child c = hello();
  return 0;
}
