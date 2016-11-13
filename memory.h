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
        int getMem(int array, int pos);
        std::vector<numtype> getMem(int array);
        void setMem(int array, int pos, int val);
        void setMem(int array, std::vector<numtype> vec);
        int newArray(int size);
        void clearArray(int pos);

    private:
        std::vector<std::vector<numtype>> ops;
        int pc;
};

#endif

