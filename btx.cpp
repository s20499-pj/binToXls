#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  cout << endl;
  int length;
  char *data;

  // open file:
  ifstream file("sample_data.bin", ios::binary);
  if (file.is_open())
  {
    file.seekg(0, ios::end);
    length = file.tellg();
    // allocate memory:
    data = new char[length];
    // read data as a block:
    file.seekg(0, ios::beg);
    file.read(data, length);
    file.close();
  }
  else
  {
    cout << "Unable to open file";
  }
  /*
  short a[length / 20]; //16 bit
  char b[length / 20];           //8bit
  bitset<8> c;                   //8bit
  long d[length / 20];           //32
  float e[length / 20];          //32
  long long f:64;                //64
  int g[length / 20];            //od 11 do 17 bitu f[]*/

  struct Record
  {
    short a : 16;     //16
    char b : 8;       //8
    char c : 8;       //8
    long d : 32;      //32
    long e : 32;      //32
    long long f : 64; //64
                      //int g[length / 20]; //od 11 do 17 bitu f[]
  };

  Record record[length / 20];

  for (int i = 0; i < length / 20; i++) //i is a 20 byte record
  {
    record[i] = {
        data[i * 20],
        data[i * 20 + 2],
        data[i * 20 + 3],
        data[i * 20 + 4],
        data[i * 20 + 8],
        data[i * 20 + 12]};
  }

  delete[] data;
  return 0;
}