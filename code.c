#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void getParameters(int* arrNum, int* arrLen, int* k) {
	FILE *fd = fopen("input.txt","r");
	fscanf(fd,"%d,%d,%d", arrNum,arrLen,k);
	fclose(fd);
}

unsigned int getValue(int arrNum, int arrInd) {
	FILE *fd;
	unsigned int value = 0, a, b, c, d;
	unsigned char num[4];
	char str[2];
	sprintf(str, "%d",arrNum);
	fd = fopen(strcat(str,".dat"),"rb");
	fseek(fd,(arrInd)*4-4,SEEK_SET);
	fread(num,4,1,fd);
	a = num[0];
	//printf("%u\n",a); 
	b = num[1];
	c = num[2];
	d = num[3];
	// printf("%u\n",b);
	// printf("%u\n",c);
	// printf("%u\n",d);
	value = (a*16777216)+(b*65536)+(c*256)+d;
	fclose(fd);
	return value;
}

int arrayLength(int arrNum, int** arrBondrs) {
	return arrBondrs[1][arrNum]-arrBondrs[0][arrNum];
}

unsigned int binarySearch(int num1, int l, int arrSize, int value)
{
	if (arrSize >= l)
	{
		unsigned int mid = l + (arrSize - l)/2;

		if (getValue(num1, mid) == value)
		{
			return mid;
		}

		if (getValue(num1, mid) > value)
		{
			return binarySearch(num1, l, mid-1, value);
		}	

		if (getValue(num1, mid) < value && getValue(num1, mid+1) > value)
		{
			return mid;
		}

		else 
			return binarySearch(num1, mid+1, arrSize, value);
		
	}
return -1;
}

int main() {
	int k, m, n;
	getParameters(&m, &n, &k);
	
int i;

for(i = 1; i <= m; i++)
{
	unsigned int v = binarySearch(i, 0, n, 5000);
	unsigned int b = getValue(i, v);
	printf("%d.dat= %d\n", i, v);
	printf("Value = %d\n", b);
}
//	int** arrayBoundaries = malloc(sizeof(int*)*m);
//	for (int i = 0; i < m; i++) {
//		arrayBoundaries[i] = malloc(sizeof(int)*n);
//	}
	//printf("%u\n", getValue(4,0));
//	int i =0;
//	while (1) {
//		i++;
//		k = getValue(5,i);
//	}
}
