#include <stdio.h>
#include<stdbool.h>
#define max 25

void firstFit(int nb, int nf, int b[], int f[]) {
    int frag[max], bf[max], ff[max];
    int i, j, temp;

    for (i = 1; i <= nf; i++) {
        for (j = 1; j <= nb; j++) {
            if (bf[j] != 1) {
                temp = b[j] - f[i];
                if (temp >= 0) {
                    ff[i] = j;
                    break;
                }
            }
        }
        frag[i] = temp;
        bf[ff[i]] = 1;
    }

    printf("\nFile_no:\tFile_size :\tBlock_no:\tBlock_size:\tFragment");
    for (i = 1; i <= nf; i++)
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
}

void bestFit(int nb, int nf, int b[], int f[]) {
    int frag[max], bf[max], ff[max];
    int i, j, temp, lowest = 10000;

    for (i = 1; i <= nf; i++) {
        for (j = 1; j <= nb; j++) {
            if (bf[j] != 1) {
                temp = b[j] - f[i];
                if (temp >= 0 && lowest > temp) {
                    ff[i] = j;
                    lowest = temp;
                }
            }
        }
        frag[i] = lowest;
        bf[ff[i]] = 1;
        lowest = 10000;
    }

    printf("\nFile No\tFile Size \tBlock No\tBlock Size\tFragment");
    for (i = 1; i <= nf && ff[i] != 0; i++)
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
}

void worstFit(int nb, int nf, int b[], int f[]) {
    int frag[max], bf[max], ff[max];
    int i, j, temp, highest = 0;

    for (i = 1; i <= nf; i++) {
        for (j = 1; j <= nb; j++) {
            if (bf[j] != 1) {
                temp = b[j] - f[i];
                if (temp >= 0 && highest < temp) {
                    ff[i] = j;
                    highest = temp;
                }
            }
        }
        frag[i] = highest;
        bf[ff[i]] = 1;
        highest = 0;
    }

    printf("\nFile_no:\tFile_size :\tBlock_no:\tBlock_size:\tFragment");
    for (i = 1; i <= nf; i++)
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
}

void main() {
    int b[max], f[max], nb, nf, choice;


    printf("\n\tMemory Management Scheme");
    printf("\nEnter the number of blocks:");
    scanf("%d", &nb);
    printf("Enter the number of files:");
    scanf("%d", &nf);
    printf("\nEnter the size of the blocks:-\n");
    for (int i = 1; i <= nb; i++) {
        printf("Block %d:", i);
        scanf("%d", &b[i]);
    }
    printf("Enter the size of the files :-\n");
    for (int i = 1; i <= nf; i++) {
        printf("File %d:", i);
        scanf("%d", &f[i]);
    }



    do{

        printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4.Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
            switch (choice) {
        case 1:
            printf("\n\tMemory Management Scheme - First Fit\n");
            firstFit(nb, nf, b, f);
            break;
        case 2:
            printf("\n\tMemory Management Scheme - Best Fit\n");
            bestFit(nb, nf, b, f);
            break;
        case 3:
            printf("\n\tMemory Management Scheme - Worst Fit\n");
            worstFit(nb, nf, b, f);
            break;
        default:
            printf("\nInvalid choice.\n");
            break;
    }



    }while(choice!=4);


}
