//KACPER KOBEL
//CS211
//PROJECT 04: LADDER
//THIS GAME CONSTRUCTS A WORD LADDER TO FILL IN
//GLHF

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct {
    char* myWord;
    struct WordNode_struct* next; 
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;


//------------------- \/\/\/ TOP OF TASK 1 \/\/\/ --------------------
// This function counts how many words in the file match a certain length
// filename (name of file); wordSize (length of word)
// Returns the # of matching words, or -1 if file cannot be opened
int countWordsOfLength(char* filename, int wordSize) { 
    FILE* fp = fopen(filename, "r");

    if(fp == NULL)
    {
        return -1;
    }

    char temp[100];
    int ct = 0;
    while (fscanf(fp, "%s", temp) != EOF)
    {
        if (strlen(temp) == wordSize)
        {
            ct++;
        }
    }
    fclose(fp);
    return ct;
}
//This function builds an array of words found in the previous function
// filename (name of file); words (array of words); numWords (number of words); wordSize (length of words)
// Returns true if successful, false if error 
bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { 
    FILE* fp = fopen(filename, "r");
    if(fp == NULL)
    {
        return false;
    }

    char temp[100];
    int index = 0;

    while (fscanf(fp, "%s", temp) != EOF)
    {
        if ((int)strlen(temp) == wordSize)
        {
            if (index >= numWords)
            {
                fclose(fp);
                return false;
            }
            words[index] = (char*)malloc((wordSize + 1) * sizeof(char));
            strcpy(words[index], temp);
            index++;
        }
    }
    fclose(fp);

    if(index != numWords)
    {
        return false;
    }
    return true;
}
// This function searches for a word using binary searches
// words (array of words); aWord (word to find); loInd (low index); hiInd (high index)
// Returns index of word if found, -1 if not found
int findWord(char** words, char* aWord, int loInd, int hiInd) {
    while (loInd <= hiInd)
    {
        int mid = (loInd + hiInd) / 2;
        int cmp = strcmp(words[mid], aWord);

        if (cmp == 0)
        {
            return mid;
        }
        else if (cmp < 0)
        {
            loInd = mid + 1;
        }
        else
        {
            hiInd = mid - 1;
        }
    }
    return -1; // modify this line
}
// This function frees all memory used by the word array
// words (array of words); numWords (number of words)
// void
void freeWords(char** words, int numWords) {
    for (int i = 0; i < numWords; i++)
    {
        free(words[i]);
    }
    free(words);
}

//---------------------- ^^^ END OF TASK 1 ^^^ ----------------------


//------------------- \/\/\/ TOP OF TASK 2 \/\/\/ -------------------
// This function counts how many characters differ between two strings
// str1 (first string); str2 (second string)
// Returns number of differing characters
int strCmpCnt(char* str1, char* str2) {
    int ct = 0;
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            ct++;
        }
        i++;
    }
    int j = i;
    while (str1[j] != '\0')
    {
        ct++;
        j++;
    }
    int k = i;
    while (str2[k] != '\0')
    {
        ct++;
        k++;
    }
    return ct;
}
// This function finds the index of the first differing character
// str1 (first string); str2 (second string)
// Returns index of first difference or -1 if strings are the same
int strCmpInd(char* str1, char* str2) {
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            return i;
        }
        i++;
    }
    if (str1[i] != '\0' || str2[i] != '\0')
    {
        return i;
    }   
    return -1;
}

//---------------------- ^^^ END OF TASK 2 ^^^ ----------------------


