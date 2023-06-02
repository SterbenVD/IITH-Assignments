#include <iostream>
#include <fstream>
#include <cstdlib>

#define FILE_NAME "output.txt"
using namespace std;

int main()
{
    try
    {
        system("./tas");
        system("./cas");
        system("./casb");
        ofstream output(FILE_NAME);
        ifstream tas("./tas.txt");
        ifstream cas("./cas.txt");
        ifstream casb("./casb.txt");
        string line;
        output << "[TAS OUTPUT]\n";
        while (getline(tas, line))
            output << line << "\n";

        output
            << "\n\n[CAS OUTPUT]\n";
        while (getline(cas, line))
            output << line << "\n";

        output << "\n\n[CAS-BOUNDED OUTPUT]\n";
        while (getline(casb, line))
            output << line << "\n";

        tas.close();
        cas.close();
        casb.close();
        remove("./tas.txt");
        remove("./cas.txt");
        remove("./casb.txt");
        output.close();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}