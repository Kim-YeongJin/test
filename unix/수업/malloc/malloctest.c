#include <stdio.h>

int main() {

     int x = 4;
     void *q = &x;
     int *p = q;

     int i = *p; // dereference is o.k because type match (int * = int *)
     //int j = *q; // dereference is not o.k because type missmatch (int * = void *)

     // So we need a type cast
     // First, void * -> (int *)
     // (int *)q
     // Second, do dereference using *(...)
     // *((int *)q)

     int j = *((int *)q); // 
     //int k = ((int *) *q); 요건 안 됨
     return 0;
}
