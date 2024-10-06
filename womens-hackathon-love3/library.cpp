#include "library.h"
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>

// delete this later if not working
//  #include <Windows.h>
//  #include "MMSystem.h"

using namespace std;

// collect one finds put the scentence into an array. Then it finds the number
// of words in the array, and the first letter of the array.

int num_rows;
void collect_one(ifstream &fin, Data &D) {
  string sentence,key;
 getline(fin, sentence);
  fin.ignore();
  D.length = sentence.length();
  cout<<sentence.length();
  for (int i = 0; i < sentence.length(); i++) {
    fin >> D.sentence[i];
    cout<<D.sentence[i];
  }
  cout<<endl;
  for (int i = 0; i < sentence.length(); i++) {
    if (D.sentence[i] == " ") {
      D.number_of_words++;
    }
  } // end of for
  D.firstletter = D.sentence[0];
   key=findkey(D);
  numberofaccidentals(D,key,D.number_of_words);
  fullkeysignature(D, D.major, D.accidentals);

  convert_partA(D);
  convert_partB(D);
} // end of collect_one

void collect_all(ifstream &fin, Data D[]) {
  num_rows=0;
  while (!fin.eof()) {
    collect_one(fin, D[num_rows]);
    num_rows+=1;
  } // while not at the end of file, end of while
} // end of collect all

string findkey(Data &D) {
  string firstletter = D.firstletter;
  bool flats = false;
  bool sharps = false;
  string answer;

  if (firstletter == "A" || firstletter == "B" || firstletter == "C" ||
      firstletter == "D" || firstletter == "E" || firstletter == "F" ||
      firstletter == "G" || firstletter == "H" || firstletter == "I" ||
      firstletter == "J" || firstletter == "K" || firstletter == "L" ||
      firstletter == "M") {
    flats = true;
    sharps = false;
  } else {
    flats = false;
    sharps = true;
  }


  if( flats ==true){
    answer = "flats";
  }else{
     answer = "sharps";
  }
  // this finds whether or not the key signature is flats or sharps
  // once we find this, we will return it and use this to find the overall key
  // signture
  return answer;
}

int numberofaccidentals(Data &D, string keysignature,
                        int numberofwordsinphrase) {
  int accidentals = 0;
  numberofwordsinphrase = accidentals;
  // this finds the number of accidentals for the sentence
  // this does NOT show us whether or not the key signature is flats or sharps
  // we need the previous function to show us this information
  // this function will return the number of accidentals
  // we can use the number of accidentals and whether or not the key signature
  // is flats or sharps to find the overall key signature
  return accidentals;
}

string fullkeysignature(Data &D, string keysignature, int accidentals) {
  findkey(D);
  string fullsignature;
  switch (accidentals) {
  case 1: // 1 accidental
    if ((accidentals == 1) && (findkey(D)=="flats")) {
      fullsignature = "F major";
    } else { // 1 accidental and the key signature is sharp
      fullsignature = "G major";
    }
    break;
  case 2: // 2 accidentals
    if ((accidentals == 2) && (findkey(D)=="flats")) {
      fullsignature = "Bb major";
    } else { // 2 accidentals and the key signature is sharp
      fullsignature = "D major";
    }
    break;
  case 3: // 3 accidentals
    if ((accidentals == 3) && (findkey(D)=="flats")) {
      fullsignature = "Eb major";
    } else { // 3 accidentals and the key signature is sharp
      fullsignature = "A major";
    }
    break;
  case 4: // 4 accidentals
    if ((accidentals == 4) && (findkey(D)=="flats")) {
      fullsignature = "Ab major";
    } else { // 4 accidentals and the key signature is sharp
      fullsignature = "E major";
    }
    break;
  case 5: // 5 accidentals
    if ((accidentals == 5) && (findkey(D)=="flats")) {
      fullsignature = "Db major";
    } else { // 5 accidentals and the key signature is sharp
      fullsignature = "B major";
    }
    break;
  case 6: // 6 accidentals
    if ((accidentals == 6) && (findkey(D)=="flats")) {
      fullsignature = "Gb major";
      
    } else { // 6 accidentals and the key signature is sharp
      fullsignature = "F# major";
    }
    break;
  case 7: // 7 accidentals
    if ((accidentals == 7) && (findkey(D)=="flats")) {
      fullsignature = "Cb major";
    } else {
      fullsignature = "C# major";
    }
    break;
  default: // 0 accidentals -- this case will never appear, because it's
           // impossible to have 0 words in the decoded phrase
    fullsignature = "C major";
  }

  D.major = fullsignature;

  // this function takes the number of accidentals and whether or not a key is
  // using sharps or flats to determine the key signature this function will
  // return the full key signature we can find out the key signature using the
  // key signature circle --> refer to the png
  return D.major;
}

void convert_partA(Data &D) {
  for (int i = 0; i < D.length; i++) {
    if (((D.sentence[i] >= "a") && (D.sentence[i] <= "g")) ||
        ((D.sentence[i] >= "A") && (D.sentence[i] <= "G"))) {
      D.length_of_note[i] = "quater note";
    } else if (((D.sentence[i] >= "h") && (D.sentence[i] <= "n")) ||
               ((D.sentence[i] >= "H") && (D.sentence[i] <= "N"))) {
      D.length_of_note[i] = "eighth note";
    } else if (((D.sentence[i] >= "o") && (D.sentence[i] <= "u")) ||
               ((D.sentence[i] >= "O") && (D.sentence[i] <= "U"))) {
      D.length_of_note[i] = "sixteenth note";
    } else if (((D.sentence[i] == "v") || (D.sentence[i] == "z")) ||
               ((D.sentence[i] == "V") || (D.sentence[i] == "Z"))) {
      D.length_of_note[i] = "thirty second note";
    } else { // if the letter is a space, it is a rest
      D.length_of_note[i] = "rest";
    }
  }
}

