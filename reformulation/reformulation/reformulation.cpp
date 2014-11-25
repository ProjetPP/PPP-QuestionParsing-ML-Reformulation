// reformulation.cpp : definit le point d'entr�e pour l'application console.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Dictionary.h"
#include "Functions.h"
#include <pthread.h>
#include <ctime>
#include "Transformator.h"
#include "Trainer.h"

using namespace std;


Dictionary dico;
Functions functions;
Transformator transformator(&functions,&dico,0.1f);
Trainer trainer(&dico,&functions,0.1f);

inline bool fileExists (const std::string& name) {
    ifstream f(name.c_str());
    if (f.good()) {
        f.close();
        return true;
    } else {
        f.close();
        return false;
    }   
}

bool init()
{
  if(!fileExists("dictionnary.txt"))
  {
    if(!dico.initializeFromClex("clex_lexicon.pl"))
      return false;
  }
  else
    dico.load("dictionnary.txt");
  if(fileExists("functions.txt"))
  {
    if(!functions.load("functions.txt"))
      return false;
  }
  return true;
}

void save()
{
  dico.save("dictionnary.txt");
  functions.save("functions.txt");
}

void setLearningprecision(float delta)
{
  transformator.setDelta(delta);
  trainer.setDelta(delta);
}

string reformulation(string input)
{
  return transformator.reformulation(input);
}

string testtag(string input)
{
  return transformator.testtaginput(input);
}



