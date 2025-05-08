#include <stdio.h>
#include <stdlib.h>

#define PHYSICAL_MEMORY_SIZE 1024        // Total size of physical memory in bytes
#define VIRTUAL_MEMORY_SIZE 2048         // Total size of virtual memory in bytes
#define PAGE_SIZE 256                    // Size of each page in bytes
#define NUM_PHYSICAL_PAGES (PHYSICAL_MEMORY_SIZE / PAGE_SIZE) // Number of pages in physical memory

// Structure to represent a page table entry
typedef struct {
    int pageNumber;  // The virtual page number currently mapped to this physical page
} PageTableEntry;

// Function to simulate memory access using FIFO page replacement
void accessMemoryFIFO(int *physicalMemory, PageTableEntry *pageTable, int *pageQueue, int *queueIndex, int virtualAddress) {
    int pageNumber = virtualAddress / PAGE_SIZE;  // Calculate the page number from the virtual address
    int offset = virtualAddress % PAGE_SIZE;      // Calculate the offset within the page
    int physicalPageNumber = -1;  // Initialize physical page number to -1 (indicating page not found)

    // TODO: Check if the page is already in physical memory by iterating through the page table.
    // If the page is found, update physicalPageNumber with the corresponding physical page index.
    for (int i = 0; i < NUM_PHYSICAL_PAGES; i++) { // checks page in physical memory by iterating
        if (pageTable[i].pageNumber == pageNumber) { // index found
            physicalPageNumber = i;             /// updating physicalpageNumber with physical page index.
            break;                               // break once the page is found
        }
    }

    
        
    
    // TODO: If the page is not in physical memory (page fault), implement the FIFO page replacement logic here.
    // - Replace the oldest page using FIFO.
    // - Update the page table to reflect the new mapping.
    // - Update the page queue to reflect the replacement and move the queue index forward.
    if (physicalPageNumber == -1 ) { 
        int replaceIndex = pageQueue[*queueIndex];  //gettng Index of page being Replace
        pageTable[replaceIndex].pageNumber = pageNumber;// page being Updated in page table
        *queueIndex = (*queueIndex + 1) %  NUM_PHYSICAL_PAGES; //page queue being Updated.
    }
        



        

    

     




    // TODO: Calculate the physical address using the physical page number and the offset. 
    int PhysicalAddress = (physicalPageNumber * PAGE_SIZE) + offset;  //

    // Print the translation from virtual address to physical address.
    printf("Virtual Address: %d -> Physical Address: %d\n", virtualAddress, PhysicalAddress);
}

int main() {
    // Allocate memory for the physical memory, page table, and page queue.
    int *physicalMemory = (int *)malloc(PHYSICAL_MEMORY_SIZE * sizeof(int));  // Allocate physical memory
    PageTableEntry *pageTable = (PageTableEntry *)malloc(NUM_PHYSICAL_PAGES * sizeof(PageTableEntry));  // Allocate page table
    int *pageQueue = (int *)malloc(NUM_PHYSICAL_PAGES * sizeof(int));  // Allocate page queue
    int queueIndex = 0;  // Initialize the queue index to 0

    // TODO: Initialize the page table. Set all entries in the page table to -1 to indicate that no pages are loaded initially.
    // Initialize the page queue with sequential physical page numbers.
    for (int i = 0; i < NUM_PHYSICAL_PAGES; i++) { // Initialize page table 
        pageTable[i].pageNumber = -1;    // settng entries in the page table to -1
    }

    for (int i = 0;  i < NUM_PHYSICAL_PAGES; +i++) {  //Initializing page queue with sequential physical page numbers.
        pageQueue[i] = i;
    }   

    
    


    int virtualAddresses[] = {100, 500, 1300, 1900, 2500};  
    int numAddresses = sizeof(virtualAddresses) / sizeof(virtualAddresses[0]);  // Calculate the number of virtual addresses

    // Simulate memory access using FIFO page replacement for each virtual address in the array.
    for (int i = 0; i < numAddresses; i++) {
        accessMemoryFIFO(physicalMemory, pageTable, pageQueue, &queueIndex, virtualAddresses[i]);  // Access each virtual address
    }

    // Free allocated memory.
    free(physicalMemory);  // Free the physical memory
    free(pageTable);  // Free the page table
    free(pageQueue);  // Free the page queue

    return 0;  // Return 0 to indicate successful execution
}

