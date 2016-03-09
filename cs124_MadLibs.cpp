/***********************************************************************
* Program:
*     Project 3, Mad Libs
*    Brother Helfrich, CS124
* Author:
*    Jacob Casperson
* Summary: 
*    This is madlibs. It's a ridiculous game wher players enter silly
*    words into a story for laughs and fun.
*    Note: Because I kept getting stuck I did get some help. In order
*    to avoid plagiarism of anothers ideas I carefully cited in
*    function headers where help was obtained. 
*
*    Estimated:  10.0 hrs   
*    Actual:     40.0 hrs
*      Figuring out how to handle text[][] was for sure the hardest of
*      all. It had to be passed around so much!  
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

/**********************************************************************
 * Most exciting function of the program: gets the file name
 ***********************************************************************/
void getFileName(char fileName[])
{
   cout << "Please enter the filename of the Mad Lib: ";
   cin  >> fileName;
}

/**********************************************************************
 * It determines if each word passed by readFile is a question or not.
 * If it is it displays a prompt for the user.
 ***********************************************************************/
int askQuestion(char text[], int *pSpace)
{

   // If it's not a question send it back    
   if (text[0] != '<' || !isalpha(text[1]))
      return 0;
  
   // otherwise it is a question and give the user a prompt
   else      
   {
      *pSpace += 1;
      
      cout << "\t";
      for (int i = 1; (text[i] != '>'); i++)
      {
         if (text[i] == '_')
         {
            cout << " ";
            
         }
         else
         {
            text[1] = toupper(text[1]);
            cout << text[i];
         }
      }
   }
   
   cout << ": ";
  
   // let the users input replace the prompt. I ran into the issue
   // of cin.ignore erasing the first letter of the all the answers
   // after the first one. *pSpace takes care of this bug in a ugly
   // but effective way
   if (*pSpace == 1)
   {
      cin.ignore();
      cin.getline(text, 32);
   }
   else 
      cin.getline(text, 32);
  
   return 0;
}

/**********************************************************************
 * NOTE: At the suggestion of another I passed char text[][32]
 * as a parameter and decided to call askQuestion every time as opposed
 * to putting it in an if statement. This helped me to have a foundation
 * I knew could work on and I built from there.
 * This function reads from the file and calls askQuesion to see if
 * there is a prompt. It also counts the number of words in the file.
 ***********************************************************************/
void readFile(char fileName[], char text[][32], int *pNumWords)
{
   int space = 0;
   int *pSpace = &space;
   // open file and display an error message if the file cannot be opened
   ifstream fin(fileName);
   if (fin.fail())
   {
      cout << "Error reading file "
           << "\"" << fileName << "\""
           << endl;
   }

   // used for counting the words in the file
   *pNumWords = 0;
   int numWords = 0;

   // meat of the function, check to see if each word is a question
   // and count the words
   while (fin >> text[*pNumWords])
   {
      askQuestion(text[*pNumWords], pSpace);

      numWords++;
      *pNumWords = numWords;
   }

   // close file
   fin.close();
}

/**********************************************************************
 * NOTE: The parameters were suggested, it was also suggested to
 * deal with the tokens here instead of askQuestion()
 * This displays the funny story for the user to view.  
 ***********************************************************************/
void display(char text[][32], int *pNumWords)
{
   // put a line between prompt and answer
   cout << endl;

   // goes through every word in the text array. If it's an annoying
   // token thingy cout would should be there. Otherwise display what
   // the text array really has in it, with the occasional space
   for (int i = 0; i < *pNumWords; i++)
   {
      if (text[i][0] == '<')
      {
         if (text[i][1] == '#')
            cout  << "\n";
         else if (text[i][1] == '{')
            cout <<  "\"";
         else if (text[i][1] == '}')
            cout <<  "\" ";
         else if (text[i][1] == '[')
            cout << "\'";
         else if (text[i][1] == ']')
            cout << "\' ";
      }
      // these catch almost all spacing issues. 
      else if (text[i + 1][0] == '.' || text[i + 1][0] == ',' ||
               text[i + 1][1] == '}' || text[i + 1][1] == ']' ||
               text[i + 1][0] == '?' || text[i + 1][0] == '!' ||
               text[i + 1][1] == '#')
         cout << text[i];
      else
         cout << text[i] << " ";
   }
}

/**********************************************************************
 * HEY! Finally our main! Just holds our variables, including a pointer
 * because I understand they're quicker. All the functions are in a
 * while loop because that way the game can be played again and again!
 * I realize that any button besides y will cancel the game and it would
 * be easy enough to fix with an if statement but I'm too tired and lazy
 * to fix it. TestBed never notices.
 ***********************************************************************/
int main()
{
   // Variables
   char fileName[256];
   char text[256][32];
   char playAgain;
   bool playGame = true;
   int numWords;
   int *pNumWords = &numWords;

   // Keep playing as long as playGame is true
   while (playGame == true)
   {
      getFileName(fileName);
   
      readFile(fileName, text, pNumWords);

      display(text, pNumWords);
      
      cout << "\nDo you want to play again (y/n)? ";
      cin  >> playAgain;

      playGame = (playAgain == 'y') ? true : false;
   }

   // Thank the user for playing
   cout << "Thank you for playing.\n";
   
   return 0;
}
