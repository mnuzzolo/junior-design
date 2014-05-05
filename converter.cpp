// this file was made to attempt to convert WAV fieles into a readable array for the arduino

#include <list>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int main() {
  list <int> all_values;

  int value = 0;
  while(value != -1) {
    cin >> std::hex >> value;
  	
    if(value == -1)
  	 break;

  	all_values.push_back(value/64);

  }
  
  ofstream myfile;
  myfile.open("wav_arr.txt");

  myfile << "{ ";

  for(list<int>::iterator it = all_values.begin(); it != all_values.end(); it++) {
  	myfile << *it << ", ";
  }

  myfile << "0 }";
  
  myfile.close();
}
