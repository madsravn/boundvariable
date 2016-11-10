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
        void condMove(numtype);

        // #1. Array Index.
        // #2. Array Amendment.
        // #3. Addition.
        // #4. Multiplication.
        // #5. Division.
        // #6. Not-And.
        // #7. Halt.
        // #8. Allocation.
        // #9. Abandonment.
        // #10. Output.
        // #11. Input.
        // #12. Load Program.
        // #13. Orthography.

        std::vector<numtype> reg;
        Memory mem;
        
};


#endif
