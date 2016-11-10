#include "VM.h"
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <tuple>

VM::VM(std::string file) {
    mem.load(file);
    reg.insert(std::begin(reg), 8, 0);
}

std::tuple<int, int, int> extract(numtype num) {
    int a,b,c;
    a = num & 0b111000000;
    b = num & 0b111000;
    c = num & 0b111;
    return std::make_tuple(a,b,c);
}


void
VM::condMove(numtype num) {
    int a,b,c;
    std::tie(a,b,c) = extract(num);



}
/*
void
VM::halt() {
    std::cout << "Halting at " << mem.getPC() << std::endl;
    std::exit(EXIT_FAILURE);

}

void 
VM::set(){
    numtype a,b;
    mem >> a >> b;
    write_value(a,read_value(b));

}

void 
VM::push(){
    numtype a;
    mem >> a;
    stack.push_back(read_value(a));
}

void 
VM::pop(){
    numtype a;
    mem >> a;
    numtype s = stack.back();
    stack.pop_back();
    write_value(a, s);
}

void 
VM::eq(){
    numtype a,b,c;
    mem >> a >> b >> c;
    if(read_value(b) == read_value(c)) {
        write_value(a,1);
    } else {
        write_value(a,0);
    }
}

void 
VM::gt(){
    numtype a,b,c;
    mem >> a >> b >> c;
    if(read_value(b) > read_value(c)) {
        write_value(a,1);
    } else {
        write_value(a,0);
    }
}

void 
VM::jmp(){
    numtype a;
    mem >> a;
    a = read_value(a);
    mem.setPC(a);

}

void 
VM::jt(){
    numtype a,b;
    mem >> a >> b;
    a = read_value(a);
    b = read_value(b);
    if(a != 0) {
        mem.setPC(b);
    }
}

void 
VM::jf(){
    numtype a,b;
    mem >> a >> b;
    a = read_value(a);
    b = read_value(b);
    if(a == 0) {
        mem.setPC(b);
    }
}

void 
VM::add(){
    numtype a,b,c;
    mem >> a >> b >> c;
    write_value(a, (read_value(b) + read_value(c)) % 32768);
}

void 
VM::mult(){
    numtype a,b,c;
    mem >> a >> b >> c;
    write_value(a, (read_value(b) * read_value(c)) % 32768);
}

void 
VM::mod(){
    numtype a,b,c;
    mem >> a >> b >> c;
    write_value(a, read_value(b) % read_value(c));

}

void 
VM::tand(){
    numtype a,b,c;
    mem >> a >> b >> c;
    write_value(a, read_value(b) & read_value(c)); 
}

void 
VM::tor(){
    numtype a,b,c;
    mem >> a >> b >> c;
    write_value(a, (read_value(b) | read_value(c)));
}

void 
VM::tnot(){
    numtype a,b;
    mem >> a >> b;
    numtype c = read_value(b);
    c = ~c;
    c = c & 0b0111111111111111;
    write_value(a, c);
}

void 
VM::rmem(){
    numtype a,b;
    mem >> a >> b;
    numtype data = mem.getMem(read_value(b));
    write_value(a, data);
}

void 
VM::wmem(){
    numtype a,b;
    mem >> a >> b;
    mem.setMem(read_value(a),read_value(b));
}

void 
VM::call(){
    numtype a;
    mem >> a;
    stack.push_back(mem.getPC());
    mem.setPC(read_value(a));
}

void 
VM::ret(){
    numtype a = stack.back();
    stack.pop_back();
    mem.setPC(a);
}

void 
VM::out(){
    numtype x;
    mem >> x;

    std::cout << (char)read_value(x);
}

void 
VM::in(){
    if(input.empty()) {
        std::cout << std::endl << "Input: ";
        std::string str;
        std::getline(std::cin, str);
        std::copy(std::begin(str), std::end(str), std::back_inserter(input));
        input.push_back(10);
        std::reverse(std::begin(input), std::end(input));
    }
    char c = input.back();
    input.pop_back();
    numtype a;
    mem >> a;
    write_value(a,c);
}

void 
VM::noop(){

}
*/


std::vector<std::function<void(numtype)>> 
VM::prepareInstructions() {
    std::vector<std::function<void(numtype)>> instr;
    /*instr.push_back(std::bind(&VM::halt, this));
    instr.push_back(std::bind(&VM::set, this));
    instr.push_back(std::bind(&VM::push, this));
    instr.push_back(std::bind(&VM::pop, this));
    instr.push_back(std::bind(&VM::eq, this));
    instr.push_back(std::bind(&VM::gt, this));
    instr.push_back(std::bind(&VM::jmp, this));
    instr.push_back(std::bind(&VM::jt, this));
    instr.push_back(std::bind(&VM::jf, this));
    instr.push_back(std::bind(&VM::add, this));
    instr.push_back(std::bind(&VM::mult, this));
    instr.push_back(std::bind(&VM::mod, this));
    instr.push_back(std::bind(&VM::tand, this));
    instr.push_back(std::bind(&VM::tor, this));
    instr.push_back(std::bind(&VM::tnot, this));
    instr.push_back(std::bind(&VM::rmem, this));
    instr.push_back(std::bind(&VM::wmem, this));
    instr.push_back(std::bind(&VM::call, this));
    instr.push_back(std::bind(&VM::ret, this));
    instr.push_back(std::bind(&VM::out, this));
    instr.push_back(std::bind(&VM::in, this));
    instr.push_back(std::bind(&VM::noop, this));
    */
    instr.push_back(std::bind(&VM::condMove, this, std::placeholders::_1));
    return instr;
}


void
VM::run() {
    std::vector<std::function<void(numtype)>> instructions = prepareInstructions();
    int run = 0;
    numtype instr;
    while(true) {
        mem >> instr;
        std::cout << (instr >> 28) << std::endl;
        auto func = instructions.at(instr >> 28);
        func(instr);
    }

}

