#include <stdio.h>

int partition(int* array, int low, int high)
{
   int pivot = array[high];
   int i = low;
   int tmp = 0;

   for(int j = low; j < high; ++j) {
     if(array[j] <= pivot) {
       tmp = array[i];
       array[i] = array[j];
       array[j] = tmp;

       i += 1;
     }
   } 
   tmp = array[i];
   array[i] = array[high];
   array[high] = tmp;
   return i;

}

void sort(int* array, int lower,  int upper)
{
  int i = 0;
  if (NULL == array)
    return;

  if(lower < upper) {
    i = partition(array, lower, upper);
    sort(array, lower, i-1);
    sort(array, i, upper);

  }
}

int main(int argc, char** argv) {
   int ar[] = {2, 3, 4, 5,10, 5};

   sort(ar, 0, (sizeof(ar)/sizeof(int)-1));

   for(int i = 0; i < sizeof(ar)/sizeof(int); ++i)
      printf("%d\t", ar[i]);

   printf("\n");
   return 0;
}
