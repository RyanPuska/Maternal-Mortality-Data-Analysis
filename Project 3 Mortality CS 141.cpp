/*Maternal Mortality II | Ryan Puska | 11/6
This program is meant to take the given data files and filter
the data in different ways to display results. There are 4 main functions
for each subtask: Displaying data in 2D array, analyzing a single factor and
sorting results in ascending or descending, displaying how many pregnancy
and non pregnancy related deaths there are and displaying the top categories
that have the most deaths, finding conditions that share 3 different factors
with 3 specific values and displaying the most frequent one.*/
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


//integer insertion sort function in ascending order
vector <int> ascendSort(vector <int> numbers)
{
    for (unsigned int i = 1; i < numbers.size(); i++)
    {
        unsigned int j = i;
        while (j > 0 && numbers[j] < numbers[j - 1])
        {
            int temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            j--;
        }
    }
    return numbers;
}

//character insertion sort function in ascending order
vector <char> ascendSort(vector <char> numbers)
{
    for (unsigned int i = 1; i < numbers.size(); i++)
    {
        unsigned int j = i;
        while (j > 0 && numbers[j] < numbers[j - 1])
        {
            int temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            j--;
        }
    }
    return numbers;

}


//integer insertion sort function in descending order
vector <int> descendSort(vector <int> numbers)
{
    for (unsigned int i = 1; i < numbers.size(); i++)
    {
        unsigned int j = i;
        while (j > 0 && numbers[j] > numbers[j - 1])
        {
            int temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            j--;
        }
    }
    return numbers;
}

//character insertion sort function in descending order
vector <char> descendSort(vector <char> numbers)
{
    for (unsigned int i = 1; i < numbers.size(); i++)
    {
        unsigned int j = i;
        while (j > 0 && numbers[j] > numbers[j - 1])
        {
            int temp = numbers[j];
            numbers[j] = numbers[j - 1];
            numbers[j - 1] = temp;
            j--;
        }
    }
    return numbers;
}

