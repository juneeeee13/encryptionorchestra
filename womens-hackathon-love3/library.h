#ifndef LIBRARY_H
#define LIBRARY_H
#include <iomanip>
#include <iostream>
#include <fstream>

using namespace std;


const int MAX= 900;
struct Data{
string sentence[MAX]; 
string firstletter;
string major;
int number_of_words=0;
int length;
string length_of_note[MAX];
string note[MAX];
int accidentals;
};


void collect_one(ifstream &fin, Data &D);
void collect_all(ifstream &fin, Data D[]);
char findmajor(ifstream &fin);
string findkey(Data &D);
int numberofaccidentals(Data &D, string keysignature, int numberofwordsinphrase);
string fullkeysignature(Data &D, string keysignature, int accidentals);
void convert_partA(Data &D);
void convert_partB(Data &D);
void display(Data P[], int p);

#endif