//------------------- \/\/\/ TOP OF TASK 3 \/\/\/ -------------------
// This function inserats a word at the front of the ladder
// ladder (pointer to wordNode list), newWord (word to add)
// void
void insertWordAtFront(WordNode** ladder, char* newWord) {
    WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));
    newNode->myWord = newWord;
    newNode->next = *ladder;
    *ladder = newNode;
}
// This function counts the height of the ladder
// ladder (WordNode list)
// Returns the height of the ladder
int getLadderHeight(WordNode* ladder) {
    int ct = 0;
    WordNode* curr = ladder;

    while(curr != NULL)
    {
        ct++;
        curr = curr->next;
    }
    return ct;
}
// THis function checks if an entered word is valid for the ladder
// words (dictionary); numWords (array size); wordSize (length of words); ladder (ladder); aWord (input)
// Returns true if valid, false otherwise
bool checkForValidWord(char** words, int numWords, int wordSize, WordNode* ladder, char* aWord) {
        if(strcmp(aWord, "DONE") == 0)
        {
            printf("Stopping with an incomplete word ladder...\n");
            return true;
        }
        if((int)strlen(aWord) != wordSize)
        {
        // user entered a word that is too long/short - invalid, priority #2
            printf("Entered word does NOT have the correct length. Try again...\n");
            return false;
        }
        if(findWord(words, aWord, 0, numWords -1) < 0)
        {
        // user entered a word that is not found in the dictionary - invalid, priority #3
            printf("Entered word NOT in dictionary. Try again...\n");
            return false;
        }
        if(ladder != NULL)
        {
            if(strCmpCnt(ladder->myWord, aWord) != 1)
            {
                printf("Entered word is NOT a one-character change from the previous word. Try again...\n");
                return false;
            }
        }    
        printf("Entered word is valid and will be added to the word ladder.\n");
        return true; //modify this line
}
// This function checks if the ladder has reached the last word
// ladder (ladder); finalWord (target)
// Returns true if complete, false otherwise
bool isLadderComplete(WordNode* ladder, char* finalWord) {
    if (ladder == NULL)
    {
        return false;
    }
    return (strcmp(ladder->myWord, finalWord) == 0);
}
// This function creates a copy of a ladder
// ladder (ladder)
// Returns a pointer to a new copied ladder
WordNode* copyLadder(WordNode* ladder) {
    if (ladder == NULL)
    {
        return NULL;
    }
    WordNode* newHead = NULL;
    WordNode* curr = ladder;

    newHead = (WordNode*)malloc(sizeof(WordNode));
    newHead->myWord = curr->myWord;
    newHead->next = NULL;

    WordNode* tail = newHead;
    curr = curr->next;

    while(curr != NULL)
    {
        WordNode* newNode = (WordNode*)malloc(sizeof(WordNode));
        newNode->myWord = curr->myWord;
        newNode->next = NULL;

        tail->next = newNode;
        tail = newNode;
        
        curr = curr->next;
    }
    return newHead;
}
// Frees memory used by the ladder
// ladder (ladder)
// void
void freeLadder(WordNode* ladder) {
    WordNode* curr = ladder;

    while(curr != NULL)
    {
        WordNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

//---------------------- ^^^ END OF TASK 3 ^^^ ----------------------


//------------------- \/\/\/ TOP OF TASK 4 \/\/\/ -------------------
// This function displays ladder but with placeholder elipse's
// ladder (ladder)
// void
void displayIncompleteLadder(WordNode* ladder) {


    for (int i = 0; i < 3; i++)
    {
        printf("  ...\n");
    }
   
    WordNode* curr = ladder;
    
    while(curr != NULL)
    {
        printf("  %s\n", curr->myWord);
        curr = curr->next;
    }
}
// This function displays the full ladder
//Ladder (ladder)
// void
void displayCompleteLadder(WordNode* ladder) {
    
    if(ladder == NULL)
    {
        return;
    }
    int height = getLadderHeight(ladder);
    WordNode** arr = (WordNode**)malloc(sizeof(WordNode*) * height);
    WordNode* curr = ladder;
    int i = 0;

    while (curr != NULL)
    {
        arr[i++] = curr;
        curr = curr->next;
    }

    for (int j = 0; j < height; j++)
    {
        printf("  %s\n", arr[j]->myWord);
        if (j < height - 1)
        {
            int ind = strCmpInd(arr[j]->myWord, arr[j+1]->myWord);
            int len = strlen(arr[j]->myWord);
            printf("  ");

            for (int k = 0; k < ind; k++)
            {
                printf(" ");
            }
            printf("^");
            for(int k = ind + 1; k < len; k++)
            {
                printf(" ");
            }
            printf("\n");
        }
    }
    free(arr);
}

//---------------------- ^^^ END OF TASK 4 ^^^ ----------------------


//------------------- \/\/\/ TOP OF TASK 5 \/\/\/ -------------------
// This function adds a ladder to the end of the ladder list
// list (list of ladders); newLadder (ladder to be added)
// void
void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {
    LadderNode* newNode = (LadderNode*)malloc(sizeof(LadderNode));
    newNode->topWord = newLadder;
    newNode->next = NULL;

    if (*list == NULL)
    {
        *list = newNode;
        return;
    }
    LadderNode* curr = *list;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    curr->next = newNode;

    //---------------------------------------------------------
    // TODO - write insertLadderAtBack()
    //---------------------------------------------------------
}
// This function returns and removes the first ladder from the list of ladders
// list (list of ladders)
// Returns the pointer of the removed ladder
WordNode* popLadderFromFront(LadderNode** list) {
    if (*list ==NULL)
    {
        return NULL;
    }

    LadderNode* front = *list;
    WordNode* ladder = front->topWord;
    *list = front->next;
    free(front);
    return ladder;
}
// This function frees the memory used by the ladder list
// myList (list of ladders)
// void
void freeLadderList(LadderNode* myList) {
    while (myList != NULL)
    {   
        LadderNode* temp = myList;
        myList = myList->next;
        freeLadder(temp->topWord);
        free(temp);
    }
}

//---------------------- ^^^ END OF TASK 5 ^^^ ----------------------


//------------------- \/\/\/ TOP OF TASK 6 \/\/\/ -------------------
// This function finds the shortest word ladder
// words (dictionary); useWord (flag); numWords (array size); wordSize (word length); startWord, finalWord
// Returns pointer to shortest ladder or NULL if there is not one
WordNode* findShortestWordLadder(   char** words, 
                                    bool* usedWord, 
                                    int numWords, 
                                    int wordSize, 
                                    char* startWord, 
                                    char* finalWord ) {
                                        LadderNode* list = NULL;
                                        int startInd = findWord(words, startWord, 0, numWords - 1);

                                        WordNode* startLadder = NULL;
                                        insertWordAtFront(&startLadder, words[startInd]);

                                        insertLadderAtBack(&list, startLadder);

                                        usedWord[startInd] = true;

                                        while (list != NULL)
                                        {
                                            WordNode* currLadder = popLadderFromFront(&list);
                                            char* currWord = currLadder->myWord;

                                            int currIndex = findWord(words, currWord, 0, numWords -1);   

                                            if (!usedWord[currIndex])
                                            {
                                                usedWord[currIndex] = true;
                                            }


                                            if (strcmp(currWord, finalWord) == 0)
                                            {
                                                freeLadderList(list);
                                                return currLadder;
                                            }
                                            for (int i = 0; i < numWords; i++)
                                            {
                                                if (!usedWord[i] && strCmpCnt(currWord, words[i]) == 1)
                                                {
                                                    WordNode* newLadder = copyLadder(currLadder);
                                                    insertWordAtFront(&newLadder, words[i]);

                                                    insertLadderAtBack(&list, newLadder);

                                                    usedWord[i] = true;
                                                }
                                            }
                                            freeLadder(currLadder);
                                        }
                                        return NULL;
    //---------------------------------------------------------
    // TODO - write findShortestWordLadder()
    //---------------------------------------------------------
    
    

}

//---------------------- ^^^ END OF TASK 5 ^^^ ----------------------


//------------------- \/\/\/ TOP OF OTHERS \/\/\/ -------------------


// randomly set a word from the dictionary word array
void setWordRand(char** words, int numWords, int wordSize, char* aWord) {
    printf("  Picking a random word for you...\n");
    strcpy(aWord,words[rand()%numWords]);
    printf("  Your word is: %s\n",aWord);
}

// interactive user-input to set a word;
//  ensures the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    if (strcmp(aWord,"RAND") != 0) printf("  Enter a %d-letter word (enter RAND for a random word): ", wordSize);
    int count = 0;
    while (!valid) {
        if (strcmp(aWord,"RAND") != 0) scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word (enter RAND for a random word): ", wordSize);
            }
        } else if (strcmp(aWord,"RAND") != 0) {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word (enter RAND for a random word): ", wordSize);
        }
        if (!valid && (count >= 5 || strcmp(aWord,"RAND") == 0)) { //too many tries, picking random word
            setWordRand(words, numWords, wordSize, aWord);
            valid = true;
        }
    }
}

// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}

//---------------------- ^^^ END OF OTHERS ^^^ ----------------------



//-----------------------------------------------------
// The primary application is mostly fully-develop as
//  provided in main(); changes in main() should be
//  limited to updates made for the game play task(s)
//  and testing-related purposes (such as command-line
//  arguments for "TESTING MODE" to call a test case 
//  master function, or something similar)
//-----------------------------------------------------
int main(int argc, char* argv[]) {

    printf("\n");
    printf("--------------------------------------------\n");
    printf("Welcome to the CS 211 Word Ladder Generator!\n");
    printf("--------------------------------------------\n\n");
    

    //-------------- \/\/\/ TOP OF PROGRAM SETTINGS \/\/\/ --------------
    //--- COMMAND-LINE ARGUMENTS AND/OR INTERACTIVE USER-INPUT \/\/\/ ---

    
    // default values for program parameters that may be set with
    //  command-line arguments
    int wordSize = -2114430;
    char dict[100] = "notAfile";
    char startWord[30] = "notAword";
    char finalWord[30] = "notValid";
    bool playMode = false;
    
    printf("\nProcessing command-line arguments...\n");

    //-------------------------------------------------------------------
    // command-line arguments:
    //  [-n wordLen] = sets word length for word ladder;
    //                 if wordLen is not a valid input
    //                 (cannot be less than 2 or greater than 20),
    //                 or missing from command-line arguments,
    //                 then let user set it using interactive user input
    // [-d dictFile] = sets dictionary file;
    //                 if dictFile is invalid (file not found) or
    //                 missing from command-line arguments, then let
    //                 user set it using interactive user input
    // [-s startWord] = sets the starting word;
    //                  if startWord is invalid
    //                  (not in dictionary or incorrect length) or
    //                  missing from command-line arguments, then let
    //                  user set it using interactive user input
    // [-f finalWord] = sets the final word;
    //                  if finalWord is invalid
    //                  (not in dictionary or incorrect length) or
    //                  missing from command-line arguments, then let
    //                  user set it using interactive user input
    // [-p playModeSwitch] = turns playMode ON if playModeSwitch is "ON"
    //                       or leaves playMode OFF if playModeSwitch is
    //                       anything else, including "OFF"
    //-------------------------------------------------------------------

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i],"-n") == 0 && argc > i+1) {
            wordSize = atoi(argv[i+1]);
            ++i;
        } else if (strcmp(argv[i],"-d") == 0 && argc > i+1) {
            strcpy(dict, argv[i+1]);
            ++i;
        } else if (strcmp(argv[i],"-s") == 0 && argc > i+1) {
            strcpy(startWord, argv[i+1]);
            ++i;
        } else if (strcmp(argv[i],"-f") == 0 && argc > i+1) {
            strcpy(finalWord, argv[i+1]);
            ++i;
        } else if (strcmp(argv[i],"-p") == 0 && argc > i+1) {
            playMode = (strcmp(argv[i+1],"ON") == 0);
            ++i;
        }
    }
    
    srand((int)time(0));
    
    // set word length using interactive user-input
    //  if wordSize == -2114430, it was NOT set with command-line args
    while (wordSize < 2 || wordSize > 20) {
        if (wordSize != -2114430) printf("Invalid word size for the ladder: %d\n", wordSize);
        printf("Enter the word size for the ladder: ");
        scanf("%d",&wordSize);
        printf("\n");
    }

    printf("This program is a word ladder building game and a solver that\n");
    printf("finds the shortest possible ");
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // interactive user-input to set the dictionary file;
    //  check that file exists; if not, user enters another file
    //  if file exists, count #words of desired length [wordSize];
    //  if dict == "notAfile", it was NOT set with command-line args
    int numWords = countWordsOfLength(dict,wordSize);
    while (numWords < 0) {
        if (strcmp(dict, "notAfile") != 0) {
            printf("  Dictionary %s not found...\n",dict);
        }
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        numWords = countWordsOfLength(dict,wordSize);
    }
    
    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i]
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize);
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n\n");

    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array,
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    // start/final words may have already been set using command-line arguments
    // the start/final word can also be set to "RAND" resulting in a random
    //  assignment from any element of the words array
    if (strcmp(startWord,"RAND")==0) {
        printf("Setting the start word randomly...\n");
        setWordRand(words, numWords, wordSize, startWord);
    } else if (findWord(words, startWord,0, numWords-1) < 0 || strlen(startWord) != wordSize) {
        if (strcmp(startWord,"notAword")==0) {
            printf("Setting the start %d-letter word... \n", wordSize);
        } else {
            printf("Invalid start word %s. Resetting the start %d-letter word... \n", startWord, wordSize);
        }
        setWord(words, numWords, wordSize, startWord);
    }
    printf("\n");
    
    if (strcmp(finalWord,"RAND")==0) {
        printf("Setting the final word randomly...\n");
        setWordRand(words, numWords, wordSize, finalWord);
    } else if (findWord(words, finalWord,0, numWords-1) < 0 || strlen(finalWord) != wordSize) {
        if (strcmp(finalWord,"notValid")==0) {
            printf("Setting the final %d-letter word... \n", wordSize);
        } else {
            printf("Invalid final word %s. Resetting the final %d-letter word... \n", finalWord, wordSize);
        }
        setWord(words, numWords, wordSize, finalWord);
    }
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");
    
    //----------------- ^^^ END OF PROGRAM SETTINGS ^^^ -----------------
    
    
    //-------------- \/\/\/ TOP OF GAME PLAY SECTION \/\/\/ --------------
    
    if (!playMode) {
        printf("\n");
        printf("---------------------------------------------\n");
        printf("No Word Ladder Builder Game; Play Mode is OFF\n");
        printf("---------------------------------------------\n");
        printf("\n");
    } else {
        printf("\n");
        printf("-----------------------------------------------\n");
        printf("Welcome to the CS 211 Word Ladder Builder Game!\n");
        printf("-----------------------------------------------\n");
        printf("\n");

        printf("Your goal is to make a word ladder between two ");
        printf("%d-letter words: \n  %s -> %s\n\n",wordSize, startWord,finalWord);
        
        WordNode* userLadder = NULL;
        int ladderHeight = 0; // initially, the ladder is empty
        int startInd = findWord(words, startWord, 0, numWords-1);
        insertWordAtFront(&userLadder, words[startInd]);
        ladderHeight++; // Now, the ladder has a start word
            
        char aWord[30] = "XYZ";
        printf("\n");
        
        // Let the user build a word ladder interactively & iteratively.
        // First, check that ladder is not too long AND not complete.
        //-------------------------------------------------------------------
        // TODO - PART OF Task 4 (GAME PLAY): modify the while loop condition
        //          such that the word ladder building process continues only
        //          if BOTH of the following conditions are met:
        //              1. the user is NOT attempting to stop the word ladder
        //                 building process, which occurs if the entered word
        //                 [aWord] from the last iteration is "DONE"
        //              2. the ladder is still incomplete; i.e. the last word
        //                 added to ladder is not the final word;
        //                 note: this should use a call to isLadderComplete()
        //-------------------------------------------------------------------
        while ( strcmp(aWord, "DONE") != 0 && !isLadderComplete(userLadder, finalWord) ) {   // modify this line
            printf("The goal is to reach the final word: %s\n",finalWord);
            printf("The ladder is currently: \n");
            displayIncompleteLadder(userLadder);
            printf("Current ladder height: %d\n",ladderHeight);
            printf("Enter the next word (or DONE to stop): ");
            scanf("%s",aWord);
            printf("\n");
            
            // Make sure the entered word is valid for the next ladder rung;
            // if not, repeatedly allow user to enter another word until one is valid
            while (!checkForValidWord(words, numWords, wordSize, userLadder, aWord)) {
                printf("Enter another word (or DONE to stop): ");
                scanf("%s",aWord);
                printf("\n");
            }

            // add the entered word to the ladder (unless it is "DONE")
            if (strcmp(aWord,"DONE") != 0) {
                int currInd = findWord(words, aWord, 0, numWords-1);
                insertWordAtFront(&userLadder, words[currInd]);
                ladderHeight++;
            }
            printf("\n");
        }

        // Check if the built word ladder is complete and
        // display the word ladder appropriately.
        if (isLadderComplete(userLadder, finalWord)) {
            printf("Word Ladder complete!\n\n");
            displayCompleteLadder(userLadder);
            printf("\nWord Ladder height = %d\n\n", ladderHeight);
            printf("Can you find a shorter Word Ladder next time??? \n");
        } else {
            printf("The final Word Ladder is incomplete:\n");
            displayIncompleteLadder(userLadder);
            printf("Word Ladder height = %d\n\n", ladderHeight);
            printf("Can you complete the Word Ladder next time??? \n");
        }
        freeLadder(userLadder);
    }
    
    //----------------- ^^^ END OF GAME PLAY SECTION ^^^ -----------------
    
    
    //-------------- \/\/\/ TOP OF WORD LADDER SOLVER \/\/\/ --------------
    
    printf("\n\n");
    printf("-----------------------------------------\n");
    printf("Welcome to the CS 211 Word Ladder Solver!\n");
    printf("-----------------------------------------\n");
    printf("\n");
    

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // OPTIONAL EXTENTION TO FIND LONGEST WORD LADDER:
    //  program must end with finding the shortest word ladder
    //  (& the associated print statements); if you choose to
    //  extend your program to find the longest word ladder,
    //  put the long word ladder algorithm (& the associated
    //  print statements) BEFORE the short word ladder algorithm
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    
    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    // display word ladder and its height if one was found
    for (int i =0; i < numWords; i++)
    {
        usedWord[i] = false;
    }
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);
    } else {
        printf("Shortest Word Ladder found!\n\n");
        displayCompleteLadder(myLadder);
        //printLadder(myLadder);
    }
    printf("\nWord Ladder height = %d\n\n",getLadderHeight(myLadder));

    //----------------- ^^^ END OF WORD LADDER SOLVER ^^^ -----------------
    
    
    //-------------- \/\/\/ TOP OF CLEAN-UP \/\/\/ --------------
    
    // TODO - Part of ALL Tasks:
    //      free all heap-allocated memory to avoid potential
    //      memory leaks. Since the word length for the word
    //      ladder is variable (i.e. set by a command-line
    //      argument or interactive user-input) any array
    //      whose size depends on the word length should be
    //      dynamically heap-allocated, and thus, must be
    //      tracked and freed before program termination.
    //      A big part of the memory management & freeing
    //      is handled by the following functions, but
    //      you may have introduced additional heap-memory
    //      allocations, especially as part of the game play.
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    //----------------- ^^^ END OF CLEAN-UP ^^^ -----------------

    
    return 0;
}
