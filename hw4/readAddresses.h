//Global Variables
int* addresses;
int numAddresses;

//read line in addresses.txt
int readFileLine(FILE* file){
	char* buffer;
	int bufferSize = 128;
	int num = -1;
	if(file != NULL){
		buffer = (char *)malloc(sizeof(char) * bufferSize);
      	fgets(buffer, sizeof(buffer), file);

      	//trim buffer and remove \n from end
      	int newSize = strlen(buffer) - 1; //length of new string
		char* trimmedString = (char *)malloc(sizeof(char) * newSize);
		int i;
		for(i = 0; i < newSize; i++){
			trimmedString[i] = buffer[i];
		}
		if(trimmedString != NULL){
			num = atoi(trimmedString);
		}
    }
    return num;
}

//open addresses.txt file.
//call all other methods through this method
void readAddresses(char* fileName){
	int addr;
	int i, count = -1;

	int bufferSize = 1028;
	int* buffer = (int *)malloc(sizeof(int) * bufferSize);

	FILE* file = fopen(fileName, "r"); //open fileName

	//read file argv[1] line by line and turn into int
	// while(count < 20){
	while(1){
		count++;
		addr = readFileLine(file);
		if(addr < 0){
			// printf("reached end of file.\n");
			break;
		}else{
			// add addr to int** address
			if(count == bufferSize){
				bufferSize *= 2;
				buffer = realloc(buffer, bufferSize); //reallocate buffer memory size
			}
			buffer[count] = addr;
			// printf("count: %d\n",count);
		}
	}
	numAddresses = count; //update global variable
	addresses = (int *)malloc(sizeof(int) * numAddresses); //malloc to num of elements read
	//copy elements read into buffer into array with size = num elements read
	for(i = 0; i < numAddresses; i++){
		addresses[i] = buffer[i];
	}
	free(buffer);
   	fclose(file);
}
