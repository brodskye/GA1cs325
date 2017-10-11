//Authors:
//David Jansen
//Pierre-Louis Sixdenier
//Eytan Brodsky

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <iostream>

typedef struct {
    int file;
    int begin;
    int end;
    int length;
    } ArrFile;


void getParameters(int*, int*, int*);
unsigned int getValue(int, int);
unsigned int binarySearch(int, int, int, unsigned int);
int alg(ArrFile[], int, int, int);
bool algIsDone(ArrFile[], int);

int main() {
	int k, m, n;
	getParameters(&m, &n, &k); //gets values of m, n, and k from file
    
    ArrFile files[m]; //initialize all files
    for(int i = 1; i <=m; i++){
        files[i-1].file = i;
        files[i-1].begin = 0;
        files[i-1].end = n;
        files[i-1].length = n;
        }


    
    
    int result = alg(files, m, n, k);
    std::cout << result << std::endl;
    /*int i;

    for(i = 1; i <= m; i++){
	    unsigned int v = binarySearch (i, 0, 4, 5000);
	    unsigned int b =	getValue(i, v);
	    printf("%d.dat= %d\n", i, v);
	    printf("Value = %d\n", b);
    }*/
    return 0;
}

int alg(ArrFile files[], int m, int n, int k){
    
    if(algIsDone(files, m)){
        int nonEmptyCount = 0;

        for(int i = 0; i < m; i++){
            if(files[i].length != 0)
                nonEmptyCount++;
            }

        int F[nonEmptyCount]; //Create F

        for(int i = 0; i < nonEmptyCount; i++){
            if(files[i].length != 0)
                F[i] = getValue(files[i].file, 1);
            }
        //sort the array by converting to vector, then calling std::sort
        std::vector<int> temp (F, F + nonEmptyCount);
        std::sort(temp.begin(), temp.end());
        return temp.at(k-1);
        }

    ArrFile biggest = files[0];
    //find biggest file if not files[0]
    for (int i = 0;i < m; i++){
        if(files[i].length > biggest.length)
            biggest = files[i];
        }
    
    int iMid = (floor(biggest.length) / 2 ) + (biggest.length) % 2 -1;
    int midVal = getValue(biggest.file, iMid+1);
    int indexArr[m];
    //fill indexArr
    for (int i = 0; i < m; i++){
        indexArr[i] = binarySearch(files[i].file, iMid, files[i].length, midVal);
        }
    int L = 0; //changed from 0 to 1
    for (int i = 0; i < m; i++){
        L += (indexArr[i]+1); // get number of elements L <= midVal
        std::cout << L << std::endl;
        }
    
    printf("k : %d\niMid : %d\nL : %d\nValue : %d\n", k, iMid,L,getValue(biggest.file, iMid+1));
    if (L >= k){
        printf("Going left\n");
        for(int i = 0; i < m; i++){
            files[i].end = indexArr[i];
            files[i].length = indexArr[i] + 1;
            }
        alg(files, m, n, k);
        }
    else if (L < k){
        printf("Going right\n");
        for (int i = 0; i < m; i++){
            files[i].begin = indexArr[i] + 1;
            files[i].length = files[i].length - L +1;
            }
         alg(files, m, n, k-L);
        }
    }

bool algIsDone(ArrFile files[], int m){
    for(int i = 0; i < m; i++){
        if(files[i].length != 1 || files[i].length != 0){
            printf("false\n");
            return false;
            }
        }
    printf("done");
    return true;
    }

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
	b = num[1];
	c = num[2];
	d = num[3];
	value = (a*16777216)+(b*65536)+(c*256)+d;
	fclose(fd);
	return value;
}

unsigned int binarySearch(int num1, int l, int arrSize, unsigned int value)
{
	if (arrSize >= l)
	{
		unsigned int mid = (arrSize)/2+ (arrSize) % 2 - 1;

		if (getValue(num1, mid+1) == value)
		{
			return mid;
		}

		if (getValue(num1, mid+1) > value)
		{
			return binarySearch(num1, l, mid-1, value);
		}	

		if (getValue(num1, mid+1) < value && (getValue(num1, mid+2) > value || arrSize == l))
		{
			return mid;
		}

		else 
			return binarySearch(num1, mid+1, arrSize, value);
		
	}
return -1;
}