/*

+--------------------------+ High Virtual Address
|                          |
|   Virtual Memory Space   |   // Represents the virtual memory available to the program
|                          |
|  +---------------------+ |
|  | Virtual Address: 2500 | -> Page Number: 9, Offset: 196
|  +---------------------+ |
|  +---------------------+ |
|  | Virtual Address: 1900 | -> Page Number: 7, Offset: 108
|  +---------------------+ |
|  +---------------------+ |
|  | Virtual Address: 1300 | -> Page Number: 5, Offset: 12
|  +---------------------+ |
|  +---------------------+ |
|  | Virtual Address:  500 | -> Page Number: 1, Offset: 244
|  +---------------------+ |
|  +---------------------+ |
|  | Virtual Address:  100 | -> Page Number: 0, Offset: 100
|  +---------------------+ |
|                          |
+--------------------------+ Low Virtual Address

        Page Table
+-----------------------------+
|  Page Number | Physical Page |
|      0       |       0       | -> Virtual page 0 is stored in physical frame 0
|      1       |       1       | -> Virtual page 1 is stored in physical frame 1
|      5       |       2       | -> Virtual page 5 is stored in physical frame 2
|      7       |       3       | -> Virtual page 7 is stored in physical frame 3
+-----------------------------+

Physical Memory (RAM)
+-----------------------------+
| Physical Frame | Data Block  |
+-----------------------------+
|       0        | Data for Page 0 (e.g., addresses 0-255)  |
|       1        | Data for Page 1 (e.g., addresses 256-511)|
|       2        | Data for Page 5 (e.g., addresses 1280-1535)|
|       3        | Data for Page 7 (e.g., addresses 1792-2047)|
+-----------------------------+

How Page Numbers and Offsets are Calculated:
Page Size is 256 bytes. This means each page in virtual memory (and corresponding page frame in physical memory) holds 256 bytes.
Virtual Addresses Provided:
Virtual Addresses: {100, 500, 1300, 1900, 2500}

Calculating Page Numbers:
To calculate the page number and offset for each virtual address:

Page Number = Virtual Address / PAGE_SIZE
Offset = Virtual Address % PAGE_SIZE
For Each Address:

Virtual Address: 100
Page Number: 100 / 256 = 0
Offset: 100 % 256 = 100
This means virtual address 100 is in Page 0 at an offset of 100 bytes.


Virtual Address: 500
Page Number: 500 / 256 = 1
Offset: 500 % 256 = 244
This means virtual address 500 is in Page 1 at an offset of 244 bytes.


Virtual Address: 1300
Page Number: 1300 / 256 = 5
Offset: 1300 % 256 = 12
This means virtual address 1300 is in Page 5 at an offset of 12 bytes.


Virtual Address: 1900
Page Number: 1900 / 256 = 7
Offset: 1900 % 256 = 108
This means virtual address 1900 is in Page 7 at an offset of 108 bytes.


Virtual Address: 2500
Page Number: 2500 / 256 = 9
Offset: 2500 % 256 = 196
This means virtual address 2500 is in Page 9 at an offset of 196 bytes.


Page Numbers:
Page Number 0: Contains virtual addresses from 0 to 255.
Page Number 1: Contains virtual addresses from 256 to 511.
Page Number 5: Contains virtual addresses from 1280 to 1535.
Page Number 7: Contains virtual addresses from 1792 to 2047.
Page Number 9: Contains virtual addresses from 2304 to 2559.

The page numbers are determined by dividing the virtual address by the page size (256 bytes).
The page number tells you which block of virtual memory the address falls into.
The offset within that page tells you how far into the page the specific address is.

*/
