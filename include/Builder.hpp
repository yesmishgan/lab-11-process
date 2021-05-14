// Copyright 2020 Your Name dolbnin@protonmail.com

#ifndef INCLUDE_BUILDER_HPP_
#define INCLUDE_BUILDER_HPP_

#include <async++.h>
#include <boost/program_options.hpp>
#include <ctime>
#include <list>
#include <string>
#include <iostream>
#include <boost/process.hpp>
#include <utility>
#include <memory>

namespace po = boost::program_options;
namespace bp = boost::process;

const char buildDir[] = "_builds";
const char installDir[] = "_install";

class Builder {
 public:
  int initBuild(int argc, char **argv);
  int startBuild();
  const std::list<std::string> getArgs(int proc);
 private:
  time_t timeout = 0;
  bool isInstall = false;
  bool isPack = false;
  std::string buildConfig = "Debug";
  std::unique_ptr<bp::child> process{nullptr};
  int errorComp = 0;
};

#endif  // INCLUDE_BUILDER_HPP_
