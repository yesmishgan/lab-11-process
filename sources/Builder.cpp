// Copyright 2020 Your Name dolbnin@protonmail.com

#include "Builder.hpp"
#include <boost/process.hpp>

void timeCounter(const time_t& timeout, std::unique_ptr<bp::child>& process){
  if (timeout <= 0){
    return;
  }
  time_t start = time(nullptr);
  time_t end = time(nullptr);
  while (end - start < timeout){
    end = time(nullptr);
  }
  std::cerr << "Time is ended!";
  process->terminate();
}

const std::list<std::string> Builder::getArgs(int proc) {
  switch (proc) {
    case 0:
      return {"-H.", "-B" + std::string(buildDir),
              "-DCMAKE_INSTALL_PREFIX=" + std::string(installDir),
              "-DCMAKE_BUILD_TYPE=" + buildConfig};
    case 1:
      return {"--build", buildDir};
    case 2:
      return {"--build", buildDir,
              "--target", "install"};
    case 3:
      return {"--build", "_builds",
              "--target", "package"};
    default:
      return {"--help"};
  }
}

void Process(std::unique_ptr<bp::child>& process,
             std::list<std::string>& args,
             int& flag){
  if (flag != 0) return;
  bp::ipstream pipe_stream;
  process = std::make_unique<bp::child>(
      bp::child{bp::search_path("cmake"),
                bp::args(args),
                bp::std_out > pipe_stream});

  for (std::string line;
       process->running() && std::getline(pipe_stream, line);)
    std::cout << line << std::endl;
  process->wait();
  flag = process->exit_code();
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
  if ((buildConfig != "Release") && (buildConfig != "Debug")){
    throw std::invalid_argument("Build config is invalid!");
  }
  return 0;
}

int Builder::startBuild() {
  auto timer = async::spawn(std::bind(&timeCounter,
                                      std::ref(timeout),
                                      std::ref(process)));
  auto my_task1 = async::spawn(std::bind(&Process,
                                         std::ref(process),
                                         getArgs(0),
                                         std::ref(errorComp)));
  my_task1.wait();
  auto my_task2 = my_task1.then(std::bind(&Process,
                                          std::ref(process),
                                          getArgs(1),
                                          std::ref(errorComp)));
  if (isInstall){
    my_task2 = my_task2.then(std::bind(&Process,
                                            std::ref(process),
                                            getArgs(2),
                                       std::ref(errorComp)));
  }
  if (isPack){
    my_task2 = my_task2.then(std::bind(&Process,
                                            std::ref(process),
                                            getArgs(3),
                                       std::ref(errorComp)));
  }
  my_task2.wait();
  timer.wait();
  return 0;
}
