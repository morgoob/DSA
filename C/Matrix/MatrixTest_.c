//-----------------------------------------------------------------------------
//  MatrixClient.c 
//  A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   int n=100000;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix Q = newMatrix(n);
   Matrix W = newMatrix(n);
   Matrix C, D, E, F, L, G;//, H;

   changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
   changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
   changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
   changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
   changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
   changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
   changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

   /* changeEntry(Q,1,53,3); */
   /* changeEntry(Q,3,35,22); */
   /* changeEntry(Q,2,1,134); */
   /* changeEntry(Q,8,3,22); */
   /* changeEntry(Q,81,2,45); */
  
   /* changeEntry(W,1,53,3); */
   /* changeEntry(W,3,35,22); */
   /* changeEntry(W,2,1,134); */
   /* changeEntry(W,8,3,22); */
   /* changeEntry(W,81,2,45); */

   /* printf("%d\n", NNZ(A)); */
   /* printf("Matrix A\n"); */
   /* printMatrix(stdout, A); */
   /* printf("\n"); */

   /* printf("%d\n", NNZ(B)); */
   /* printf("Matrix B\n"); */
   /* printMatrix(stdout, B); */
   /* printf("\n"); */


   /*  printf("%s\n", equals(A, A)?"true":"false \n" ); */
   /*  printf("%s\n", equals(Q, W)?"true":"false \n" ); */

   /*  changeEntry(Q,83,4,23); */

   /*  printf("%s\n", equals(Q, W)?"true":"false \n" ); */



   /* C = scalarMult(1.5, A); */
   /* printf("Matrix C (scalar mult)\n"); */
   /* printf("%d\n", NNZ(C)); */
   /* printMatrix(stdout, C); */
   /* printf("\n"); */


   /* printf("%d\n", NNZ(A)); */
   /* printf("Matrix A ( after scalar mult() ) \n"); */
   /* printMatrix(stdout, A); */
   /* printf("\n"); */

   /* D = sum(A, B); */
   /* printf("%d\n", NNZ(D)); */
   /* printf("Matrix D ( sum(A,B) )\n "); */
   /* printMatrix(stdout, D); */
   /* printf("\n"); */

   /* E = diff(A, A); */
   /* printf("%d\n", NNZ(E)); */
   /* printf("Matrix E ( diff(A,A) )\n"); */
   /* printMatrix(stdout, E); */
   /* printf("\n"); */

   /* printf("%d\n", NNZ(A)); */
   /* printf("Matrix A ( after diff/sum ) \n"); */
   /* printMatrix(stdout, A); */
   /* printf("\n"); */

   /*  F = transpose(B); */
   /* printf("%d\n", NNZ(F)); */
   /*  printf("Matrix F ( transpose(B) )  \n"); */
   /*  printMatrix(stdout, F); */
   /*  printf("\n"); */

   /* L = transpose(A); */
   /* printf("%d\n", NNZ(L)); */
   /*  printf("Matrix L ( transpose(A) )  \n"); */
   /*  printMatrix(stdout, L); */
   /*  printf("\n"); */

   G = product(B, B);
   printf("%d\n", NNZ(G));
   printf("Matrix G ( product(B,B) ) \n");
   printMatrix(stdout, G);
   printf("\n");

   // H = copy(A);
   // printf("%d\n", NNZ(H));
   // printMatrix(stdout, H);
   // printf("\n");

   // printf("%s\n", equals(A, H)?"true":"false" );
   // printf("%s\n", equals(A, B)?"true":"false" );
   // printf("%s\n", equals(A, A)?"true":"false" );

   // makeZero(A);
   // printf("%d\n", NNZ(A));
   // printMatrix(stdout, A);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&Q);
   freeMatrix(&W);
   freeMatrix(&F);
   freeMatrix(&L);
   freeMatrix(&G);
   // freeMatrix(&H);

   return EXIT_SUCCESS;
}

/*
Output of this program:
9
 Matrix A 
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6 
Matrix B 
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

true
true
false

9 
Matrix C (scalar mult)
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

9
Matrix A ( after scalar mult() )
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

9 
Matrix D ( sum(A,B) )
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

0
Matrix E ( diff(A,A) )

9
Matrix A ( after diff/sum )
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6 
Matrix F ( transpose(B) ) 
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

9
Matrix L ( transpose(A) ) 
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)


7
Matrix G ( product(B,B) )
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)



true
false
true
0
*/
