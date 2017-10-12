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
int binarySearch(ArrFile, int, int, int);
int alg(ArrFile[], int, int, int);
bool algIsDone(ArrFile[], int);
void bubbleSort(int*, int);

int main() {
	int k, m, n;
	getParameters(&m, &n, &k); //gets values of m, n, and k from file
    
    ArrFile files[m]; //initialize all files
    for(int i = 1; i <=m; i++){
        files[i-1].file = i;
        files[i-1].begin = 0;
        files[i-1].end = n-1;
        files[i-1].length = n;
        }

    unsigned int result = alg(files, m, n, k);
    
    /*FILE *fd = fopen("output.txt", "w");
    printf("%d", result);
    fclose(fd);*/
    
    return 0;
}

int alg(ArrFile files[], int m, int n, int k){
    if(algIsDone(files, m)){
        int nonEmptyCount = 0;

        for(int i = 0; i < m; i++){
            if(files[i].length != 0)
                nonEmptyCount++;
            }
        //std::cout << nonEmptyCount << "\n";
        int F[nonEmptyCount]; //Create F

        for(int i = 0; i < nonEmptyCount; i++){
            if(files[i].length != 0)
                F[i] = getValue(files[i].file, files[i].begin+1);
                //std::cout << F[i] << "\n";
            }
        //sort the array by converting to vector, then calling std::sort
        /*std::vector<int> temp(nonEmptyCount);
        for(int i = 0; i < nonEmptyCount; i++)
            temp[i] = F[i];
        std::sort(temp.begin(), temp.end());*/
        //std::cout << "k is: " << k << "\n";


        bool swapped = true;
        int j = 0;
        int tmp;
        while (swapped){
            swapped = false;
            j++;
            for(int i = 0; i < nonEmptyCount - j; i++){
                if (F[i] > F[i+1]){
                    tmp = F[i];
                    F[i] = F[i+1];
                    F[i+1] = tmp;
                    swapped = true;
                    }
                }
            }
        int sol = F[k-1];
        //std::cout << F[k-1];

        FILE *fd = fopen("output.txt", "w");
        fprintf(fd, "%d", F[k-1]);
        fclose(fd);

        return sol;
        //return temp.at(k-1);
        }
    //END BASE CASE
    //
    //END BASE CASE

    ArrFile biggest = files[0];
    //find biggest file if not files[0]
    for (int i = 0;i < m; i++){
        if(files[i].length > biggest.length)
            biggest = files[i];
        }
    int iMid;
    //int iMid = (floor(biggest.length) / 2 ) + ((biggest.length) % 2 ) -1; //GOOD
    if((biggest.end - biggest.begin + 1) % 2 == 0)
        iMid = ((biggest.end + biggest.begin -1) / 2);
    else if ((biggest.end - biggest.begin+ 1) % 2 == 1)
        iMid=(biggest.end + biggest.begin) / 2;
    
    unsigned int midVal = getValue(biggest.file, iMid+1);//GOOD
    int indexArr[m];
    //fill indexArr
    for (int i = 0; i < m; i++){
        indexArr[i] = binarySearch(files[i], files[i].begin, files[i].end, midVal); //GOOD
        }
    
    std::cout << "indexArr: ";
    for(int i = 0; i < m; i++){
        std::cout << indexArr[i] << " ";
        }
    std::cout << "\n";
    
    int L = 0; //changed from 0 to 
    for (int i = 0; i < m; i++){
        if(indexArr[i] != -1)
            L += (indexArr[i]-files[i].begin+1); // get number of elements L <= midVal GOOD
        std::cout << L << std::endl;
        }
    
    printf("k : %d\niMid : %d\nL : %ud\nValue : %ud\n", k, iMid,L,getValue(biggest.file, iMid+1));
    std::cout << "getval at iMid+1: " << getValue(biggest.file, iMid+1) << "\n";
    for (int i = 0; i < m; i++){
        std::cout << "beginning for file " << i+1 << ": " <<files[i].begin << std::endl;
        std::cout << "end for file " << i+1 << ": " << files[i].end << std::endl;
        std::cout << "length of file " << i+1 << ": " << files[i].length << std::endl;
        }
        


    if (L >= k){
        printf("Going left\n");
        for(int i = 0; i < m; i++){
                files[i].end = indexArr[i];
                files[i].length = files[i].end - files[i].begin + 1;
            }
        alg(files, m, n, k);
        }
    else if (L < k){
        printf("Going right\n");
        for (int i = 0; i < m; i++){
            files[i].begin = indexArr[i]+1;
            files[i].length = files[i].end - files[i].begin + 1;
            }
         alg(files, m, n, k-L);
        }
    }

bool algIsDone(ArrFile files[], int m){
    for(int i = 0; i < m; i++){
        if(files[i].end - files[i].begin + 1 != 1 && files[i].end - files[i].begin + 1 != 0){
            printf("false\n");
            return false;
            }
        }
    printf("done\n");
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


int binarySearch(ArrFile fr, int iLow, int iHigh, int targetVal){
    
    int fileNum = fr.file;
    int arrSize = iHigh - iLow + 1;
	if (arrSize >= 1) {
        int iMid;
        if((iHigh - iLow + 1) % 2 == 0)
            iMid = ((iHigh + iLow -1) / 2);
        else if ((iHigh - iLow + 1) % 2 == 1)
            iMid=(iHigh + iLow) / 2;

        //std::cout << iMid << " " << iLow << " " << iHigh << " " << arrSize << "\n";

		if (getValue(fileNum, iMid+1) == targetVal)
		{
			return iMid;
		}

		if (getValue(fileNum, iMid+1) > targetVal)
		{
			return binarySearch(fr, iLow, iMid-1, targetVal);
		}	

		if ((getValue(fileNum, iMid+1) < targetVal && ((getValue(fileNum, iMid+2) > targetVal) || arrSize == 1)))//CHECK LATER
		{
			return iMid;
		}
		else 
			return binarySearch(fr, iMid+1, iHigh, targetVal);
		
	}
return -1;
}

void bubbleSort(int* arr, int n){
    bool swapped = true;
    int j = 0;
    int tmp;
    while (swapped){
        swapped = false;
        j++;
        for(int i = 0; i < n - j; i++){
            if (arr[i] > arr[i+1]){
                tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                swapped = true;
                }
            }
        }
    }
