//Joseph Crandall
//Virtual Memory Manager
//The output for the FIFO, LRU, and TLB Hit Rates and Pages Faults are stored in output txt files.
// pg 458 OS-Book 9th edition

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "terminalColors.h"
#include "readAddresses.h"
#define FIFO_REPLACEMENT_POLICY "FIFO"
#define LRU_REPLACEMENT_POLICY "LRU"
#define PAGE_SIZE 256             //256 bytes per page
#define NUM_VIRTUAL_PAGES 256     //number of pages in virtual memory
#define NUM_PHYSICAL_FRAMES 128  //number of frames (pages) in physical memory
#define CACHE_SIZE 16             //number of TLBEntries in cache

//Global Variables
char* replacementPolicy = FIFO_REPLACEMENT_POLICY;
int currCacheSize;          //number of cache slots filled
int currNumPhysicalFrames;  //number of frames filled
int currFrameNumber;
char physical_memory[PAGE_SIZE * NUM_PHYSICAL_FRAMES]; //physical memory

struct TLBEntry{
	int virtualAddress; //for debugging. TODO: remove this and adjust functions
	int valid;          // 1 = virtualPage is mapped to physical memory
	int virtualPage;    // need for cache
	int physicalFrame;  // if valid = 1, this is set to physical frame that page is mapped to
	struct TLBEntry *next;
};

struct TLBEntry pageTable[NUM_VIRTUAL_PAGES];
struct TLBEntry *pmHead;
struct TLBEntry *cacheHead;

//for statistics
int TLBHit;
int pageTableFaultCounter;
int timeLapsed;


void initialize(){
	int i;
	currCacheSize = 0;
	currNumPhysicalFrames = 0;
	currFrameNumber = -1;

	//initialize TLB values in pageTable[]
	for(i = 0; i < NUM_VIRTUAL_PAGES; i++){
		pageTable[i].valid = 0;         // TLB entry not mapped to physical memory
		pageTable[i].virtualPage = -1;   // don't need this for page table. need for cache
		pageTable[i].virtualAddress = -1;
	}

	TLBHit = 0;
	pageTableFaultCounter = 0;
	timeLapsed = 0;
}


//masks 32 bit address to 16 bit address
unsigned int maskAddress(unsigned int x){
	return x & 0xffff;
}

//get page of address
unsigned int getPage(unsigned int addr){
	//assumes 16 bit address
	//page = greater 8 bits (leftmost)
	return addr >> 8;   // gets page
}

//get offset of address
unsigned int getOffset(unsigned int addr){
	//assumes 16 bit address
	//offset = lesser 8 bits (rightmost)
	return addr & 0xff;   // gets offset
}


// **************************************************************
// **************************Methods*****************************
// **************************************************************
void makeInvalid(int frameNumber){
	int i;
	// printCyan("makeInvalid\n");
	//make mappings to frameNumber in pageTable invalid
	for(i = 0; i < NUM_VIRTUAL_PAGES; i++){
		if(pageTable[i].physicalFrame == frameNumber && pageTable[i].valid == 1){
			pageTable[i].valid = 0;
		}
	}
	// printf("invalidation of pageTable complete\n");


	//make mappings to frameNumber in TLB Cache invalid
	struct TLBEntry *temp;
	temp = cacheHead;
	for(i = 0; i < currCacheSize; i++){
		if(temp == NULL){
			break;
		}
		if(temp->physicalFrame == frameNumber && temp->valid == 1){
			//make invalid
			temp->valid = 0;
		}
		temp = temp->next;
	}

	// printRed("invalidation of cache complete\n");
}


