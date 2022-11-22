#include <iostream>
#include <vector>
#include <string>
/*#include <ctype.h>
#include <sstream>
#include <iterator>*/

using namespace std;

vector<string> seperate_string(string input)
{
    string delim = " ";
    size_t pos = 0;
    vector<string> sub_input{};
    string s;
    while ((pos = input.find(delim)) != string::npos)
    {
        s = input.substr(0, pos);
        input.erase(0, pos + delim.length());
        sub_input.push_back(s);
    }
    sub_input.push_back(input);
    return sub_input;
}

vector<double> nums_check(vector<string> x_vector)
{
    vector<double> num_vector{};
    for (auto x : x_vector)
    {
        if (isdigit(x[0]) && x.length() == 1)
        {
            double num = stof(x);
            num_vector.push_back(num);
            continue;
        }
        if (!isdigit(x[0]))
        {
            continue;
        }
        else if (x[0] == '0' && x[1] != '.')
        {
            continue;
        }
        bool dot_flag = false;
        for (int i = 0; i < x.length(); i++)
        {
            if (isdigit(x[i]) && (i == x.length() - 1))
            {
                double num = stod(x);
                num_vector.push_back(num);
            }
            else if (isdigit(x[i]))
            {
                continue;
            }
            else if (x[i] == '.')
            {
                if (dot_flag == false)
                {
                    dot_flag = true;
                    continue;
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }
    return num_vector;
}

bool vectors_check(vector<double> x, vector<double> y)
{
    for (auto a : x)
    {
        cout << a << endl;
    }
    for (auto b : y)
    {
        cout << b << endl;
    }
    if (x.size() == y.size() && x.size() != 0)
    {
        cout << "input is valid";
        return true;
    }
    else
    {
        cout << "input is not valid, exiting progrem";
        return false;
    }
}
void get_input()
{
    string x, y;
    cout << "Please enter the first vector: ";
    getline(cin, x);
    cout << "Please enter the second vector: ";
    getline(cin, y);
    vector<string> str_vec1 = seperate_string(x);
    vector<string> str_vec2 = seperate_string(y);
    vector<double> num_vec1 = nums_check(str_vec1);
    vector<double> num_vec2 = nums_check(str_vec2);
    if (vectors_check(num_vec1, num_vec2))
    {
        cout << "yay";
    }
    else
    {
        return;
    }
}

int main()
{
    get_input();

    return 1;
}