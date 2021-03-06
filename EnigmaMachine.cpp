#include "EnigmaMachine.hpp"
#include <iostream>
//Rotor



Rotor::Rotor(){
  char assigement = 'a';
  for(int i = 0; i <= 26; i++){
    rotor.insert(std::pair<char, char>(assigement, assigement));
    assigement += 1;
    assigement = static_cast<char>(assigement);
  }
}

char Rotor::reflectMap(char character){
  for (std::multimap<char, char>::iterator Values = rotor.begin(); Values != rotor.end(); ++Values)
  {
    if(Values->second == character){
      return Values->first;
    }
  }
  return ')';
}

char Rotor::shift(char character, bool reflect){
  char newCharacter;
  if(reflect){
    newCharacter = reflectMap(character);
  } else {
    newCharacter = rotor.find(character)->second;
  }
  newCharacter = static_cast<char>(newCharacter);
  std::cout << "->" << newCharacter;
  rotate();
  return newCharacter;
}


void Rotor::rotate(){
  std::vector<char> values;
  for(std::map<char,char>::iterator rotorRef = rotor.begin(); rotorRef != rotor.end(); ++rotorRef) {
    values.push_back(rotorRef->second);
  }
  std::rotate(values.begin(), values.begin()+values.size()-1, values.end());//Rotate the vector right
  int iterator = 0;
  for(auto &value : rotor){
    value.second = values[iterator];
    iterator++;
  }
}



void Rotor::initRotor(int init){
  std::vector<char> values;
  for(std::map<char,char>::iterator rotorRef = rotor.begin(); rotorRef != rotor.end(); ++rotorRef) {
    values.push_back(rotorRef->second);
  }
  std::rotate(values.begin(), values.begin()+init, values.end());//Rotate the vector right
  int iterator = 0;
  for(auto &value : rotor){
    value.second = values[iterator];
    iterator++;
  }
}
//Enigma Machine
EnigmaMachine::EnigmaMachine(){

}

std::string EnigmaMachine::cipher(std::string text){
  unsigned long stringLen = text.length();
  int abreviatedStrLen = stringLen & INT_MAX;
  char c_str_text[abreviatedStrLen];
  strcpy(c_str_text, text.c_str());

  std::vector<char> v_newString;

  for (auto &character : c_str_text) {
    v_newString.push_back(r3.shift(r2.shift(r3.shift(character, false), false), false));
    std::cout << "\n";
  }
  
  std::string newString(v_newString.begin(), v_newString.end());
  return newString;
}

std::string EnigmaMachine::decipher(std::string text){
  unsigned long stringLen = text.length();
  int abreviatedStrLen = stringLen & INT_MAX;
  char c_str_text[abreviatedStrLen];
  strcpy(c_str_text, text.c_str());
  
  std::vector<char> v_newString;
  
  for (auto &character : c_str_text) {
    v_newString.push_back(r3.shift(r2.shift(r3.shift(character, true), true), true));
    std::cout << "\n";
  }
  
  std::string newString(v_newString.begin(), v_newString.end());
  return newString;
}
