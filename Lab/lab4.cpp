#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

class Date {
    friend ostream& operator<<(ostream&, const Date&);
    friend istream& operator>>(istream&, Date&);
public:
    Date(int m = 1, int d = 1, int y = 1900); // default constructor
    void setDate(int, int, int); // set month, day, year
    Date get100thDay() const;
    Date getFirstBirthday() const;
    Date getGoSchool() const;
    Date& operator++(); // prefix increment operator
    Date operator++(int); // postfix increment operator
    Date& operator+=(unsigned int); // add days, modify object
    static bool leapYear(int); // is year a leap year?
    bool endOfMonth(int) const; // is day at the end of month?
private:
    unsigned int month;
    unsigned int day;
    unsigned int year;
    static const array<int, 13> days; // days per month
    void helpIncrement(); // utility function for incrementing date
};

// Date class member- and friend-function definitions.

const array<int, 13> Date::days{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

Date::Date(int month, int day, int year) {
    setDate(month, day, year);
}

void Date::setDate(int mm, int dd, int yy) {
    month = mm;
    day = dd;
    year = yy;
}

Date Date::get100thDay() const {
    Date temp = *this;
    temp += 99;
    return temp;
}

Date Date::getFirstBirthday() const {
    if (month == 2 && day == 29)
        return Date(2, 28, year + 1);

    return Date(month, day, year + 1);
}

Date Date::getGoSchool() const {
    return Date(3, 1, year + 7);
}

// overloaded prefix increment operator
Date& Date::operator++() {
    helpIncrement(); // increment date
    return *this; // reference return to create an lvalue
}

// overloaded postfix increment operator
Date Date::operator++(int) {
    Date temp{*this}; // hold current state of object
    helpIncrement();

    // return unincremented, saved, temporary object
    return temp;  // value return; not a reference return
}

// add specified number of days to date
Date& Date::operator+=(unsigned int additionalDays) {
    for (unsigned int i = 0; i < additionalDays; ++i) {
        helpIncrement();
    }
    return *this; // enables cascading
}

bool Date::leapYear(int testYear) {
    return (testYear%400==0 || (testYear%100 != 0 && testYear%4==0));
}

bool Date::endOfMonth(int testDay) const {
    if (month == 2 && leapYear(year))
        return testDay == 29; // last day of Feb. in leap year
    else return testDay == days[month];
}

void Date::helpIncrement() {
    if (!endOfMonth(day))
        ++day; // increment day
    else {
        if (month < 12) { // day is end of month and month < 12
            ++month; // increment month
            day = 1; // first day of new month
        }
        else { // last day of year
            ++year; // increment year
            month = 1; // first month of new year
            day = 1; // first day of new month
        }
    }
}

ostream& operator<<(ostream& output, const Date& d) {
    output << d.month << '/' << d.day << "/" << d.year;
    return output; // enables cascading
}

istream& operator>>(istream& input, Date& d) {
    int mm, dd, yy;
    input >> mm;
    input.ignore();
    input >> dd;
    input.ignore();
    input >> yy;
    d.setDate(mm, dd, yy);
    return input;
}

class Baby {
    public:
    Baby(const string& name, const Date& d) {
        setName(name);
        setBirthDate(d);
    }
    void setName(const string& name) {
        this->name = name;
    }
    void setBirthDate(const Date& d) {
        birthDate = d;
    }
    string getName() const {
        return name;
    }
    Date getBirthDate() const {
        return birthDate;
    }
    private:
    string name;
    Date birthDate;
};

bool compareName(const Baby& b1, const Baby& b2) {
    return b1.getName() < b2.getName();
}

int main() {
    int n;
    cout << "Enter the number of newborn babies: ";
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<Baby> bVec;

    for (int i{0}; i<n; i++) {
        Date birth;
        string name;
        cout << "\nEnter the baby name: ";
        getline(cin, name);
        cout << "Enter the baby's birth date in the form mm/dd/yyyy: ";
        cin >> birth;
        Baby b(name, birth);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << name << " born on " << birth << endl;
        cout << "100th day: " << b.getBirthDate().get100thDay() << endl;
        cout << "First birthday: " << b.getBirthDate().getFirstBirthday() << endl;
        cout << "First school day: " << b.getBirthDate().getGoSchool() << endl;

        bVec.push_back(b);
    }

    sort(bVec.begin(), bVec.end(), compareName);
    cout << "\nNewborn babies in the alphabetical order of names:\n";
    for (int i{0}; i<n; i++) {
        cout << bVec[i].getName() << " (" << bVec[i].getBirthDate() << ")\n";
    }
}