//function for the single factor, sorts and diplays number of 
//records for each category
void singleFactor(vector<vector<string>>& data)
{
    string factor;
    cout << "Enter the factor name: ";
    cin >> factor;
    cout << endl;


    unsigned int col;
    unsigned int i;
    unsigned int j;
    string value;
    int errorCheck = 0;

    //finds the factor inputted by the user
    for (i = 0; i < data[0].size(); i++)
    {
        if (data[0][i] == factor)
        {
            col = i;
            errorCheck++;
            break;
        }
    }

    //makes sure the factor exists
    if (errorCheck == 0)
    {
        cout << "Factor does not exist. ";
        return;
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
            if (value.empty())
            {
                continue;
            }

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

    //converting vector to integers to sort
    bool toInt = true;
    vector <int> intVals;
    for (i = 0; i < nums.size(); i++)
    {
        string newString = nums[i];
        bool isNum = true;
        //make sure the vector contains digits
        for (j = 0; j < newString.length(); j++)
        {
            if (!isdigit(newString[j]))
            {
                isNum = false;
                break;
            }
        }
        //if it does, convert and put into new vector
        if (isNum)
        {
            intVals.push_back(stoi(newString));
        }
        else
        {
            toInt = false;
            break;
        }
    }

    //prompt the user for the sorting
    int selection;
    cout << "How do you want to view the results?" << endl;
    cout << "1) By category" << endl;
    cout << "2) By record count" << endl;
    cout << "Your choice: ";
    cin >> selection;

    int sort;
    cout << "What sort order do you want to display?" << endl;
    cout << "1) Ascending" << endl;
    cout << "2) Descending" << endl;
    cout << "Your choice: ";
    cin >> sort;

    //vector to make sure duplicate counts aren't outputted under
    //the same category
    vector<bool>duplicate(count.size(), false);
    //if the vector has integers
    if (toInt)
    {
        vector <int> sortedIntData;
        vector <int> sortedCount = count;

        //based on user input
        if (selection == 1 && sort == 1)
        {
            //sort the vector
            sortedIntData = ascendSort(intVals);
            //realign the values of the vectors together
            for (i = 0; i < sortedIntData.size(); i++)
            {
                for (j = 0; j < intVals.size(); j++)
                {
                    if (intVals[j] == sortedIntData[i] && !duplicate[j])
                    {
                        sortedCount[i] = count[j];
                        duplicate[j] = true;
                        break;
                    }
                }
            }
        }
        //repeat for all cases
        else if (selection == 2 && sort == 1)
        {
            //repeat for all cases
            sortedCount = ascendSort(count);
            //repeat for all cases
            for (i = 0; i < sortedCount.size(); i++)
            {
                for (j = 0; j < count.size(); j++)
                {
                    if (count[j] == sortedCount[i] && !duplicate[j])
                    {
                        sortedIntData.push_back(intVals[j]);
                        duplicate[j] = true;
                        break;
                    }
                }
            }
        }
        else if (selection == 1 && sort == 2)
        {
            sortedIntData = descendSort(intVals);
            for (i = 0; i < sortedIntData.size(); i++)
            {
                for (j = 0; j < intVals.size(); j++)
                {
                    if (intVals[j] == sortedIntData[i] && !duplicate[j])
                    {
                        sortedCount[i] = count[j];
                        duplicate[j] = true;
                        break;
                    }
                }
            }
        }
        else if (selection == 2 && sort == 2)
        {
            sortedCount = descendSort(count);
            for (i = 0; i < sortedCount.size(); i++)
            {
                for (j = 0; j < count.size(); j++)
                {
                    if (count[j] == sortedCount[i] && !duplicate[j])
                    {
                        sortedIntData.push_back(intVals[j]);
                        duplicate[j] = true;
                        break;
                    }
                }
            }
        }
        //keep track of total number of occurences to calculate ratio
        int total = 0;
        for (i = 0; i < count.size(); i++)
        {
            total += count[i];
        }

        //output filtered and sorted data
        cout << "Single Factor Analysis: " << factor << endl;
        cout << "Category" << setw(9) << "Count" << setw(12) << "Ratio(%)" << endl;
        for (i = 0; i < sortedIntData.size(); i++)
        {
            double ratio = (static_cast<double>(sortedCount[i]) / total) * 100;
            cout << sortedIntData[i] << setw(12) << sortedCount[i] << setw(12) << fixed << setprecision(1) << ratio << endl;
        }
    }
    //else if the vector does not have integers
    else
    {
        //convert vector to character to sort
        bool toChar = true;
        vector <char> charVals;
        vector <char> sortedCharData;

        for (i = 0; i < nums.size(); i++)
        {
            if (nums[i].length() == 1)
            {
                charVals.push_back(nums[i][0]);
            }
            else
            {
                toChar = false;
                break;
            }
        }
        //if converted to characters
        if (toChar)
        {

            vector <char> sortedCharData;
            vector <int> sortedCount = count;
            //based on user input
            if (selection == 1 && sort == 1)
            {
                //sort the vector
                sortedCharData = ascendSort(charVals);
                //realign the values of the vectors together
                for (i = 0; i < sortedCharData.size(); i++)
                {
                    for (j = 0; j < charVals.size(); j++)
                    {
                        if (charVals[j] == sortedCharData[i])
                        {
                            sortedCount[i] = count[j];
                            break;
                        }
                    }
                }
            }
            //repeat for all cases
            else if (selection == 2 && sort == 1)
            {
                //repeat for all cases
                sortedCount = ascendSort(count);
                //repeat for all cases
                for (i = 0; i < sortedCount.size(); i++)
                {
                    for (j = 0; j < count.size(); j++)
                    {
                        if (count[j] == sortedCount[i])
                        {
                            sortedCharData.push_back(charVals[j]);
                            break;
                        }
                    }
                }
            }
            else if (selection == 1 && sort == 2)
            {
                sortedCharData = descendSort(charVals);
                for (i = 0; i < sortedCharData.size(); i++)
                {
                    for (j = 0; j < charVals.size(); j++)
                    {
                        if (charVals[j] == sortedCharData[i])
                        {
                            sortedCount[i] = count[j];
                            break;
                        }
                    }
                }
            }
            else if (selection == 2 && sort == 2)
            {
                sortedCount = descendSort(count);
                for (i = 0; i < sortedCount.size(); i++)
                {
                    for (j = 0; j < count.size(); j++)
                    {
                        if (count[j] == sortedCount[i] && !duplicate[j])
                        {
                            sortedCharData.push_back(charVals[j]);
                            duplicate[j] = true;
                            break;
                        }
                    }
                }
            }

            //keep track of total number of occurences to calculate ratio
            int total = 0;
            for (i = 0; i < count.size(); i++)
            {
                total += count[i];
            }
            //output filtered and sorted data
            cout << "Single Factor Analysis: " << factor << endl;
            cout << "Category" << setw(9) << "Count" << setw(12) << "Ratio(%)" << endl;
            for (i = 0; i < sortedCharData.size(); i++)
            {
                double ratio = (static_cast<double>(sortedCount[i]) / total) * 100;
                cout << sortedCharData[i] << setw(12) << sortedCount[i] << setw(12) << fixed << setprecision(1) << ratio << endl;
            }
        }
    }

}

//function to count pregnancy related deaths and top categories
void primaryOverview(vector<vector<string>>& data)
{
    int choice;
    cout << "Primary Condition Menu:" << endl << "1) Display Overview";
    cout << endl << "2) Display Top-N Categories" << endl << "Your choice: ";
    cin >> choice;

    unsigned int col;
    unsigned int i;
    string value;

    //if user chooses overview
    if (choice == 1)
    {
        //finds the factor inputted by the user
        for (i = 0; i < data[0].size(); i++)
        {
            if (data[0][i] == "condition_1")
            {
                col = i;
                break;
            }
        }

        vector <string> nums{ "O","X" };
        vector <int> count = { 0,0 };

        //loops through rows
        for (i = 1; i < data.size(); i++)
        {
            //checks if the column exists
            if (col < data[i].size())
            {
                //set value equal to that location
                value = data[i][col];
                if (value.empty())
                {
                    continue;
                }
                else
                    //based on first letter, increment either position in count
                {
                    if (value[0] == 'O')
                    {
                        count[0]++;
                    }
                    else
                    {
                        count[1]++;
                    }
                }
            }
        }
        //to keep track of total occurences
        int total = 0;
        for (i = 0; i < count.size(); i++)
        {
            total += count[i];
        }

        vector<string> names = { "Pregnancy-related", "Non-pregnancy-related" };

        //output the data
        cout << "Condition_1 Type" << setw(13) << "Count" << setw(12) << "Ratio(%)" << endl;
        for (i = 0; i < nums.size(); i++)
        {
            double ratio = (static_cast<double>(count[i]) / total) * 100;
            cout << names[i] << setw(10) << count[i] << setw(10) << fixed << setprecision(1) << ratio << endl;
        }
    }

    //if user chooses top categories
    if (choice == 2)
    {
        unsigned int category;
        cout << "Enter number of top categories: ";
        cin >> category;
        unsigned int col;
        unsigned int i;
        unsigned int j;
        string value;

        //finds the factor inputted by the user
        for (i = 0; i < data[0].size(); i++)
        {
            if (data[0][i] == "condition_1")
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
                string index = value;
                //erase any value after 3 positions
                if (index.length() > 3)
                {
                    index.erase(3, 1);
                }
                if (value.empty())
                {
                    continue;
                }

                bool isTrue = false;
                for (j = 0; j < nums.size(); j++)
                {

                    //if value is in nums array
                    if (nums[j] == index)
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
                    nums.push_back(index);
                    count.push_back(1);
                }
            }
        }
        vector<int> sortedCount = count;
        vector<string>sortedData;
        vector<bool>duplicate(count.size(), false);

        //sort vector
        sortedCount = descendSort(count);
        //realign vectors for output
        for (i = 0; i < sortedCount.size(); i++)
        {
            for (j = 0; j < count.size(); j++)
            {
                if (count[j] == sortedCount[i] && !duplicate[j])
                {
                    sortedData.push_back(nums[j]);
                    duplicate[j] = true;
                    break;
                }
            }
        }

        //count occurences
        int total = 0;
        for (i = 0; i < count.size(); i++)
        {
            total += count[i];
        }

        //output the data
        unsigned int min = 0;
        cout << "Category" << setw(9) << "Count" << setw(12) << "Ratio(%)" << endl;
        for (unsigned int k = 0; k < category; k++)
        {
            //make sure to not output more data than exists
            if (category > sortedData.size() && min == sortedData.size())
            {
                break;
            }
            double ratio = (static_cast<double>(sortedCount[k]) / total) * 100;
            cout << sortedData[k] << setw(12) << sortedCount[k] << setw(12) << fixed << setprecision(1) << ratio << endl;
            min++;

        }
    }
}

