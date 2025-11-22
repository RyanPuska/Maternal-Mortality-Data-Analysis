#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

void displayData(vector<vector<string>>& data)
{
    for (unsigned int i = 0; i < data.size(); i++)
    {
        for (unsigned int j = 0; j < data[i].size(); j++)
        {
            cout << data[i][j];
            if (j < data[i].size() - 1)
            {
                cout << ",";
            }
        }
        cout << endl;
    }
}

void printRow(vector<vector<string>>& data)
{
    unsigned int row;
    cout << "Enter a row number: ";
    cin >> row;
    cout << endl;

    vector <string> name = data[0];
    vector <string> nums = data[row];

    for (unsigned int i = 0; i < nums.size(); i++)
    {
        cout << name[i] << ": " << nums[i] << endl;
    }
}

void singleFactor(vector<vector<string>>& data)
{
    string factor;
    cout << "Enter a factor name: ";
    cin >> factor;
    cout << endl;

    unsigned int col;
    unsigned int i;
    unsigned int j;
    string value;

    for (i = 0; i < data[0].size(); i++)
    {
        if (data[0][i] == factor)
        {
            col = i;
            break;
        }
    }

    vector <string> nums;
    vector <int> count;

    for (i = 1; i < data.size(); i++)
    {
        if (col < data[i].size())
        {
            value = data[i][col];
            bool isTrue = false;
            for (j = 0; j < nums.size(); j++)
            {
                if (nums[j] == value)
                {
                    count[j]++;
                    isTrue = true;
                    break;
                }
            }
            if (isTrue == false)
            {
                nums.push_back(value);
                count.push_back(1);
            }
        }
    }

    for (i = 0; i < nums.size(); i++)
    {
        cout << factor << " " << nums[i] << ": " << count[i] << " records\n";
    }
}

void twoFactor(vector<vector<string>>& data)
{
    string factor;
    string factor2;
    cout << "Enter a factor name: ";
    cin >> factor;
    cout << "Enter a second factor name: ";
    cin >> factor2;

    unsigned int col;
    unsigned int col2;
    unsigned int i;
    unsigned int j;
    string value;

    for (i = 0; i < data[0].size(); i++)
    {
        if (data[0][i] == factor)
        {
            col = i;
            break;
        }
        else if (data[0][i] == factor2)
        {
            col2 = i;
        }
    }

    vector <string> nums;
    vector <string> nums2;
    vector <int> count;
    vector <int> count2;

    for (i = 1; i < data.size(); i++)
    {
        if (col < data[i].size())
        {
            value = data[i][col];
            bool isTrue = false;
            for (j = 0; j < nums.size(); j++)
            {
                if (nums[j] == value)
                {
                    count[j]++;
                    isTrue = true;
                    break;
                }
            }
            if (isTrue == false)
            {
                nums.push_back(value);
                count.push_back(1);
            }
        }
    }

    for (i = 0; i < nums.size(); i++)
    {
        cout << factor << " " << nums[i] << ": " << count[i] << " records\n";
        //for loop for second factor
        cout << setfill('=') << setw(30) << "=" << endl;
    }
}



int main()
{
    string filename;

    // The menu output. Don't modify this, so that it outputs exactly as expected
    cout << "Project 1: Understanding Maternal Mortality" << endl;
    cout << "Enter a file name you want to use: ";
    cin >> filename;
    cout << "Which option would you like?" << endl;
    cout << "  1. Display data" << endl;
    cout << "  2. Print a selected row" << endl;
    cout << "  3. Single factor analysis" << endl;
    cout << "  4. Two factor analysis" << endl;
    cout << "Your choice: ";

    int choices;
    cin >> choices;

    vector<vector<string>> data;

    ifstream inFile(filename);
    if (!inFile)
    {
        cout << "Error: Cannot open file!" << endl;
        return 1;
    }
    else
    {
        string line;

        while (getline(inFile, line))
        {
            string value;
            vector<string> vectorTwo;
            stringstream ss(line);
            while (getline(ss, value, ','))
            {
                vectorTwo.push_back(value);
            }
            data.push_back(vectorTwo);
        }
        inFile.close();
    }

    if (choices == 1)
    {
        displayData(data);
    }
    else if (choices == 2)
    {
        printRow(data);
    }
    else if (choices == 3)
    {
        singleFactor(data);
    }
    else if (choices == 4)
    {
        twoFactor(data);
    }
    else
    {
        cout << "No valid choice entered. ";
    }
}