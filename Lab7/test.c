//comand line arguments
#include <stdio.h>
#include <stdlib.h>

void foo(void *);


typedef struct{
	double x;
	double y;
}Point;

typedef struct
{
	int i;
	float *fltArr;
	Point *point;
	double dbl;
}functionData;

int main(int argumentCount, char *argumentArray[]){
	int i;
	printf("number of arguments = %d\n", argumentCount);

	for (i = 1; i < argumentCount; i++)
		printf("argArray[%d]= %d\n", i, atoi(argumentArray[i]));

	//declares an integer start pointer
	int *ptr;

	int x = 5;

//pointer to a point
	Point *point = malloc(sizeof(point));

//equivalnet
	(*point).x = 22.1;

	point -> x = 22.1;

	point -> y = -4;



	ptr = &x;

	//void pointer can point to anything
	void *voidPointer;
	voidPointer = &x;

	//ptr and voidPointer are pointing at the same thing

	printf("*prt = %d, *voidPointer = %d", *ptr, *((int*)voidPointer));
	//brings your void pointer back to an int pointer, then derefence the int potiner

	double dbl = 3.14;
	voidPointer = &dbl;

	printf("*voidPointer (double) => %f\n",*((double*)voidPointer));

	float fltArr[4] = {1.1,2.25,3,4.0};
	voidPointer = fltArr;

	printf("*voidPointer[3] = %f\n" , ((float*)voidPointer)[3]);

	voidPointer = point;
	printf("*voidPointer.x = %f\n", ((Point *)voidPointer)->x);

	void *voidArr[4];


	voidArr[0] = &x;
	voidArr[1] = &fltArr;
	voidArr[2] = &point;
	voidArr[3] = &dbl;

	printf("*voidArr[3] = %f\n", *((double *)voidArr[3]));
	//foo(voidArr);
	//-------------------------------------------------
	functionData data;

	data.i = x;
	data.fltArr = fltArr;
	data.point = point;
	data.dbl = dbl;

	foo(&data);
}


//if you add star, you can pass it thorugh a thread

// pass around whatever you want with a void pointer, then cast it back when you need it
void foo(void *data){

	// void **voidArr = (void **)data;
	// printf("*voidArr[3] = %f\n", *((double *)voidArr[3]));

	functionData myData;
	myData = *((functionData *)data);

	printf("myData.dbl = %f\n", myData.dbl);
}






