#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Word {
public:
    Word(string w) {
        setWord(w);
        setCount(1);
    }
    string getWord() const {
        return word;
    }
    void setWord(string w) {
        word = w;
    }
    int getCount() const {
        return count;
    }
    void setCount(int c) {
        count = c;
    }
    void increment() {
        count++;
    }
private:
    string word;
    int count;
};

int findWord(vector<Word> v, Word w) {
    for (int i{0}; i < v.size(); i++) {
        if (v[i].getWord() == w.getWord()) {
            return i;
        }
    }
    return -1;
}

bool compareWord(const Word& w1, const Word& w2) {
    if (w1.getCount() > w2.getCount()) {
        return true;
    }
    if (w1.getCount() < w2.getCount()) {
        return false;
    }
    else {
        return w1.getWord() < w2.getWord();
    }
}

int main() {
    string filename;
    cout << "Enter the file name: ";
    cin >> filename;
    ifstream input{filename, ios::in};
    ofstream output{"Words_" + filename, ios::out};
    string s{""};
    char c;
    vector<Word> v;
    while (input.get(c)) {
        if (c <= 'z' && c >= 'a') {
            s += c;
        }
        else if (s != "") {
            Word w(s);
            int i = findWord(v, w);
            if (i == -1) {
                v.push_back(w);
            }
            else {
                v[i].increment();
            }
            s = "";
        }
    }

    sort(v.begin(), v.end(), compareWord);
    for (auto e : v) {
        output << e.getWord() << ": " << e.getCount() << endl;
    }

    cout << "Word count has been recorded in file \"" << "Words_" + filename << "\"";
    return 0;
}
