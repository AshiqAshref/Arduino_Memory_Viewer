/**
* Memory Layout:
*                0x0000
*                 +---------------+
*            +--> | Code Segment  |
*            |    +---------------+
* Constant <-|    | Data Segment  |
*  Memory    |    +---------------+
*            +--> |  bss Segment  |
*                 +---------------+ <-- bss_end_addr
*                   bss_heap_size
*                 +---------------+ <-- heap_origin_addr
*            +--> |     Heap      |
*            |    |   heap_size   |
*            |    +---------------+ <-- heap_ptr_addr
* Dynamic <--|    |  Free Memory  |
*  Memory    |    |  free_space   |
* (total_memory)  +---------------+ <-- stack_ptr_addr
*            |    |     Stack     |
*            |    |   stack_size  |
*            +--> +---------------+ <-- stack_origin_addr
*                0xFFFF
*
*
*/


#ifndef MEMORY_VIEW_H
#define MEMORY_VIEW_H
#include <Arduino.h>

/**
 * \class Memory_View
 * \brief A class to view and analyze memory usage.
 * \author Ashiq A
 * \date 1/1/2025
 * \version 1.0
 *
 */
class Memory_View {
public:
    /**
     * \brief Displays memory information.
     * \details This function prints detailed memory information to the Serial monitor.
     * \note Ensure that the Serial monitor is initialized before calling this function.
     */
    static void showMemory();

    /**
     * \brief Displays memory information in CSV format.
     * \param identifier (Optional) use this to mark where you are calling from.
     * \details This function prints memory information in CSV format to the Serial monitor.
     * \note Ensure that the Serial monitor is initialized before calling this function.
     */
    static void showMemoryCsv(byte identifier = 0);

    /**
     * \brief Gets the current stack pointer address.
     * \return The current stack pointer address.
     * \details This function retrieves the current address of the stack pointer.
     */
    static size_t stack_ptr_addr();

    /**
     * \brief Gets the origin address of the stack.
     * \return The origin address of the stack.
     * \details This function retrieves the origin address of the stack.
     */
    static size_t stack_origin_addr();

    /**
     * \brief Gets the current heap pointer address.
     * \return The current heap pointer address.
     * \details This function retrieves the current address of the heap pointer.
     */
    static size_t heap_ptr_addr();

    /**
     * \brief Gets the origin address of the heap.
     * \return The origin address of the heap.
     * \details This function retrieves the origin address of the heap.
     */
    static size_t heap_origin_addr();

    /**
     * \brief Gets the end address of the BSS segment.
     * \return The end address of the BSS segment.
     * \details This function retrieves the end address of the BSS segment.
     */
    static size_t bss_end_addr();

    /**
     * \brief Calculates the size between the BSS end and heap start.
     * \return The size between the BSS end and heap start.
     * \details This function calculates the size of the memory between the end of the BSS segment and the start of the heap.
     */
    static size_t bss_heap_size();

    /**
     * \brief Calculates the size of the stack.
     * \param stack_ptr The current stack pointer.
     * \return The size of the stack.
     * \details This function calculates the size of the stack based on the current stack pointer.
     */
    static size_t stack_size(uint16_t stack_ptr);

    /**
     * \brief Calculates the size of the stack.
     * \return The size of the stack.
     * \details This function calculates the size of the stack.
     */
    static size_t stack_size();

    /**
     * \brief Calculates the free space in memory.
     * \param stack_ptr The current stack pointer.
     * \return The free space in memory.
     * \details This function calculates the free space in memory based on the current stack pointer.
     */
    static size_t free_space(uint16_t stack_ptr);

    /**
     * \brief Calculates the free space in memory.
     * \return The free space in memory.
     * \details This function calculates the free space in memory.
     */
    static size_t free_space();

    /**
     * \brief Calculates the size of the heap.
     * \return The size of the heap.
     * \details This function calculates the size of the heap.
     */
    static size_t heap_size();

    /**
     * \brief Calculates the total usable memory.
     * \return The total usable memory.
     * \details This function calculates the total dynamic memory available to use by the stack and the heap.
     * \note This does not return your total memory size. this is the dynamic memory available for your program after the code and data segments.
     */
    static size_t total_memory();

    /**
     * \brief Calculates the percentage of used memory.
     * \param mem The amount of memory used.
     * \param totalMemory The total memory available.
     * \return The percentage of used memory.
     * \details This function calculates the percentage of used memory based on the total memory available.
     */
    static float percentOfMemory(size_t mem, size_t totalMemory = 0);
};



#endif //MEMORY_VIEW_H
