#ifndef MEMORY_H_
#define MEMORY_H_
#include <string>
#include <vector>
#include <fstream>
#include <cstdint>

using numtype = std::uint32_t;

class Memory {
    public:
        Memory();
        Memory(std::string file);
        void load(std::string file);
        Memory& operator>>(numtype& x);
        void setPC(int x);
        int getPC();
        int getMem(int pos);
        void setMem(int pos, int val);

    private:
        std::vector<std::vector<numtype>> ops;
        int pc;
};

#endif

