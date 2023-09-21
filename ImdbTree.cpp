#include <iostream>
#include <string>
#include <vector>
#include "Bridges.h"
#include "DataSource.h"
#include "BSTElement.h"
#include <queue>
using namespace std;
using namespace bridges;

/*
  Step 1: Get the Bridges USER ID and API KEY for your program
          by creating an account and signing up (You can use any
          email): https://bridges-cs.herokuapp.com/login

  Step 2: User ID (Username) and Key (API Sha1 Key) can be
          found under Profile on the top left
*/


int main(int argc, char **argv)
{

    // Step 3: Test if the following print statement is being run
    cout << "Bridges: IMDB Data in a BST\n";

    /*
     Step 4: Create a Bridges object by uncommenting the next line
     and inserting the values from steps 1 and 2
    */
    //Bridges bridges(1, "USER_ID", "API_KEY");

    /*
       Step 5: Import IMDB data into a vector<ActorMovieIMDB> by
               referring to the Bridges IMDB documentation:
               https://bridgesuncc.github.io/tutorials/Data_IMDB.html
    */

    /*
       Step 6: Open the file "insertIntoBST.txt" and copy the provided
               function for inserting an actor/movie pair into a BST.
               Paste the function into this file above your "main" function.
    */

    /*
       Step 7: Use the insertion function from the previous step to insert
               any 100 actor/movie pairs into a Bridges BST. Refer to the
               Bridges IMDB documentation:
               https://bridgesuncc.github.io/tutorials/Data_IMDB.html
    */

    /*
       Step 8: Visualize this tree by referring to the Bridges BST documentation:
               https://bridgesuncc.github.io/tutorials/BinarySearchTree.html
    */

    /*
       Step 9: Color each level of the tree using a level-order traversal.
               Every node in a given level should have the same color.
               Do not use the same color in two consecutive levels. A starter
               queue has been provided in case you wish to use an iterative
               implementation of BFS.

               Refer to the Bridges BST Styling documentation:
               https://bridgesuncc.github.io/tutorials/BinarySearchTree.html

    */

    queue<BSTElement<string, string> *> q;

    /*
      Step 10: Visualize the updated tree. Comment out or remove the old
               visualization code from Step 8
    */

    return 0;
}