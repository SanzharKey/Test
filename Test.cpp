
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string>
#include <limits>

using namespace std;

template <class Iterator, class Element>
bool contains(Iterator first, Iterator last, const Element& val)
{
    return find(first, last, val) != last;
}

string to_lower(string);

void print(vector<string>&, vector<string>& , const string&);

int DL_Distance(string&, string&);
int min(int, int);

int main()
{
    string input;
    string tmp; 
    vector<string> dictionary;
    vector<string> words;
    // Input string and fill the dictionary
    getline(cin, input);
    for (size_t i = 0; i < input.length() + 1; i++)
    {
        if (input[i] == ' ' || input[i] == '\0')
        {
            dictionary.push_back(tmp);
            tmp.clear();
        }
        else
        {
            tmp += input[i];
        }

    }
    tmp.clear();
    input.clear();
    string first_border;
    string second_border;
    getline(cin, first_border);
    // Input string and fiil the words
    getline(cin, input);
    for (size_t i = 0; i < input.size(); i++)
    {
        if (i == input.size() - 1 && input[i] != ' ')
        {
            tmp += input[i];
            words.push_back(tmp);
            tmp.clear();
        }
        if (input[i] == ' ' && input[i - 1] != ' ')
        {
            words.push_back(tmp);
            words.push_back(" ");
            tmp.clear();
        }
        else if (input[i] == ' ' && input[i - 1] == ' ')
        {
            words.push_back(" ");         
        }
        else
        {
            tmp += input[i];
        }      
    }
    getline(cin, second_border);
    int count{};
    while (count != words.size())
    {
        // if space - cout;
        if (words[count] == " ")
        {
            cout << words[count];
            count++;
            continue;
        }
        string word = to_lower(words.at(count));
        if (contains(dictionary.begin(), dictionary.end(), word))
        {
            cout << words.at(count);
        }
        else
        {
            vector<string> one_cor; // words with one edit
            vector<string> two_cor; // words with two edits
            for (string w : dictionary)
            {
                int metric = DL_Distance(word, w);
                if (metric == 1)
                {
                    one_cor.push_back(w);
                }
                if (metric == 2)
                {
                    two_cor.push_back(w);
                }
            }
            print(one_cor, two_cor, words.at(count));
            one_cor.clear();
            two_cor.clear();
        }
        count++;
    }
    return 0;
}

string to_lower(string s) {
    transform(s.begin(), s.end(), s.begin(), tolower);
    return s;
}

void print(vector<string>& correctly_one, vector<string>& correctly_two, const string& w) {

    if (correctly_one.size() == 0 && correctly_two.size() == 0)
    {
        cout << "{" << w << "?}";
        return;
    }
    else if (correctly_one.size() == 0)
    {
        if (correctly_two.size() > 1)
        {
            cout << "{";
            for (int i = 0; i < correctly_two.size(); i++)
            {
                cout << correctly_two[i] << " ";
            }
            cout << correctly_two[correctly_two.size() - 1] << "}";
        }
        else if (correctly_two.size() == 1)
        {
            cout << correctly_two[0];
        }
    }
    else
    {
        if (correctly_one.size() > 1)
        {
            cout << "{";
            for (int i = 0; i < correctly_one.size() - 1; i++)
            {
                cout << correctly_one[i] << " ";
            }
            cout << correctly_one[correctly_one.size() - 1] << "}";
        }
        else
        {
            cout << correctly_one[0];
        }
    }
};

int min(int n1, int n2) {
    return (n1 < n2) ? n1 : n2;
}

// Leventshtein metrics with two operation: insert, delete
int DL_Distance(string& s1, string& s2) {
    if (s1.length() == 0)
    {
        if (s2.length() == 0)
        {
            return 0;
        }
        else
        {
            return s2.length();
        }
    }
    else if (s2.length() == 0)
    {
        return s1.length();
    }

    string word = s1;
    string dictant = s2;
    int tmp = 1;
    int wI = 1;
    int d_OPERATION{};
    int i_OPERATION{};
    int M = word.length() + 2;
    int N = dictant.length() + 2;
    int sumChar = word.length() + dictant.length();
    int length_diff = word.length() - dictant.length();
    if (abs(length_diff) > 2)
    {
        return sumChar;
    }

    int** ary;
    ary = new int* [M];
    for (size_t i = 0; i < M; i++)
    {
        ary[i] = new int[N];
    }


    ary[0][0] = sumChar;
    for (size_t i = 0; i < word.length() + 1; i++)
    {
        ary[i + 1][1] = i;
        ary[i + 1][0] = sumChar;
    }

    for (size_t j = 0; j < dictant.length() + 1; j++)
    {
        ary[1][j + 1] = j;
        ary[0][j + 1] = sumChar;
    }

    for (size_t i = 1; i < word.length() + 1; i++)
    {
        for (size_t j = 1; j < dictant.length() + 1; j++)
        {
            if (word[i - 1] == dictant[j - 1])
            {
                ary[i + 1][j + 1] = ary[i][j];
            }
            else
            {
                d_OPERATION = tmp + ary[i][j + 1];
                i_OPERATION = wI + ary[i + 1][j];
                ary[i + 1][j + 1] = min(d_OPERATION, i_OPERATION);
            }
        }
    }

    int _j = N - 1;
    int _i = M - 1;
    int buff_i = _i; 
    int buff_j = _j;
    vector<int> op;
    while (_i > 0 || _j > 0)
    {
        if (_i == 0)
        {
            op.push_back(2);
            _j--;
        }
        else if (_j == 0)
        {
            op.push_back(1);
            _i--;
        }
        else
        {   
            if (word[_i - 1] == dictant[_j - 1])
            {
                op.push_back(0);
                _i--;
                _j--;
            }
            else
            {
                if (ary[_i - 1][_j] < ary[_i][_j - 1])
                {
                    op.push_back(1);
                    _i--;
                }
                else
                {
                    op.push_back(2);
                    _j--;
                }
            }
        }
    }

    int buff = -1;
    for(int op_ : op)
    {
        if (buff == op_ && op_ != 0)
        {
            return sumChar;
        }
        buff = op_;
    }

    int dl_distance = ary[M - 1][N - 1];


    for (size_t t = 0; t < M; t++)
    {
        delete[] ary[t];
    }
    delete[] ary;
    return dl_distance;
}