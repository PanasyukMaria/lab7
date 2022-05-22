// Copyright by PanasyukMaria

#include "http_server.h"

namespace po = boost::program_options;  // from <boost/program_options.hpp>

int main(int argc, char *argv[]) {

  std::shared_ptr<std::timed_mutex> mutex =
      std::make_shared<std::timed_mutex>();
  std::shared_ptr<JsonStorage> storage =
      std::make_shared<JsonStorage>("../suggestions.json");
  std::shared_ptr<CallSuggestions> suggestions =
      std::make_shared<CallSuggestions>();

  try {
    if (argc != 4) {
      std::cerr << "Usage: suggestion_server <address> <port> <doc_root>\n"
                << "Example:\n"
                << "    http-server-sync 0.0.0.0 8080\n";
      return EXIT_FAILURE;
    }
    auto const address = net::ip::make_address(argv[1]);
    auto const port = static_cast<uint16_t>(std::atoi(argv[2]));
    auto const doc_root = std::make_shared<std::string>(argv[3]);
    net::io_context ioc{1};
    tcp::acceptor acceptor {ioc, { address, port }};
    std::thread{suggestion_updater, storage, suggestions, mutex}.detach();
    for (;;) {
      tcp::socket socket{ioc};
      acceptor.accept(socket);
      std::thread{std::bind(
                      &do_session,
                      std::move(socket),
                      suggestions,
                      mutex)}.detach();
    }
  } catch (std::exception& e) {

    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}