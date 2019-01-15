/**
 * Pass by value and pointer example
 *
 * Yusuf Pisan
 */

#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *nextPtr;
};

// synonym for struct Node
typedef struct Node Node;

// data types match what is passed exactly
// int copied, Node copied and all its members copied,
// Nodeptr (a memory address) copied
void passByValue(int anInt, Node aNode, Node *aNodePtr) {
  printf("Inside passByValue\n");
  printf("Int is %d, memory address %p\n", anInt, &anInt);
  printf("Node has data %d, memory address of Node %p\n", aNode.data, &aNode);
  printf("NodePtr has data %d, memory address of NodePtr %p\n",
         aNodePtr->data, &aNodePtr);
  // changing copied int value, no effect beyond function
  anInt = anInt * 2;
  // changing copied node data value, no effect beyond function
  aNode.data = aNode.data * 2;
  // changing copied nodeptr data value
  // nodeptr is a memory address, copying it gives the same memory address
  // changing data at that memory address changes data value
  aNodePtr->data = aNodePtr->data * 2;
}

void testBpassByValue() {
  int i = 10;
  Node n;
  n.data = 100;
  n.nextPtr = NULL;
  Node *nptr = (Node *) malloc(sizeof(Node));
  nptr->data = 1000;
  nptr->nextPtr = NULL;

  printf("Before passByValue\n");
  printf("Int is %d, memory address %p\n", i, &i);
  printf("Node has data %d, memory address of Node %p\n", n.data, &n);
  printf("NodePtr has data %d, memory address of NodePtr %p\n\n",
         nptr->data, &nptr);

  passByValue(i, n, nptr);

  printf("\nAfter passByValue\n");
  printf("Int is %d, memory address %p\n", i, &i);
  printf("Node has data %d, memory address of Node %p\n", n.data, &n);
  printf("NodePtr has data %d, memory address of NodePtr %p\n",
         nptr->data, &nptr);
}

void passByPointerChangeDataValue(int *anIntPtr, Node **aNodePtrPtr) {
  printf("Inside passByPointerChangeDataValue\n");
  printf("Int pointer points to %d which is stored at address %p\n",
         *anIntPtr, anIntPtr);
  printf("NodePtrPtr has value %p, it is pointing to that address\n", *aNodePtrPtr);
  printf("That memory address has the node with data %d\n", (*aNodePtrPtr)->data);
  // changing value pointed by this integer pointer
  *anIntPtr = *anIntPtr * 2;

  // we can change the data pointed by node pointer
  (*aNodePtrPtr)->data = (*aNodePtrPtr)->data * 2;
}

void passByPointerChangeToNewNode(int *anIntPtr, Node **aNodePtrPtr) {
  printf("Inside passByPointerChangeToNewNode\n");
  printf("Int pointer points to %d which is stored at address %p\n",
         *anIntPtr, anIntPtr);
  printf("NodePtrPtr has value %p, it is pointing to that address\n", *aNodePtrPtr);
  printf("That memory address has the node with data %d\n", (*aNodePtrPtr)->data);
  // changing value pointed by this integer pointer
  *anIntPtr = *anIntPtr * 2;

  // Say NodePtrPtr has address to 0xFA2
  // at 0xFA2 the value 0xFB2 is stored (pointing to another memory address)
  // at OxFB2 the value 0xFC2 is stored
  // 0xFC2 is where the Node is, that is where the data is

  // Can change the value at 0xFB2 which is the pointer to the Node
  // Can make it point to a totally new node
  Node *another = (Node *) malloc(sizeof(Node));
  another->data = 25;
  another->nextPtr = NULL;
  // Say "another" is at memory location 0xFF01
  // OxFB2 now has the value 0xFF01
  *aNodePtrPtr = another;
  printf("\nanother node at address %p has been created\n", another);
  printf("NodePtrPtr now has value %p, pointing to that address\n\n", *aNodePtrPtr);
  // Now we no longer have any way of getting to the old node
  // we created a memory leak
}

void testPassByPointer() {
  int i = 10;
  Node *nptr = (Node *) malloc(sizeof(Node));
  nptr->data = 1000;
  nptr->nextPtr = NULL;

  printf("Before passByPointerChangeDataValue\n");
  printf("Int is %d, memory address %p\n", i, &i);
  printf("NodePtr has data %d, pointing to a node at %p\n\n",
         nptr->data, nptr);

  // passing address of int and adress of Node*
  passByPointerChangeDataValue(&i, &nptr);

  printf("\nAfter passByPointerChangeDataValue, before passByPointerChangeToNewNode\n");
  printf("Int is %d, memory address %p\n", i, &i);
  printf("NodePtr has data %d, pointing to a node at %p\n\n",
         nptr->data, nptr);

  // passing address of int and adress of Node*
  passByPointerChangeToNewNode(&i, &nptr);

  printf("\nAfter passByPointerChangeToNewNode\n");
  printf("Int is %d, memory address %p\n", i, &i);
  printf("NodePtr has data %d, pointing to a node at %p\n\n",
         nptr->data, nptr);
  printf("NodePtr is pointing to a totally new node, not just new data!!!\n\n");

}

int main() {
  testBpassByValue();
  printf("\n===================\n");
  testPassByPointer();
  printf("Done\n");
  return 0;
}

/**
Output:

/Users/pisan/bitbucket/github/pisan133/pointer-to-pointer/cmake-build-debug/pointer_to_pointer
Before passByValue
Int is 10, memory address 0x7fff5165d9fc
Node has data 100, memory address of Node 0x7fff5165d9e0
NodePtr has data 1000, memory address of NodePtr 0x7fff5165d9d8

Inside passByValue
Int is 10, memory address 0x7fff5165d9bc
Node has data 100, memory address of Node 0x7fff5165d9a0
NodePtr has data 1000, memory address of NodePtr 0x7fff5165d9b0

After passByValue
Int is 10, memory address 0x7fff5165d9fc
Node has data 100, memory address of Node 0x7fff5165d9e0
NodePtr has data 2000, memory address of NodePtr 0x7fff5165d9d8

===================
Before passByPointerChangeDataValue
Int is 10, memory address 0x7fff5165d9fc
NodePtr has data 1000, pointing to a node at 0x7fbc0cc026a0

Inside passByPointerChangeDataValue
Int pointer points to 10 which is stored at address 0x7fff5165d9fc
NodePtrPtr has value 0x7fbc0cc026a0, it is pointing to that address
That memory address has the node with data 1000

After passByPointerChangeDataValue, before passByPointerChangeToNewNode
Int is 20, memory address 0x7fff5165d9fc
NodePtr has data 2000, pointing to a node at 0x7fbc0cc026a0

Inside passByPointerChangeToNewNode
Int pointer points to 20 which is stored at address 0x7fff5165d9fc
NodePtrPtr has value 0x7fbc0cc026a0, it is pointing to that address
That memory address has the node with data 2000

another node at address 0x7fbc0cd00000 has been created
NodePtrPtr now has value 0x7fbc0cd00000, pointing to that address


After passByPointerChangeToNewNode
Int is 40, memory address 0x7fff5165d9fc
NodePtr has data 25, pointing to a node at 0x7fbc0cd00000

NodePtr is pointing to a totally new node, not just new data!!!

Done

Process finished with exit code 0

*/
