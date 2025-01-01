#include "Memory_View.h"

extern size_t __stack;
extern void* __brkval;
extern size_t __heap_start;
extern size_t __bss_end;


bool isFirst = true;
uint16_t counter=1;

void Memory_View::showMemory() {
    const size_t stack_ptr_ = stack_ptr_addr();

    Serial.print(F("Free space________________: "));
    Serial.println(stack_ptr_ - reinterpret_cast<size_t>(__brkval));

    Serial.print(F("Starting Stack address_: "));
    Serial.print(stack_ptr_);
    Serial.print(F(" "));
    Serial.println(stack_ptr_, HEX);

    Serial.print(F("Ending Stack address___: "));
    Serial.print(reinterpret_cast<size_t>(&__stack));
    Serial.print(F(" "));
    Serial.println(reinterpret_cast<size_t>(&__stack), HEX);

    Serial.print(F("Total Stack____________: "));
    Serial.println(reinterpret_cast<size_t>(&__stack) - stack_ptr_);

    Serial.println();

    Serial.print(F("Ending Heap address_______: "));
    Serial.print(reinterpret_cast<size_t>(__brkval));
    Serial.print(F(" "));
    Serial.println(reinterpret_cast<size_t>(__brkval), HEX);

    Serial.print(F("Starting Heap Address_____: "));
    Serial.print(reinterpret_cast<size_t>(&__heap_start));
    Serial.print(F(" "));
    Serial.println(reinterpret_cast<size_t>(&__heap_start), HEX);

    Serial.print(F("Total Heap________________: "));
    Serial.println(reinterpret_cast<size_t>(__brkval) - reinterpret_cast<size_t>(&__heap_start));

    Serial.println();

    Serial.print(F("Ending BSS address________: "));
    Serial.print(reinterpret_cast<size_t>(&__bss_end));
    Serial.print(F(" "));
    Serial.println(reinterpret_cast<size_t>(&__bss_end), HEX);

    Serial.print(F("Space between BSS and heap: "));
    Serial.println(reinterpret_cast<size_t>(&__heap_start) - reinterpret_cast<size_t>(&__bss_end));

    Serial.print(F("Total usable memory:"));
    Serial.println(reinterpret_cast<size_t>(&__stack) - reinterpret_cast<size_t>(&__bss_end));


    Serial.println(F("----------------------"));
    Serial.println();
}

void Memory_View::showMemoryCsv(const byte identifier) {
    const size_t stack_prt = stack_ptr_addr();

    if(isFirst) {
        isFirst = false;
        Serial.println(F("SI,id,Starting Stack Address,Ending Stack Address,Total Stack,Free Space,Ending Heap Address,Starting Heap Address,Total Heap,Ending BSS Address,Space Between BSS and Heap,Total Usable Memory (Stack),Total Usable Memory (BSS),Total Usable Memory (Total)"));
    }

    Serial.print(counter++);
    Serial.print(",");
    Serial.print(identifier);
    Serial.print(",");
    Serial.print(stack_prt);
    Serial.print(",");
    Serial.print(reinterpret_cast<size_t>(&__stack));
    Serial.print(",");
    Serial.print(reinterpret_cast<size_t>(&__stack) - stack_prt);
    Serial.print(",");
    Serial.print(stack_prt - reinterpret_cast<size_t>(__brkval));
    Serial.print(",");
    Serial.print(reinterpret_cast<size_t>(__brkval));
    Serial.print(",");
    Serial.print(reinterpret_cast<size_t>(&__heap_start));
    Serial.print(",");
    Serial.print(reinterpret_cast<size_t>(__brkval) - reinterpret_cast<size_t>(&__heap_start));
    Serial.print(",");
    Serial.print(reinterpret_cast<size_t>(&__bss_end));
    Serial.print(",");
    Serial.print(reinterpret_cast<size_t>(&__heap_start) - reinterpret_cast<size_t>(&__bss_end));
    Serial.print(",");
    Serial.print(reinterpret_cast<size_t>(&__stack));
    Serial.print(",");
    Serial.print(reinterpret_cast<size_t>(&__bss_end));
    Serial.print(",");
    Serial.println(reinterpret_cast<size_t>(&__stack) - reinterpret_cast<size_t>(&__bss_end));
}

size_t Memory_View::stack_ptr_addr() {
    uint16_t stack_pointer;
    asm volatile (
        "in %A0, __SP_L__ \n\t"
        "in %B0, __SP_H__"
        : "=r" (stack_pointer)
    );
    return stack_pointer;
}


size_t Memory_View::stack_origin_addr() {
    return reinterpret_cast<size_t>(&__stack);
}
size_t Memory_View::heap_ptr_addr() {
    return reinterpret_cast<size_t>(__brkval);
}

size_t Memory_View::heap_origin_addr() {
    return reinterpret_cast<size_t>(&__heap_start);
}
size_t Memory_View::bss_end_addr() {
    return reinterpret_cast<size_t>(&__bss_end);
}
size_t Memory_View::bss_heap_size() {
    return reinterpret_cast<size_t>(&__heap_start) - reinterpret_cast<size_t>(&__bss_end);
}

size_t Memory_View::stack_size(const uint16_t stack_ptr) {
    return reinterpret_cast<size_t>(&__stack) - stack_ptr;
}
size_t Memory_View::stack_size() {
    return reinterpret_cast<size_t>(&__stack) - stack_ptr_addr();
}

size_t Memory_View::free_space(const uint16_t stack_ptr) {
    return stack_ptr - reinterpret_cast<size_t>(__brkval);
}
size_t Memory_View::free_space() {
    return stack_ptr_addr() - reinterpret_cast<size_t>(__brkval);
}

size_t Memory_View::heap_size() {
    return reinterpret_cast<size_t>(__brkval) - reinterpret_cast<size_t>(&__heap_start);
}


size_t Memory_View::total_memory() {
    return reinterpret_cast<size_t>(&__stack) - reinterpret_cast<size_t>(&__bss_end);
}

float Memory_View::percentOfMemory(const size_t mem, const size_t totalMemory) {
    if(totalMemory) {
        return (mem / static_cast<float>(totalMemory)) * 100.0f;
    }return (mem / static_cast<float>(total_memory())) * 100.0f;
}