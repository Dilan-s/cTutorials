#include "binaryheap.h"
#include <assert.h>
#include <string.h>



/*allocate memory in the heap for a node_heap type element and returns a pointer to the new node_heap*/

node_heap *allocate_node_heap(void)
{
  node_heap *heap = calloc(1, sizeof(node_heap));
  if (!heap) {
    perror("allocate_node_heap");
    exit(EXIT_FAILURE);
  }
  return heap;
}

/*initialise the heap array elements*/

void initial_heap(node_heap **heap,char* sequence)
{
  assert(heap);
  assert(sequence);

  for (int i = 0; i < strlen(sequence); i++) {
    node_heap *node = allocate_node_heap();
    node->key = &sequence[i];
    node->position = i+1;
    heap[i+1] = node;
  }  
}


/*print every element of the heap array*/
void print_elem_heap(node_heap **heap, int length)
{
  for (int i = 1; i <= length; i++) {
    printf("%c", heap[i]->key[0]);
    if (i == length) {
      printf("\n");
    } else {
      printf(" ");
    }
  }
  for (int i = 1; i <= length; i++) {
    printf("%d", heap[i]->position);
    if (i == length) {
      printf("\n");
    } else {
      printf(" ");
    }
  }
}

/* returns the index in the heap array where the parent is allocated for the index passed as argument*/

int parent(int index)
{
  return index / 2;
}

/* returns the index in the heap array where the left child is allocated for the index passed as argument*/

int left_child(int index)
{
  return 2 * index;
}

/* returns the index in the heap array where the right child is allocated for the index passed as argument*/

int right_child(int index)
{
  return 2 * index + 1;
}

/* exchange node_heap node1 to node_heap node2*/ 

void swap(node_heap *node1, node_heap *node2)
{
  assert(node1);
  assert(node2);
  node_heap temp = *node2;
  *node2 = *node1;
  *node1 = temp;
}

/*Moves down the value of the heap[current] so the subtree rooted at index "current" satisfies with the max-heap property*/ 

void max_heapify(node_heap **heap, int current, int heap_size)
{
  assert(heap);
  assert(heap[current]);

  int leftChild = left_child(current);
  int rightChild = right_child(current);

  if (leftChild > heap_size) {
    return;
  }
  if (leftChild == heap_size) {
    if ((heap[leftChild]->key[0]) > (heap[current]->key[0])){
      swap(heap[current], heap[leftChild]);
    }
    return;
  }
  int swapChild = ((heap[leftChild]->key[0]) > (heap[rightChild]->key[0])) ? leftChild : rightChild;

  if ((heap[swapChild]->key[0]) > (heap[current]->key[0])){
    swap(heap[current], heap[swapChild]);
    max_heapify(heap, swapChild, heap_size);
  }
  return;
}

/*it orders the heap so the ordered heap complies the max-heap property*/

void build_max_heap(node_heap **heap, int heap_size)
{
  assert(heap);
  for (int i = heap_size / 2; i > 0; i--) {
    max_heapify(heap, i, heap_size);
  }
}

/*starting from a max-heap ordered array, it moves the largest item from the heap and it into the array position left as the heap shrinks*/

void heapsort(node_heap **heap, int length)
{
  build_max_heap(heap, length);
  while(length > 0) {
    swap(heap[length], heap[1]);
    length--;
    build_max_heap(heap, length);
  }
}

/*free the memory allocated by a node_heap type element in the heap*/

void free_node(node_heap *node)
{
  free(node);
}

/*free the memory allocated in the heap array*/

void free_heap(node_heap **heap, int length)
{
  for (int i = 1; i <=length; i++) {
    free_node(heap[i]);
  }
  free(heap);
}
