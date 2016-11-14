#include "VM.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <tuple>
#include <cmath>

VM::VM(std::string file) {
    mem.load(file);
    reg.insert(std::begin(reg), 8, 0);
}

std::tuple<int, int, int> extract(numtype num) {
    int a,b,c;
    if(num >> 28 != 13) {
        a = (num & 0b111000000) >> 6;
        b = (num & 0b111000) >> 3;
        c = num & 0b111;
        return std::make_tuple(a,b,c);
    } else {
        a = (num >> 25) & 0b111;
        b = num & 0b1111111111111111111111111;
        return std::make_tuple(a,b,c);
    }
}


void
VM::condMove(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);
    if(reg.at(c)) {
        reg.at(a) = reg.at(b);
    }
}

void
VM::arrayIndex(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);
    reg.at(a) = mem.getMem(reg.at(b),reg.at(c));

}

void 
VM::arrayAmendment(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);
    mem.setMem(reg.at(a), reg.at(b), reg.at(c));
}

void 
VM::addition(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);
    reg.at(a) = (reg.at(b) + reg.at(c)) & 0b11111111111111111111111111111111;
}

void 
VM::multiplication(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);
    reg.at(a) = (reg.at(b) * reg.at(c)) & 0b11111111111111111111111111111111;
}

void 
VM::division(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);
    reg.at(a) = reg.at(b) / reg.at(c);
}

void 
VM::notAnd(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);
    reg.at(a) = ~(reg.at(b) & reg.at(c));
}

void
VM::halt(numtype num) {
    std::cout << "Halting at " << mem.getPC() << std::endl;
    std::exit(EXIT_FAILURE);
}

void 
VM::allocation(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);
    int placement = mem.newArray(reg.at(c));
    reg.at(b) = placement;
}

void
VM::abandonment(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);
    mem.clearArray(reg.at(c));
}

void
VM::output(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);
    std::cout << (char)reg.at(c);
}

void
VM::inputcmd(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);
    if(input.empty()) {
        std::cout << std::endl << "Input: ";
        std::string str;
        std::getline(std::cin, str);
        std::copy(std::begin(str), std::end(str), std::back_inserter(input));
        input.push_back(10);
        std::reverse(std::begin(input), std::end(input));
    }
    char k = input.back();
    input.pop_back();
    if(k == 10) {
        numtype end = (((1 >> 31) - 1) >> 1) + 1
        reg.at(c) = end;
    } else {
        reg.at(c) = k;
    }
}

void
VM::loadProgram(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);
    if(reg.at(b)) {
        std::vector<numtype> B = mem.getMem(reg.at(b));
        mem.setMem(0,B);
    }
    mem.setPC(reg.at(c));
}

void
VM::orthography(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);
    reg.at(a) = b;
}

std::vector<std::function<void(numtype)>> 
VM::prepareInstructions() {
    std::vector<std::function<void(numtype)>> instr;
    instr.push_back(std::bind(&VM::condMove, this, std::placeholders::_1));
    instr.push_back(std::bind(&VM::arrayIndex, this, std::placeholders::_1));
    instr.push_back(std::bind(&VM::arrayAmendment, this, std::placeholders::_1));
    instr.push_back(std::bind(&VM::addition, this, std::placeholders::_1));
    instr.push_back(std::bind(&VM::multiplication, this, std::placeholders::_1));
    instr.push_back(std::bind(&VM::division, this, std::placeholders::_1));
    instr.push_back(std::bind(&VM::notAnd, this, std::placeholders::_1));
    instr.push_back(std::bind(&VM::halt, this, std::placeholders::_1));
    instr.push_back(std::bind(&VM::allocation, this, std::placeholders::_1));
    instr.push_back(std::bind(&VM::abandonment, this, std::placeholders::_1));
    instr.push_back(std::bind(&VM::output, this, std::placeholders::_1));
    instr.push_back(std::bind(&VM::inputcmd, this, std::placeholders::_1));
    instr.push_back(std::bind(&VM::loadProgram, this, std::placeholders::_1));
    instr.push_back(std::bind(&VM::orthography, this, std::placeholders::_1));
    return instr;
}


void
VM::run() {
    std::vector<std::function<void(numtype)>> instructions = prepareInstructions();
    numtype instr;
    while(true) {
        mem >> instr;
        auto func = instructions.at(instr >> 28);
        func(instr);
    }

}

