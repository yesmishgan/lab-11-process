// Copyright 2020 Your Name dolbnin@protonmail.com

#include "Builder.hpp"

int Builder::initBuild(int argc, char **argv) {
  po::options_description desc("Usage: builder [options]\nAllowed options");

  desc.add_options()(
      "help", "produce help message")(
      "config", "Specify the build configuration (default is Debug)")(
      "install", "Add step of install (to the directory _install)")(
      "pack", "Add step of packing (to the archive tar.gz format)")(
      "timeout", po::value<time_t>(&timeout),
          "Set a waiting time");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }

  if ((vm.count("config")) && (vm["config"].as<std::string>() == "Release")){
    buildConfig = 1;
  }

  if (vm.count("install")){
    isInstall = 1;
  }

  if (vm.count("pack")){
    isPack = 1;
  }

  //std::cout << "OK";
  return 0;
}