//function used to output the data for multiFactor function
void outputMultiFactor(const vector<string>& names, const vector<int>& count, const int& total)
{
    int max = 0;
    vector<int>mostCounted;
    //count only the most frequent condition
    //if there is a tie, count them too
    for (unsigned int i = 0; i < count.size(); i++)
    {
        if (count[i] > max)
        {
            max = count[i];
            mostCounted.clear();
            mostCounted.push_back(i);
        }
        else if (count[i] == max)
        {
            mostCounted.push_back(i);
        }
    }
    //output data
    cout << "Most frequent condition(s) in filtered data:\n";
    for (unsigned int i = 0; i < mostCounted.size(); i++)
    {
        cout << names[mostCounted[i]] << " occurs in " << count[mostCounted[i]] << " of " << total << " matching records.\n";

    }
}

//function to display occurences of all 3 factors and values
void multiFactor(vector<vector<string>>& data)
{
    unsigned int i;
    unsigned int j;
    unsigned int col1, col2, col3;
    unsigned int condition;
    string factor1, factor2, factor3;
    string val1, val2, val3;
    //prompt user
    cout << "Enter first factor name: ";
    cin >> factor1;
    cout << "Value to search for: ";
    cin >> val1;
    cout << "Enter second factor name: ";
    cin >> factor2;
    cout << "Value to search for: ";
    cin >> val2;
    cout << "Enter third factor name: ";
    cin >> factor3;
    cout << "Value to search for: ";
    cin >> val3;

    //find position of factors and condition
    int exists = 0;
    for (i = 0; i < data[0].size(); i++)
    {
        if (data[0][i] == factor1)
        {
            col1 = i;
            exists++;
        }
        if (data[0][i] == factor2)
        {
            col2 = i;
            exists++;
        }
        if (data[0][i] == factor3)
        {
            col3 = i;
            exists++;
        }
        if (data[0][i] == "condition_1")
        {
            condition = i;
        }
    }

    //if not all factors exists, return
    if (exists != 3)
    {
        cout << "Factor not found. ";
        return;
    }
    vector<vector<string>> multiData;
    vector <string> names;
    vector <int> count;

    //loop through data vector
    for (i = 1; i < data.size(); i++)
    {
        //checks if column exists
        if (col1 < data[i].size() && col2 < data[i].size() && col3 < data[i].size())
        {
            //add row to vector if data is found
            if (data[i][col1] == val1 && data[i][col2] == val2 && data[i][col3] == val3)
            {
                multiData.push_back(data[i]);
            }
        }
    }
    //if vector is empty output that there are no records and return
    if (multiData.empty())
    {
        cout << "No records match this combination, please try again." << endl;
        return;
    }

    int total = multiData.size();

    string conditionVal;
    string filterCondition;
    //loop through records
    for (i = 0; i < multiData.size(); i++)
    {
        if (condition < multiData[i].size())
        {
            conditionVal = multiData[i][condition];
            //if the length of the condition is greater than or equal to 3,
            //keep first three characters
            if (conditionVal.length() >= 3)
            {
                filterCondition = conditionVal.substr(0, 3);
            }
            else
            {
                filterCondition = conditionVal;
            }

            bool isTrue = false;
            for (j = 0; j < names.size(); j++)
            {
                //if condition is in nums array increment count
                if (names[j] == filterCondition)
                {
                    count[j]++;
                    isTrue = true;
                    break;
                }
            }
            //else push back condition and count
            if (isTrue == false)
            {
                names.push_back(filterCondition);
                count.push_back(1);
            }
        }
    }
    //call outputting function and pass vectors and total
    outputMultiFactor(names, count, total);
}

int main()
{
    bool again = true;

    string filename;

    // The menu output. Don't modify this, so that it outputs exactly as expected
    cout << "Project 2: Maternal Mortality II" << endl;
    cout << "Enter a file name you want to use: ";
    cin >> filename;

    vector<vector<string>> data;

    //error handle
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

    //continuously prompt user until they choose exit
    while (again)
    {
        cout << "Which option would you like?" << endl;
        cout << "  1. Display data" << endl;
        cout << "  2. Single Factor Analysis" << endl;
        cout << "  3. Primary Condition Overview" << endl;
        cout << "  4. Multi-factor Pattern Exploration" << endl;
        cout << "  5. Exit the Program" << endl;
        cout << "Your choice: ";

        int choices;
        cin >> choices;

        //case switch for each choice by the user
        switch (choices)
        {
        case 1:
            displayData(data);
            break;
        case 2:
            singleFactor(data);
            break;
        case 3:
            primaryOverview(data);
            break;
        case 4:
            multiFactor(data);
            break;
        case 5:
            again = false;
            cout << "Program exited.";
            return 0;
        default:
            cout << "Invalid choice entered. ";
            break;
        }
    }
}