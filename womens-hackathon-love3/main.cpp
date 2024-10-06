#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include "library.h"
// 4 MESSAGES:
// 1. recognize and report phishing
// 2. use strong passwords
// 3. update your softwares
// 4. turn on multifactor authentication

using namespace std;

int main() {
  ifstream fin;
  Data data[4];
  fin.open("phrases.txt"); // open the file containing the phrases
  if (!fin.is_open()){
    cout << "File not found."; // shows if the file doesn't open
   } // end of if
  else {
    cout << "\nFile opened successfully.\n" << endl; // shows if the file is opened
  } // end of else

    collect_all(fin, data);
   

   display(data,4);

   fin.close(); // close the file

  return 0;
}




