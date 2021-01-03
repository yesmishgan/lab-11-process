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
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>

namespace po = boost::program_options;

const char buildDir[] = "_builds";
const char installDir[] = "_install";

class Builder {
 public:
  int initBuild(int argc, char **argv);
  void startBuild();
 private:
  time_t timeout = 0;
  bool isInstall = false;
  bool isPack = false;
  std::string buildConfig = "Debug";
};

#endif  // INCLUDE_BUILDER_HPP_
