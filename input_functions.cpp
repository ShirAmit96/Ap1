#include <iostream>
#include <vector>
#include <string>
/*#include <ctype.h>
#include <sstream>
#include <iterator>*/

using namespace std;

void get_input()
{
    string x, y;
    vector<double> vec_x{};
    vector<double> vec_y{};
    cout << "Please enter the first vector: ";
    getline(cin, x);
    cout << "Please enter the second vector: ";
    getline(cin, y);
    vector<string> x_vector{};
    string delim = " ";
    size_t pos = 0;
    string s;

    while ((pos = x.find(delim)) != string::npos)
    {
        s = x.substr(0, pos);
        x.erase(0, pos + delim.length());
        x_vector.push_back(s);
    }
    x_vector.push_back(x);
    for (auto x : x_vector)
    {
        cout << x << endl;
    }
    vector<float> num_vector{};
    for (auto x : x_vector)
    {
        if (!isdigit(x[0]))
        {
            continue;
        }
        else if (x[0] == '0' && x[1] != '.')
        {
            continue;
        }
        bool dot_flag = false;
        for (int i = 1; i < x.length(); i++)
        {
            if (isdigit(x[i]) && (i == x.length() - 1))
            {
                float num = stof(x);
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
    for (auto a : num_vector)
    {
        cout << a << endl;
    }
}

int main()
{
    get_input();
}