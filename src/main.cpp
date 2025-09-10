#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unistd.h>     // fork, execvp, chdir
#include <sys/wait.h>   // waitpid
#include <cstring>      // strerror
#include <cstdlib>      // getenv
#include <cerrno>

void print_prompt() {
    std::cout << "$ " << std::flush;
}

std::vector<std::string> tokenize(const std::string& line) {
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string tok;
    while (iss >> tok) {
        tokens.push_back(tok);
    }
    return tokens;
}

// This function will handle the cd and exit commands itself
bool run_builtin(const std::vector<std::string>& args) {
    if (args.empty()) return true;
    const std::string& cmd = args[0];

    if (cmd == "exit") {
        std::exit(0);
    }
    if (cmd == "cd") {
        const char* path;
        if (args.size() >= 2) {
            path = args[1].c_str();
        } else {
            path = std::getenv("HOME");
            if (!path) {
                std::cerr << "cd: HOME not set\n";
                return true;
            }
        }
        if (chdir(path) != 0) {
            std::cerr << "cd: " << path << ": " << std::strerror(errno) << "\n";
        }
        return true;
    }
    // tells main() that this is not a built in and to try
    // an external program
    return false;

}

void run_external(const std::vector<std::string>& args) {
    std::vector<char*> argv;
    for (const auto& s : args) {
        argv.push_back(const_cast<char*>(s.c_str()));
    }
    argv.push_back(nullptr);

    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "fork failed: " << std::strerror(errno) << "\n";
        return;
    }
    if (pid == 0) {
        // Child process
        execvp(argv[0], argv.data());
        std::cerr << argv[0] << ": " << std::strerror(errno) << "\n";
        _exit(127);
    } else {
        // Parent waits
        int status;
        waitpid(pid, &status, 0);
    }
}

int main() {
    while (true) {
        print_prompt();

        std::string line;
        if (!std::getline(std::cin, line)) {
            std::cout << "\n";
            break; // Ctrl-D exits
        }

        auto args = tokenize(line);
        if (args.empty()) continue;

        if (!run_builtin(args)) {
            run_external(args);
        }
    }
    return 0;
}
