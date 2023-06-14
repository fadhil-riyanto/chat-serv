#ifndef PARSECMD_H
#define PARSECMD_H
#include <cstddef>

class parse_cmd {
    private:
    int argc;
    char **argv;

    public:
    parse_cmd(int argc, char **argv);
    int get(const char *param, char **ret);
    
};

#endif