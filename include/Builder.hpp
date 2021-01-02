// Copyright 2020 Your Name dolbnin@protonmail.com

#ifndef INCLUDE_BUILDER_HPP_
#define INCLUDE_BUILDER_HPP_

#include <async++.h>
#include <boost/process.hpp>
#include <boost/program_options.hpp>
#include <boost/process/child.hpp>
#include <ctime>
#include <string>
#include <iostream>

namespace po = boost::program_options;

const std::string buildDir = "_builds";
const std::string installDir = "_install";

class Builder {
 public:
  int initBuild(int argc, char **argv);
 private:
  time_t timeout = 0;
  bool isInstall = 0;
  bool isPack = 0;
  bool buildConfig = 0;
};

#endif  // INCLUDE_BUILDER_HPP_
