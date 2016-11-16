#ifndef VM_H_
#define VM_H_
#include "memory.h"
#include <functional>

class VM {

    public: 
        void run();
        VM(std::string file);

    private:
        std::vector<std::function<void(numtype)>> prepareInstructions();
        std::vector<char> input;
        // #0. Conditional Move.
        void condMove(numtype num);
        // #1. Array Index.
        void arrayIndex(numtype num);
        // #2. Array Amendment.
        void arrayAmendment(numtype num);
        // #3. Addition.
        void addition(numtype num);
        // #4. Multiplication.
        void multiplication(numtype num);
        // #5. Division.
        void division(numtype num);
        // #6. Not-And.
        void notAnd(numtype num);
        // #7. Halt.
        void halt(numtype num);
        // #8. Allocation.
        void allocation(numtype num);
        // #9. Abandonment.
        void abandonment(numtype num);
        // #10. Output.
        void output(numtype num);
        // #11. Input.
        void inputcmd(numtype num);
        // #12. Load Program.
        void loadProgram(numtype num);
        // #13. Orthography.
        void orthography(numtype num);

        std::vector<numtype> reg;
        Memory mem;
        
};


#endif
