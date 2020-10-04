#include <iostream>
#include <math.h>
#include "server/server.h"
#include <string>
#include <fstream>

struct Config {
  size_t threadLimit;
  size_t maxConnections;
  std::string documentRoot;
};

Config ParseConfig() {
    Config config{0,0, std::string("")};
    // /home/alexandr/Projects/fast-web-server
    std::ifstream file("/home/alexandr/Projects/fast-web-server/httpd.conf");
    //std::ifstream file("httpd.conf");
    std::string line;
    int pos;

    if (file) {
        std::getline(file, line);
        pos = line.find(' ');
        std::string value = line.substr(pos + 1, line.length());
        try {
            config.threadLimit = std::stoi(value);
        }
        catch (...) {
            std::cerr << "Thread limit is not a number\n";
        }

        std::getline(file, line);
        pos = line.find(' ');
        std::string mConn = line.substr(pos + 1, line.length());
        try {
            config.maxConnections = std::stoi(mConn);
        }
        catch (...) {
            std::cerr << "Thread limit is not a number\n";
        }


        std::getline(file, line);
        pos = line.find(' ');
        config.documentRoot = line.substr(pos + 1, line.length());
    } else {
        std::cerr << "Can't read config file\n";
    }

    return config;
}

int main() {
    std::string address = "127.0.0.1";
    auto port = 8080;
    auto config = ParseConfig();


    try {
        Server::Start(address, port, config.maxConnections, config.threadLimit, config.documentRoot).Run();
    }
    catch (const char * msg) {
        std::cerr << msg << std::endl;
    }
    catch (...) {
        std::cerr << "Error" << std::endl;
    }


    return 0;
}
