// Copyright 2020 Your Name dolbnin@protonmail.com

#include "Builder.hpp"

void timeCounter(time_t timeout){
  time_t start = time(nullptr);
  time_t end = time(nullptr);
  while (end - start < timeout){
    end = time(nullptr);
  }
  throw std::out_of_range("Time is ended");
}

int Builder::initBuild(int argc, char **argv) {
  po::options_description desc("Usage: builder [options]\nAllowed options");
  desc.add_options()(
      "help", "produce help message")(
      "config", po::value<std::string>(&buildConfig),
          "Specify the build configuration (default is Debug)")(
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

  if (vm.count("install")){
    isInstall = true;
  }

  if (vm.count("pack")){
    isPack = true;
  }
  return 0;
}

void Builder::startBuild() {
  std::cout << "Pack: " << isPack << std::endl <<
      "Config: " << buildConfig << std::endl;
  std::cout << "Build started!";
  auto my_task = async::spawn(std::bind(&timeCounter,
                                        std::ref(timeout)));
  while (!my_task.ready()) {
    std::cout << "wait..." << std::endl;
    sleep(1);
  }
  std::cout << "OK";
}