void convert_partB(Data &D) {
  for (int i = 0; i < D.length; i++) {
    if ((D.sentence[i] == "a") || (D.sentence[i] == "A") ||
        (D.sentence[i] == "h") || (D.sentence[i] == "H") ||
        (D.sentence[i] == "o") || (D.sentence[i] == "O") ||
        (D.sentence[i] == "v") || (D.sentence[i] == "V")) {
      if ((D.major == "Ab major") || (D.major == "Eb major") ||
          (D.major == "Db major") || (D.major == "Gb major") ||
          (D.major == "Cb major")) {
        D.note[i] = "Ab";
      } else if ((D.major == "B major") || (D.major == "F# major") ||
                 (D.major == "C# major")) {
        D.note[i] = "A#";
      } else {
        D.note[i] = "A";
      }
    } else if ((D.sentence[i] == "b") || (D.sentence[i] == "B") ||
               (D.sentence[i] == "i") || (D.sentence[i] == "I") ||
               (D.sentence[i] == "p") || (D.sentence[i] == "P") ||
               (D.sentence[i] == "w") || (D.sentence[i] == "W")) {
      if (D.major == "F major" || (D.major == "Bb major") ||
          (D.major == "Eb major") || (D.major == "Ab major") ||
          (D.major == "Db major") || (D.major == "Gb major") ||
          (D.major == "Cb major")) {
        D.note[i] = "Bb";
      } else if (D.major == "C# major") {
        D.note[i] = "B#";
      } else {
        D.note[i] = "B";
      }
    } else if ((D.sentence[i] == "c") || (D.sentence[i] == "C") ||
               (D.sentence[i] == "j") || (D.sentence[i] == "J") ||
               (D.sentence[i] == "q") || (D.sentence[i] == "Q") ||
               (D.sentence[i] == "x") || (D.sentence[i] == "X")) {
      if ((D.major == "Cb major") || (D.major == "Gb major")) {
        D.note[i] = "Cb";
      } else if ((D.major == "D major") || (D.major == "A major") ||
                 (D.major == "E major") || (D.major == "B major") ||
                 (D.major == "F# major") || (D.major == "C# major")) {
        D.note[i] = "C#";
      } else {
        D.note[i] = "C";
      }
    } else if ((D.sentence[i] == "d") || (D.sentence[i] == "D") ||
               (D.sentence[i] == "k") || (D.sentence[i] == "K") ||
               (D.sentence[i] == "r") || (D.sentence[i] == "R") ||
               (D.sentence[i] == "y") || (D.sentence[i] == "Y")) {
      if ((D.major == "Ab major") || (D.major == "Db major") ||
          (D.major == "Gb major") || (D.major == "Cb major")) {
        D.note[i] = "Db";
      } else if ((D.major == "E major") || (D.major == "A major") ||
                 (D.major == "B major") || (D.major == "F# major") ||
                 (D.major == "C# major")) {
        D.note[i] = "D#";
      } else {
        D.note[i] = "D";
      }
    } else if ((D.sentence[i] == "e") || (D.sentence[i] == "E") ||
               (D.sentence[i] == "l") || (D.sentence[i] == "L") ||
               (D.sentence[i] == "s") || (D.sentence[i] == "S")) {
      if ((D.major == "Eb major") || (D.major == "Ab major") ||
          (D.major == "Db major") || (D.major == "Gb major") ||
          (D.major == "Cb major")) {
        D.note[i] = "Eb";
      } else if ((D.major == "E major") || (D.major == "B major") ||
                 (D.major == "F# major") || (D.major == "C# major")) {
        D.note[i] = "E#";
      } else {
        D.note[i] = "E";
      }
    } else if ((D.sentence[i] == "f") || (D.sentence[i] == "F") ||
               (D.sentence[i] == "m") || (D.sentence[i] == "M") ||
               (D.sentence[i] == "t") || (D.sentence[i] == "T")) {
      if (D.major == "Cb major") {
        D.note[i] = "Fb";
      } else if ((D.major == "G major") || (D.major == "A major") ||
                 (D.major == "E major") || (D.major == "B major") ||
                 (D.major == "F# major") || (D.major == "C# major")) {
        D.note[i] = "F#";
      } else {
        D.note[i] = "F";
      }
    }else if ((D.sentence[i] == "g") || (D.sentence[i] == "G") ||
               (D.sentence[i] == "n") || (D.sentence[i] == "N") ||
               (D.sentence[i] == "u") || (D.sentence[i] == "U")) {
        if ((D.major == "Db major") || (D.major == "Gb major") ||
            (D.major == "Cb major")) {
          D.note[i] = "Gb";
        } else if ((D.major == "A major") || (D.major == "E major") ||
                   (D.major == "B major") || (D.major == "F# major") ||
                   (D.major == "C# major")) {
          D.note[i] = "G#";
        } else {
          D.note[i] = "G";
        }
    } else { // if the letter is a space, it is a rest
          D.note[i] = "rest";
        }
      }
    }

    void display(Data P[], int p) {
      cout << "\nMusic notes in Piano:\n";
      for (int j = 0; j < p; j++) {
        for (int i = 0; i < P[j].length; i++) {
          cout << "Note: " << P[j].note[i]
               << " Length of Note: " << P[j].length_of_note[i] << endl;
        }
      }
    } 
