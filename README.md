# Arduino_Memory_Viewer

## Overview
This project provides a `Memory_View` class to view and analyze memory usage in an Arduino environment. It includes methods to display memory information, calculate memory sizes, and determine free space.

## Features
- Display detailed memory information.
- Show memory information in CSV format.
- Calculate various memory addresses and sizes.
- Determine the percentage of used memory.

## File Structure
- `src/main.cpp`: Main application file.
- `lib/Memory_View/Memory_View.h`: Header file for the `Memory_View` class.
- `lib/Memory_View/Memory_View.cpp`: Implementation file for the `Memory_View` class.

## Memory Layout
  ```plaintext
                0x0000
                   +---------------+
              +--> | Code Segment  |
              |    +---------------+
    Constant<-|    | Data Segment  |
    Memory    |    +---------------+
              +--> |  bss Segment  |
                   +---------------+ <-- bss_end_addr
                     bss_heap_size
                   +---------------+ <-- heap_origin_addr
              +--> |     Heap      |
              |    |   heap_size   |
              |    +---------------+ <-- heap_ptr_addr
    Dynamic<--|    |  Free Memory  |
    Memory    |    |  free_space   |
    (total_memory) +---------------+ <-- stack_ptr_addr
              |    |     Stack     |
              |    |   stack_size  |
              +--> +---------------+ <-- stack_origin_addr
                  0xFFFF
  ```

                
## Usage
1. **Include the `Memory_View` class in your project:**
    ```cpp
    #include <Memory_View.h>
    ```

2. **Initialize the Serial monitor in the `setup` function:**
    ```cpp
    void setup() {
        Serial.begin(115200);
        Memory_View::showMemory();
    }
    ```

3. **Display memory information in the `loop` function:**
    ```cpp
    void loop() {
        Memory_View::showMemory();
        delay(1000);
    }
    ```

## Methods
- `static void showMemory()`: Displays memory information.
- `static void showMemoryCsv(byte identifier = 0)`: Displays memory information in CSV format.
- `static size_t stack_ptr_addr()`: Gets the current stack pointer address.
- `static size_t stack_origin_addr()`: Gets the origin address of the stack.
- `static size_t heap_ptr_addr()`: Gets the current heap pointer address.
- `static size_t heap_origin_addr()`: Gets the origin address of the heap.
- `static size_t bss_end_addr()`: Gets the end address of the BSS segment.
- `static size_t bss_heap_size()`: Calculates the size between the BSS end and heap start.
- `static size_t stack_size(uint16_t stack_ptr)`: Calculates the size of the stack.
- `static size_t stack_size()`: Calculates the size of the stack.
- `static size_t free_space(uint16_t stack_ptr)`: Calculates the free space in memory.
- `static size_t free_space()`: Calculates the free space in memory.
- `static size_t heap_size()`: Calculates the size of the heap.
- `static size_t total_memory()`: Calculates the total usable memory.
- `static float percentOfMemory(size_t mem, size_t totalMemory = 0)`: Calculates the percentage of used memory.