//get next available frame number.
//Sets to unavailable if returning available frame number
int getAvailableFrameNumber(){
	// printCyan("getAvailableFrameNumber()\n");
	int error = -1;
	int i;
		//list is empty
		if(pmHead == NULL){
			//physical memory empty
			currFrameNumber++; //now 0
			// printGreen("pmHead == NULL\n");
			// printf("%d\n",currFrameNumber);
			struct TLBEntry *newNode = (struct TLBEntry *)malloc(sizeof(struct TLBEntry));
			newNode->physicalFrame = currFrameNumber;
			pmHead = newNode;
			currNumPhysicalFrames++; //counter for num frames. will not excede NUM_PHYSICAL_FRAMES
			makeInvalid(currFrameNumber);
			return currFrameNumber;
		}
		else if(currNumPhysicalFrames < NUM_PHYSICAL_FRAMES){
			currFrameNumber++;
			struct TLBEntry *newNode = (struct TLBEntry *)malloc(sizeof(struct TLBEntry));
			newNode->physicalFrame = currFrameNumber;
			// printGreen("currNumPhysicalFrames < NUM_PHYSICAL_FRAMES\n");
			// printf("%d\n",currFrameNumber);
			struct TLBEntry *temp;
			temp = pmHead;
			pmHead = newNode;
			pmHead->next = temp;
			currNumPhysicalFrames++; //counter for num frames. will not excede NUM_PHYSICAL_FRAMES
			makeInvalid(currFrameNumber);
			return currFrameNumber;
		}
		else{
			//need to remove tail b/c size NUM_PHYSICAL_FRAMES exceeded
			struct TLBEntry *tail;
			struct TLBEntry *prev;
			tail = pmHead;
			while(tail->next != NULL){
				prev = tail;
				tail = tail->next;
			}
			//tail is tail of linked list
			currFrameNumber = tail->physicalFrame;
			prev->next = NULL; //remove tail
			// printGreen("else\n");
			// printf("%d\n",currFrameNumber);
			struct TLBEntry *newNode = (struct TLBEntry *)malloc(sizeof(struct TLBEntry));
			newNode->physicalFrame = currFrameNumber;
			struct TLBEntry *temp;
			temp = pmHead;
			pmHead = newNode;
			pmHead->next = temp;
			makeInvalid(currFrameNumber);
			return currFrameNumber;
		}
	printRed("no available frame\n");
	return error; //error.
}
//checks if page is already mapped by checking TLBCache then page table
//returns 1 mapped but not in TLBCache
//returns 2 if mapped and in TLBCache
int checkMapped(unsigned int addr){
	// printCyan("checkMapped()\n");
	unsigned int addrPage = getPage(addr);
	int i;
	struct TLBEntry *temp;
	temp = cacheHead;
	// printRed("before loop in checkMapped()\n");
	for(i = 0; i < currCacheSize; i++){
		if(temp == NULL){
			break;
		}
		if(temp->virtualPage == addrPage && temp->valid == 1){
			//page is mapped to physical memory
			//page is also valid in TLB Cache
			// printGreen("return 2\n");
			return 2;
		}
		temp = temp->next;
	}
	// printRed("not in cache\n");
	//check pageTable
	if(pageTable[addrPage].valid == 1){
		// printRed("in if\n");
		//printGreen("pageTable hit!\n");
		//page already mapped to physical memory
		// printGreen("return 1\n");
		return 1;
	}else{
		// printGreen("return 0\n");
		return 0;
	}
}

//goes to pageTable to get mapped frame
int getMappedFrame(unsigned int addr){
	// printCyan("getMappedFrame()\n");
	int error = -1;
	unsigned int addrPage = getPage(addr);
	int i, frame;

	if(checkMapped(addr) == 0){
		printRed("addr not mapped. cannot get frame\n");
		return error;
	}
	else if(checkMapped(addr) == 2){
		// printGreen("TLB Cache hit! addrPage = ");
		// printf("%d\n",addrPage);

		//addr in TLB Cache, getting frame from TLB Cache
		struct TLBEntry *temp;
		temp = cacheHead;
		for(i = 0; i < currCacheSize; i++){
			if(temp == NULL){
				break;
			}
			if(temp->virtualPage == addrPage){
				frame = temp->physicalFrame;
			}
			temp = temp->next;
		}
	}
	else if(checkMapped(addr) == 1){
		// printGreen("TLB Cache miss! Mapped in pageTable. addrPage = ");
		// printf("%d\n",addrPage);

		//addr not in TLB Cache, getting frame from pageTable
		frame = pageTable[addrPage].physicalFrame;
		return frame;
	}
	return frame;
}




