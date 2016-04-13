#include <stdio.h>

void sort(int* array, size_t size)
{
  int i = 0;
  int key = 0;

  if(NULL == array || 0 == size)
	return;

  // Starting from 1, we need to walk
  // to the end of the array.
  for(int j = 1; j < size; ++j) {
    // Our inner loop will start just below our outer, and
    // count backwards.
    i = j - 1;
    // We will take the value we're currently at,
    // and sort everything before it.
    key = array[j];
    // while 0 <= i < j, we will check to see
   // if the current value in our array is bigger
   // than "key"
    while(i >= 0 && array[i] > key) {
      // If it's bigger, then shift it forward
      // one position.
      array[i+1] = array[i];
      i = i -1;
    } 
    // store the key we started with in the found position.
    array[i+1] = key;   
  }

}

int main(int argc, char** argv) {
   int ar[] = {2, 3, 4, 5,10, 23, 22,7, 5};

   sort(ar, sizeof(ar)/sizeof(int));

   for(int i = 0; i < sizeof(ar)/sizeof(int); ++i)
      printf("%d\t", ar[i]);

   printf("\n");
   return 0;
}
