// Copyright 2020 Your Name dolbnin@protonmail.com

#ifndef INCLUDE_BUILDER_HPP_
#define INCLUDE_BUILDER_HPP_

#include <async++.h>
#include <boost/program_options.hpp>
#include <ctime>
#include <list>
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
#include <boost/process.hpp>

namespace po = boost::program_options;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;
namespace bp = boost::process;

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