void insertPageTable(int addr, int frameNumber){
	int addrPage = getPage(addr);
	pageTable[addrPage].virtualAddress = addr;
	pageTable[addrPage].physicalFrame = frameNumber;
	pageTable[addrPage].valid = 1;
}


void insertTLBCache(int addr, int frameNumber){
	// printCyan("insertTLBCache()\n");
	int addrPage = getPage(addr);
	// printf("insertTLBCache(%d, %d)\n",addrPage, frameNumber);
	int i;


	if(replacementPolicy == FIFO_REPLACEMENT_POLICY){  //First in First out page replacement

		//list is empty
		if(cacheHead == NULL){
			//cache empty
			struct TLBEntry *newNode = (struct TLBEntry *)malloc(sizeof(struct TLBEntry));
			newNode->physicalFrame = frameNumber;
			newNode->virtualPage = addrPage;
			newNode->valid = 1;
			cacheHead = newNode;
			currCacheSize++; //counter for cache size. will not excede CACHE_SIZE
		}
		else if(currCacheSize < CACHE_SIZE){
			struct TLBEntry *newNode = (struct TLBEntry *)malloc(sizeof(struct TLBEntry));
			newNode->physicalFrame = frameNumber;
			newNode->virtualPage = addrPage;
			newNode->valid = 1;

			struct TLBEntry *temp;
			temp = cacheHead;
			cacheHead = newNode;
			cacheHead->next = temp;
			currCacheSize++; //counter for cache size. will not excede CACHE_SIZE
		}
		else{
			//need to remove tail b/c size CACHE_SIZE exceeded
			struct TLBEntry *tail;
			struct TLBEntry *prev;
			tail = cacheHead;
			while(tail->next != NULL){
				prev = tail;
				tail = tail->next;
			}
			//tail is tail of linked list
			prev->next = NULL; //remove tail

			struct TLBEntry *newNode = (struct TLBEntry *)malloc(sizeof(struct TLBEntry));
			newNode->physicalFrame = frameNumber;
			newNode->virtualPage = addrPage;
			newNode->valid = 1;

			struct TLBEntry *temp;
			temp = cacheHead;
			cacheHead = newNode;
			cacheHead->next = temp;
		}
	}
	else if(replacementPolicy == LRU_REPLACEMENT_POLICY){  //last recenently used page replacement


		struct TLBEntry *temp;
		struct TLBEntry *prev;
		temp = cacheHead;

		//check if frameNumber is already in the cache
		for(i = 0; i < currCacheSize; i++){
			if(temp == NULL){
				break;
			}
			if(temp->physicalFrame == frameNumber){
				//frame number is in cache
				//move temp to head
				struct TLBEntry *prev;
				temp = cacheHead;
				//move temp to head
				prev->next = temp->next;
				struct TLBEntry *temp2;
				temp2 = cacheHead;
				cacheHead = temp;
				cacheHead->next = temp2;
				break;
			}
			prev = temp;
			temp = temp->next;
		}




		if(temp == NULL){  //might have to change this
			// frameNumber not in cache
			//list is empty
			if(cacheHead == NULL){
				//cache empty
				struct TLBEntry *newNode = (struct TLBEntry *)malloc(sizeof(struct TLBEntry));
				newNode->physicalFrame = frameNumber;
				newNode->virtualPage = addrPage;
				newNode->valid = 1;
				cacheHead = newNode;
				currCacheSize++; //counter for cache size. will not excede CACHE_SIZE
			}
			else if(currCacheSize < CACHE_SIZE){
				struct TLBEntry *newNode = (struct TLBEntry *)malloc(sizeof(struct TLBEntry));
				newNode->physicalFrame = frameNumber;
				newNode->virtualPage = addrPage;
				newNode->valid = 1;

				struct TLBEntry *temp;
				temp = cacheHead;
				cacheHead = newNode;
				cacheHead->next = temp;
				currCacheSize++; //counter for cache size. will not excede CACHE_SIZE
			}
			else{
				//need to remove tail b/c size CACHE_SIZE exceeded
				struct TLBEntry *tail;
				struct TLBEntry *prev;
				tail = cacheHead;
				while(tail->next != NULL){
					prev = tail;
					tail = tail->next;
				}
				//tail is tail of linked list
				prev->next = NULL; //remove tail

				struct TLBEntry *newNode = (struct TLBEntry *)malloc(sizeof(struct TLBEntry));
				newNode->physicalFrame = frameNumber;
				newNode->virtualPage = addrPage;
				newNode->valid = 1;

				struct TLBEntry *temp;
				temp = cacheHead;
				cacheHead = newNode;
				cacheHead->next = temp;
			}
		}
	}
}



