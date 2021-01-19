#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

int main()
{
    int length; //liczba bajtów w pliku
    short a;    //integer o długości 16 bitów
    char b;     //znak (character)
    char c;     //8 bitów wypełnienia (padding)
    int d;      //integer 32 bitowy (big endian)
    float e;    //32b liczba zmiennoprzecinkowa
    long f;     //pole bitowe o długości 64 bitów
    long g;     //7 bitowa liczba od bitu 11 zawarta w F

    // open file:
    ifstream file("sample_data.bin", ios::binary);
    if (file.is_open())
    {
        //reading length of file:
        file.seekg(0, ios::end);
        length = file.tellg();

        // read data as a block:
        file.seekg(0, ios::beg);

        // opens an existing csv file or creates a new file.
        fstream result;
        result.open("export.csv", ios::out | ios::trunc);

        //reading data, i is a 20 byte record
        for (int i = 0; i < length / 20; i++)
        {
            file.read((char *)&a, sizeof a);
            file.read((char *)&b, sizeof b);
            file.read((char *)&c, sizeof c);
            file.read((char *)&d, sizeof d);
            file.read((char *)&e, sizeof e);
            file.read((char *)&f, sizeof f);
            f >>= 10;

            //d little endian to big endian:
            int dBigEndian = ((d & 0xff000000) >> 24) | ((d & 0x00ff0000)) >> 8 | ((d & 0x0000ff00) << 8) | ((d & 0x000000ff) << 24);
            
            //writing data
            result
                << a << ", "; //a
            if (b == '\"')    //b
            {
                result << "\"" << b << b << "\", ";
            }
            else
            {
                result << "\"" << b << "\", ";
            }
            result << ", "               //c
                   << dBigEndian << ", " //d
                   << e << ", "          //e
                   << ", "               //f
                   << endl;
        }

        file.close();
        result.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    return 0;
}