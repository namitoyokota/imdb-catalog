#include <stdio.h>
#include <stdlib.h>
#include "parse.h"
#include "bst.h"

int main(void) {


    NODE* bst = NULL;
    //bst = insert(bst, 50);

    bst = parseFILE("./data/title.basics.tsv", bst);

    /*
	bst = insert(bst,12);
	bst = insert(bst,5);
	bst = insert(bst,8);
	bst = insert(bst,1);
	bst = insert(bst,9);
	bst = insert(bst,7);

	traverse(bst);

	Delete(bst,8);

	traverse(bst);

    Delete(bst,9);
    */

	traverse(bst);


    return 0;
}