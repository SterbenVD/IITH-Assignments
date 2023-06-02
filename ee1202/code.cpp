// KMap digital circuits
// Team Members -
// CS21BTECH11007 Vedant
// CS21BTECH11051 Rajiv
// CS21BTECH11061 Vishal

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
// #include <memory>

#define Empty 0
#define Filled 1
#define Taken 2

using namespace std;

char literal_upper(int i)
{
    return 'A' + i;
}

char literal_lower(int i)
{
    return 'a' + i;
}

class KMap
{
public:
    vector<int> inputs, kmap;
    int variables;
    int type; // 0 for minterms, 1 for maxterms
    string minimizedExpression;
    char config;
    int mode; // 1 for increasing and -1 for decreasing

    // Merging new methods - methods for solving the KMap
    int simplify();
    void minimizeExpression();
    int printTerm(int index, int grpMask);
    bool checkGroup(int index, int grpMask);
    bool reserveGroup(int index, int grpMask);
    int makeGroups(int index, int grpDim);

    void input(int type)
    {
        int in = -1;
        if (type == 0)
            cout << "Enter the minterms and enter -1 to finish: ";
        else
            cout << "Enter the maxterms and enter -1 to finish: ";

        /*
        do
        {
            if (in != -1)
                inputs.push_back(in);
            cin >> in;
        } while (in != -1);
        */
        while (1)
        {
            cin >> in;
            if (in < -1 || in >= 1 << variables)
            {
                cout << "Invalid term ignored:" << in << endl;
            }
            else if (in == -1)
            {
                break;
            }
            else
            {
                inputs.push_back(in);
            }
        }
        sort(inputs.begin(), inputs.end());
    }

    void NumberOfVariables()
    {
        cout << "Enter the number of variables: ";
        cin >> variables;
        if (variables < 2 || variables > 4)
        {
            variables = 0;
        }
    }

    void choice()
    {
        cout << "Choose input type ( 0 for Minterm, 1 for Maxterm): ";
        cin >> type;
        if (type != 0)
        {
            type = 1;
        }
        config = (type == 0) ? '+' : 'x';
    }

    KMap()
    {
        mode = 1;
        choice();
        NumberOfVariables();

        if (variables != 0)
        {
            input(type);
        }

        for (int i = 0; i < 1 << variables; i++)
            kmap.push_back(Empty);
        for (const int &i : inputs)
            kmap[i] = Filled;
    }
};

bool KMap::checkGroup(int index, int grpMask)
{
    int loc;
    for (int offset = 1; offset < kmap.size(); offset++)
    {
        loc = offset & grpMask; // only takes a non-zero offset allowed within in the group
        if (loc != 0)           // for now a bit inefficient because of repetitions
        {
            if ((mode == 1 && kmap[index ^ loc] != Filled) || (mode == -1 && kmap[index ^ loc] == Empty)) // in mode == -1 ie leftovers overlapping groups are allowed
                return false;
        }
    }
    return true;
}

bool KMap::reserveGroup(int index, int grpMask)
{
    int loc;
    for (int offset = 1; offset < kmap.size(); offset++)
    {
        loc = offset & grpMask; // only takes a non-zero offset allowed within in the group
        if (loc != 0)           // for now a bit inefficient because of repetitions
            kmap[index ^ loc] = Taken;
    }
    return true;
}

int KMap::printTerm(int index, int grpMask)
{
    string term;
    if (minimizedExpression.length() != 0)
        minimizedExpression.append(1, config);
    if (config == 'x')
        term.append("(");

    for (int literal = variables - 1; literal >= 0; literal--)
    {
        if ((grpMask & 1) == 0)
        {

            if (config == 'x' && term.length() != 1)
                term.append(1, '+');
            if ((index & 1) == 0)
            {
                if (type == 0)
                    term.append(1, literal_lower(literal));
                else
                    term.append(1, literal_upper(literal));
            }
            else
            {
                if (type == 0)
                    term.append(1, literal_upper(literal));
                else
                    term.append(1, literal_lower(literal));
            }
        }
        grpMask = grpMask >> 1;
        index = index >> 1;
    }

    if (config == 'x')
        term.append(")");
    if (config == '+' || term.compare("()"))
        minimizedExpression.append(term);
    return 0;
}

// grpDim is 1 for group of 2, 2 for group of 4, 3 for group of 8 etc
int KMap::makeGroups(int index, int grpDim)
{
    int maskSize;
    int digitChecker;
    int savedGrpMask;
    int counter = 0;

    // grpMask will have bits 0 for literals that do not change in a group
    // bits are 1 for literals that are present in both complemented and uncomplemented form
    for (int grpMask = 0; grpMask < kmap.size(); grpMask++)
    {
        maskSize = 0;
        digitChecker = grpMask;
        for (int pos = 0; pos < variables; pos++)
        {
            if ((digitChecker & 1) == 1)
                maskSize++;
            digitChecker = digitChecker >> 1;
        }

        // group mask is of valid size
        if (maskSize == grpDim)
        {
            if (checkGroup(index, grpMask) == true)
            {
                savedGrpMask = grpMask;
                counter++;
            }
        }
    }

    // Prime Implicant
    if (counter == 0 && grpDim == 1 && mode == -1)
    {
        printTerm(index, 0);
        kmap[index] = Taken;
        return 1;
    }

    // If unique group exists in increasing mode, or else all groups in decreasing mode
    if ((counter == 1) || (mode == -1 && counter >= 1))
    {
        printTerm(index, savedGrpMask);    // Take index, remove the eliminated vars the 1s in savedgrp
        reserveGroup(index, savedGrpMask); // Traverse grp and set to Taken
        kmap[index] = Taken;
    }
    return 0;
}

int KMap::simplify()
{
    if (variables == 0)
    {
        cout << "Number of variables can only be from 2 to 4." << endl;
        return 1;
    }
    // Goes from small grp to big, then goes from big grp to small
    for (int grpDim = 1; grpDim > 0 && grpDim <= variables; grpDim += mode)
    {
        for (int i = 0; i < kmap.size(); i++)
        {
            if (kmap[i] == Filled)
                makeGroups(i, grpDim);
        }
        if (grpDim == variables)
            mode = -1; // Change to decreasing mode
    }
    if (minimizedExpression.length() > 0)
        cout << minimizedExpression;
    else
    {
        if (inputs.size() > 0)
            cout << 1 - type; // Prints 1 if all MinTerm, 0 if all MaxTerm
        else
            cout << type; // Prints 0 if no MinTerm, 1 if no MaxTerm
    }
    cout << "\n";
    kmap.clear();
    inputs.clear();
    return 0;
}

int main()
{
    KMap *kmap = new KMap();
    kmap->simplify();
    delete kmap;
    return 0;
}
