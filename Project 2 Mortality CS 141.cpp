#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

//function that displays the data of the file
void displayData(vector<vector<string>>& data)
{
    //loops through rows
    for (unsigned int i = 0; i < data.size(); i++)
    {
        //loops through columns and displays
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

//function that prints each factor with it's corresponding data 
//from a particular row
void printRow(vector<vector<string>>& data)
{
    //asks user for row number
    unsigned int row;
    cout << "Enter a row number: ";
    cin >> row;
    cout << endl;

    vector <string> name = data[0];
    vector <string> nums = data[row];

    //outputs data
    for (unsigned int i = 0; i < nums.size(); i++)
    {
        cout << name[i] << ": " << nums[i] << endl;
    }
}

//function that prints out the amount of records for a particular factor
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

    //finds the factor inputted by the user
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

    //loops through rows
    for (i = 1; i < data.size(); i++)
    {
        //checks if the column exists
        if (col < data[i].size())
        {
            //set value equal to that location
            value = data[i][col];
            bool isTrue = false;
            for (j = 0; j < nums.size(); j++)
            {
                //if value is in nums array
                if (nums[j] == value)
                {
                    //increment record
                    count[j]++;
                    isTrue = true;
                    break;
                }
            }
            //if value isn't in nums array
            if (isTrue == false)
            {
                //add to vector
                nums.push_back(value);
                count.push_back(1);
            }
        }
    }

    //output data
    for (i = 0; i < nums.size(); i++)
    {
        cout << factor << " " << nums[i] << ": " << count[i] << " records\n";
    }
}

//function that prints out records for two particular factors that are together
void twoFactor(vector<vector<string>>& data)
{
    string factor;
    string factor2;
    cout << "Enter a factor name: ";
    cin >> factor;
    cout << "Enter a second factor name: ";
    cin >> factor2;

    unsigned int col = 0;
    unsigned int col2 = 0;
    unsigned int i;
    unsigned int j;
    unsigned int k;
    string value;
    string value2;

    //find both factors inputted by user
    for (i = 0; i < data[0].size(); i++)
    {
        if (data[0][i] == factor)
        {
            col = i;
        }
        if (data[0][i] == factor2)
        {
            col2 = i;
        }
    }

    vector <string> nums;
    vector <string> nums2;
    vector <vector<int>> count;

    //loop through rows
    for (i = 1; i < data.size(); i++)
    {
        //checks if column exists
        if (col < data[i].size() && col2 < data[i].size())
        {
            value = data[i][col];
            value2 = data[i][col2];
            int addValue1 = -1;
            int addValue2 = -1;

            for (j = 0; j < nums.size(); j++)
            {
                //if value is in nums array save the index
                if (nums[j] == value)
                {
                    addValue1 = j;
                    break;
                }
            }
            //if it's not in nums array, add value to nums array and
            //add another row to count array 
            if (addValue1 == -1)
            {
                nums.push_back(value);
                addValue1 = nums.size()-1;
                count.push_back(vector<int>());
            }

            for (k = 0; k < nums2.size(); k++)
            {
                //if value is in nums2 array, save the index
                if (nums2[k] == value2)
                {
                    addValue2 = k;
                    break;
                }
            }

            //if it's not in nums2 array, add value to nums2 array and
            //resize the count array
            if (addValue2 == -1)
            {
                nums2.push_back(value2);
                addValue2 = nums2.size()-1;
                for(unsigned int h = 0; h < count.size(); h++)
                {
                    count[h].resize(nums2.size(), 0);
                }
            }
            //if there are enough columns, resize count vector
            if(count[addValue1].size() < nums2.size())
            {
                count[addValue1].resize(nums2.size(),0);
            }
            //increment count vector
            count[addValue1][addValue2]++;
        }
    }

    //outputs the factors and number of records
    for (i = 0; i < nums.size(); i++)
    {
        cout << factor << " " << nums[i] << ": " << endl;
        for(j = 0; j < nums2.size(); j++)
        {
            cout << factor2 << " " << nums2[j] << ": " << count[i][j] << " records" << endl;
        }
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
        //while loop reads in lines of file
        while (getline(inFile, line))
        {
            string value;
            vector<string> vectorTwo;
            stringstream ss(line);
            //puts values in to vector
            while (getline(ss, value, ','))
            {
                vectorTwo.push_back(value);
            }
            data.push_back(vectorTwo);
        }
        inFile.close();
    }

    //select choices
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
