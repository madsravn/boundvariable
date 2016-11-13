#include "memory.h"
#include <iostream>

Memory::Memory() {
    pc = 0;
}

Memory& Memory::operator>>(numtype& x) {
    x = ops.at(0).at(pc);
    ++pc;
    return (*this);
}

void
Memory::load(std::string file) {
    std::ifstream read(file, std::ios::binary);
    std::istreambuf_iterator<char> i(read), e;
    std::vector<unsigned char> inf (i,e);
    ops.push_back(std::vector<numtype>());

    for(auto i = 0; i < inf.size(); i += 4) {
        ops.at(0).push_back((inf.at(i) << 24) | (inf.at(i +1) << 16) | (inf.at(i +2) << 8) | (inf.at(i +3)));
    }
}

Memory::Memory(std::string file) {
    load(file);
    pc = 0;
}

void
Memory::setPC(int x) {
    pc = x;
}

int
Memory::getPC() {
    return pc;
}

int
Memory::getMem(int array, int pos) {
    return ops.at(array).at(pos);
}

std::vector<numtype>
Memory::getMem(int array) {
    return ops.at(array);
}

void
Memory::setMem(int array, std::vector<numtype> vec) {
    ops.at(array) = vec;
}

void
Memory::setMem(int array, int pos, int value) {
    ops.at(array).at(pos) = value;
}

int
Memory::newArray(int size) {

    std::vector<numtype> vec(size, 0);

    // Try to find an empty array in the memory
    for(int i = 1; i < ops.size(); ++i) {
        if(ops.at(i).size() == 0) {
            ops.at(i) = vec;
            return i;
        }
    }
    ops.push_back(vec);
    return ops.size()-1;
}

void
Memory::clearArray(int pos) {
    std::vector<numtype> vec(0,0);
    ops.at(pos) = vec;
}
