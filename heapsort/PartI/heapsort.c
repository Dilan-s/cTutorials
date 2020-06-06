#include "binaryheap.h"
#include <string.h>
#include <assert.h>

#define MAX_STRING_LENGTH 20

int main(int argc, char **argv){
  assert(argc == 2);
  int size = (strlen(argv[1]) <= MAX_STRING_LENGTH) ? strlen(argv[1]) : MAX_STRING_LENGTH; 
  node_heap **heap = calloc(size + 1, sizeof(node_heap *));
  initial_heap(heap, argv[1]);
  print_elem_heap(heap, size);
  
  build_max_heap(heap, size);
  print_elem_heap(heap, size);

  heapsort(heap, size);
  print_elem_heap(heap, size);

  free_heap(heap, size);
  return EXIT_SUCCESS;
}
