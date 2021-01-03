// Copyright 2020 Your Name dolbnin@protonmail.com
/*
#include <async++.h>
#include <iostream>
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
}*/

#include <boost/process.hpp>
#include <iostream>

namespace bp = boost::process;

int main()
{
  bp::ipstream pipe_stream;
  bp::child c("gcc --version", bp::std_out > pipe_stream);

  std::string line;

  while (pipe_stream && std::getline(pipe_stream, line) && !line.empty())
    std::cerr << line << std::endl;

  c.wait();
}