//adds to cache afterwards
int getPhysicalAddress(unsigned int addr){

	// printf("getPhysicalAddress()\n");
	int error = -1;
	int frameNumber = getMappedFrame(addr);
	if(frameNumber == -1){
		printRed("error\n");
		return error;
	}
	int physicalAddress = frameNumber;
	physicalAddress = physicalAddress << 8;
	int offset = getOffset(addr);
	physicalAddress = physicalAddress + offset;

	//add addr to cache
	insertTLBCache(addr, frameNumber);

	return physicalAddress;
}


char getValue(unsigned int physicalAddr){
	int error = -1;
	int frameNumber = getPage(physicalAddr);
	if(frameNumber == -1){
		return error;
	}
	int offset = getOffset(physicalAddr);

	int value = physical_memory[(frameNumber * PAGE_SIZE) + offset];


	if(replacementPolicy == LRU_REPLACEMENT_POLICY){
		//modify main memory
		struct TLBEntry *temp;
		struct TLBEntry *prev;
		temp = pmHead;

		//temp is head
		if(temp->physicalFrame != frameNumber){
			prev = temp;
			temp = temp->next;

			while(temp != NULL){
				if(temp->physicalFrame == frameNumber){

					prev->next = temp->next;

					struct TLBEntry *temp2; //current head
					temp2 = pmHead;

					temp->next = temp2;
					pmHead = temp;
					break;
				}
				prev = temp;
				temp = temp->next;
			}
		}
	}
	return value;
}


//seeks to page in BACKING_STORE.bin file and reads in 1 page of bytes
void mapAddrToPhysicalMemory(unsigned int addr){
	if(checkMapped(addr) == 2){  // == 2 == mapped in physical memory and in cache
		//addrPage already mapped to physical memory
		// printGreen("addrPage already mapped to physical memory\n");
		TLBHit++;
		return;
	}

	if(checkMapped(addr) == 1){  // == 1 == mapped in physical memory and NOT ain cache
		//addrPage already mapped to physical memory
		// printGreen("addrPage already mapped to physical memory\n");
		return;
	}
	pageTableFaultCounter++;
	unsigned int addrPage = getPage(addr);

	int frameNumber = getAvailableFrameNumber();
	if(frameNumber == -1){
		//Error in getting next available frame number
		return;
	}
	char const* const fileName = "BACKING_STORE.bin";  //move this to global
	FILE* file = fopen(fileName, "r"); //open fileName

	//move file pointer to addrPage
    if(0 != fseek(file, addrPage * PAGE_SIZE, SEEK_SET)){  //SEEK_SET = start at beginning of file
        printf("\n fseek() failed\n");
    }
	//read bytes from file into physical_memory
	fread(&physical_memory[frameNumber * PAGE_SIZE], PAGE_SIZE, 1, file);

	//map addrPage to frameNumber

	insertPageTable(addr, frameNumber);


    fclose(file); //close fileName
}




// **************************************************************
// ***********************Print Methods**************************
// **************************************************************
void printAddresses(){
	int i;
	printCyan("printAddresses()\n");
	for(i = 0; i < numAddresses; i++){
		printf("address[%d] = %d\n",i, addresses[i]);
	}
}

void printPhysicalMemory(){
	int i;
	int numberFrames = NUM_PHYSICAL_FRAMES;

	for(i = 0; i < numberFrames * PAGE_SIZE; i = i+2){
		if(i%PAGE_SIZE == 0){
			printf("\nframe %d:", i/PAGE_SIZE);
		}
		if(i%16 == 0){
			printf("\n");
		}
		printf("%02x%02x ",physical_memory[i], physical_memory[i+1]);
	}
	printf("\n");
}

