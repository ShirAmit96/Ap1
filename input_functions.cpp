
#include "header.h"
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
    vector<double> empty_vector{};
    for (auto x : x_vector)
    {
        if (isdigit(x[0]) && x.length() == 1)
        {
            double num = stof(x);
            num_vector.push_back(num);
            continue;
        }
        else if (x[0] == '0' && x[1] != '.')
        {
            return empty_vector;
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
            else if (x[0] == '-' && x.length() > 1)
            {
                if (x[1] == '-')
                {
                    return empty_vector;
                }
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
                    return empty_vector;
                }
            }
            else
            {
                return empty_vector;
            }
        }
    }
    return num_vector;
}

bool vectors_check(vector<double> x, vector<double> y)
{
    if (x.size() == y.size() && x.size() != 0)
    {
        return true;
    }
    else
    {
        cout << "Input is not valid, exiting program" << endl;
        return false;
    }
}
vector<double> get_input()
{
    string x;
    cout << "Please enter vector: ";
    getline(cin, x);
    vector<string> str_vec1 = seperate_string(x);
    vector<double> num_vec1 = nums_check(str_vec1);
    return num_vec1;
}