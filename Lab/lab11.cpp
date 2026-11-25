#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;

class Locker {
public:
    Locker(const int no = 0, const string& user = "") {
        setLockerNo(no);
        setLockerUser(user);
    }
    int getLockerNo() const { return lockerNo; }
    void setLockerNo(const int no) { lockerNo = no; }
    string getLockerUser() const { return lockerUser; }
    void setLockerUser(const string& name) {
        for (int i{0}; i<16; i++) {
            lockerUser[i] = '\0';
        }
        for (int i{0}; i<name.length(); i++) {
            lockerUser[i] = name[i];
        }
        lockerUser[name.length()] = '\0';
    }
    void print() const {
        cout <<left << setw(12) << lockerNo << lockerUser << endl;
    }
private:
    int lockerNo;         // locker number in [1, 20]
    char lockerUser[16];  // max. 15 characters for the name
};

int main() {
    int choice;
    fstream locker{"locker.dat", ios::in | ios::out |ios::binary};
    if (!locker) {
        cerr << "File  could not be opened." << endl;
        exiat(EXIT_FAILURE);
    }
    Locker blanck;
    for (int i{0}; i<20; i++) {
        locker.seekp(i*sizeof(Locker));
        locker.write(reinterpret_cast<const char*>(&blanck), sizeof(Locker));
    }
    cout << "Select a menu (1: use, 2: return, 3: print, 4: quit): ";
    cin >> choice;
    while (choice != 4) {
        Locker l;
        string name;
        int lockerNo;
        switch (choice) {
            case 1:
                cout << "Enter locker number [1-20] and user name: ";
                cin >> lockerNo >> name;
                locker.seekp((lockerNo-1)*sizeof(Locker));
                locker.read(reinterpret_cast<char*>(&l), sizeof(Locker));
                if (l.getLockerNo() == 0) {
                    l.setLockerNo(lockerNo);
                    l.setLockerUser(name);
                    cout << "Locker #" << lockerNo << " successfully occupied.\n";
                    locker.seekp((lockerNo-1)*sizeof(Locker));
                    locker.write(reinterpret_cast<char*>(&l), sizeof(Locker));
                }
                else {
                    cout << "Locker #" << lockerNo << " is already occupied\n";
                }
                break;
            case 2:
                cout << "Enter locker number [1-20] to return: ";
                cin >> lockerNo;
                locker.seekg((lockerNo-1)*sizeof(Locker));
                locker.read(reinterpret_cast<char*>(&l), sizeof(Locker));
                if (l.getLockerNo() != 0) {
                    locker.seekg((lockerNo-1)*sizeof(Locker));
                    locker.write(reinterpret_cast<const char*>(&blanck), sizeof(Locker));
                    cout << "Locker #" << lockerNo << " successfully unoccupied.\n";
                }
                else {
                    cout << "Locker #" << lockerNo << " is already vaccant\n";
                }
                break;
            case 3:
                cout << left << setw(12) << "Locker #" << "User\n";
                for (int i{0}; i<20; i++) {
                    locker.seekg(i*sizeof(Locker));
                    locker.read(reinterpret_cast<char*>(&l), sizeof(Locker));
                    if (l.getLockerNo() != 0) {
                        l.print();
                    }
                }
                break;
        }
        cout << "\nSelect a menu (1: use, 2: return, 3: print, 4: quit): ";
        cin >> choice;
    }
    cout << "Bye!";

    return 0;
}
