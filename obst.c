#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc,char *argv[]){

    int minAvg,i;

    int n = atoi(argv[1]);
    float prob[n+1];
    for(i=1;i<=n;i++)
        prob[i] = atof(argv[i+1]);
    int R[200][200];

    optsearchtree(n,prob,&minAvg,R);

    printf("\n");

    return 0;
}


void optsearchtree(int n, const float p[], float *minavg, int R[200][200]){
    int i, j, k, diagonal, min;
    float A[n][n];
    for (i = 1; i <= n; i++) //initialization
    {
         A[i][i-1] = 0;
         R[i][i-1] = 0;
         A[i][i] = p[i];
         R[i][i] = i;
    }

    A[n+1][n] = 0;
    R[n+1][n] = 0;

    for (diagonal = 1; diagonal <= n-1; diagonal++){
        for (i = 1; i <= n - diagonal; i++){
            j = i + diagonal;
            int m;
            float min = 100000000;
            float sumFromItoJ = 0,kMin;
            for(m=i;m<=j;m++)
                sumFromItoJ += p[m];
            for(k = i;k<=j;k++){
                float sum = A[i][k-1]+A[k+1][j] + sumFromItoJ;
                if(min > sum){
                    min = sum;
                    kMin = k;
                }
            }
            A[i][j] = min;
            R[i][j] = kMin;
        }
	}
    *minavg = A[1][n];
    int state[100][3];  //1: root, 2: start, 3: end
    int itr,depth,start=1,end=n,root,elementsPrinted=0;
    for(itr=1;elementsPrinted<n;itr++){
        float op = log10(itr)/log10(2);
        depth = (int) op;
        if(op == depth)
            printf("depth %d:",depth);
        if(itr != 1){
            if(itr%2 == 0) { //itr is even, thus left child
                start =  state[itr/2][1];   //1: start
                end =  state[itr/2][0]-1;   //0: root
            }else{            //itr is odd, thus right child
                start =  state[itr/2][0]+1;   //0: root
                end = state[itr/2][2];      //2: end
            }
        }

        if(start > end || (state[itr/2][0] == 0 && itr !=1))
            root = 0;
        else{
            root = R[start][end];
            elementsPrinted++;
        }

        if(elementsPrinted == n)
            printf("%d",root);
        else
            printf("%d,",root);
        state[itr][0] = root;
        state[itr][1] = start;
        state[itr][2] = end;
    }
 }