void printTLBCache(){
	printCyan("printTLBCache()\n");
	int i = 0;
	printGreen("currCacheSize: ");
	printf("%d\n",currCacheSize);

	struct TLBEntry *temp;
	temp = cacheHead;
	while(temp != NULL){
		printf("TLBCache[%d]:\n",i);
		printf("  virtualAddress = %d\n",temp->virtualAddress);
		printf("  virtualPage = %d\n",temp->virtualPage);
		printf("  physicalFrame = %d\n",temp->physicalFrame);
		printf("  valid = %d\n",temp->valid);
		i++;
		temp = temp->next;
	}
}

void printPageTable(){
	printCyan("printPageTable()\n");
	int i;
	for(i = 0; i < NUM_VIRTUAL_PAGES; i++){
		if(pageTable[i].valid == 0){
			printf("pageTable[%d] = empty\n",i);
		}else{
			printf("pageTable[%d] = %d\n",i,pageTable[i].physicalFrame);
		}
	}
}

// **************************************************************
// *************************Main Method**************************
// **************************************************************


int main(int argc, char* argv[]){
	char* fileName = argv[1]; //addresses.txt
	int i;
	int physicalAddress, value;
	FILE *f;

	double TLBHitRate;
	double pageFaultRate;

	initialize();

	//create array of addresses
	readAddresses(fileName);
	// printAddresses();

	//match expected output for project
	replacementPolicy = FIFO_REPLACEMENT_POLICY;

	f = fopen("outputFIFO.txt", "w");  //Write output to file outputFIFO.txt
	if (f == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}
	for(i = 0; i < numAddresses; i++){
		mapAddrToPhysicalMemory(addresses[i]);
		physicalAddress = getPhysicalAddress(addresses[i]);
		value = getValue(physicalAddress);

		fprintf(f, "Virtual Address: %d Physical Address: %d Value: %d\n", addresses[i], physicalAddress, value);
	}
	fclose(f);


	f = fopen("statisticsFIFO.txt", "w");
	if (f == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(f, "TLB Hits = %d\n", TLBHit);
	TLBHitRate = (double)TLBHit / (double)numAddresses;
	fprintf(f, "TLB Hit Rate = TLBHits / numAddresses = %f\n", TLBHitRate);

	fprintf(f, "Page Faults = %d\n", pageTableFaultCounter);
	pageFaultRate = (double)pageTableFaultCounter / (double)numAddresses;
	fprintf(f, "Page Fault Rate = pageTableFaultCounter / numAddresses = %f\n", pageFaultRate);

	fclose(f);


	//match expected output for project
	replacementPolicy = LRU_REPLACEMENT_POLICY;
	initialize();

	f = fopen("outputLRU.txt", "w");  //Write output to file outputFIFO.txt
	if (f == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}
	for(i = 0; i < numAddresses; i++){
		mapAddrToPhysicalMemory(addresses[i]);

		// printf("i after mapAddr: %d\n",i);

		// printf("addresses[%d] = %d\n",i,addresses[i]);
		physicalAddress = getPhysicalAddress(addresses[i]);

		// printf("i before getValue: %d\n",i);
		value = getValue(physicalAddress);

		// printf("i after getValue: %d\n",i);

		fprintf(f, "Virtual Address: %d Physical Address: %d Value: %d\n", addresses[i], physicalAddress, value);
	}
	fclose(f);

	f = fopen("statisticsLRU.txt", "w");
	if (f == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}
	fprintf(f, "TLB Hits = %d\n",TLBHit);
	TLBHitRate = (double)TLBHit / (double)numAddresses;
	fprintf(f, "TLB Hit Rate = TLBHits / numAddresses = %f\n", TLBHitRate);

	fprintf(f, "Page Faults = %d\n", pageTableFaultCounter);
	pageFaultRate = (double)pageTableFaultCounter / (double)numAddresses;
	fprintf(f, "Page Fault Rate = pageTableFaultCounter / numAddresses = %f\n", pageFaultRate);


	fclose(f);


	// printTLBCache();
   	// printPageTable();
	// printPhysicalMemory();
}

















