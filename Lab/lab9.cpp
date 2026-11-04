#include <iostream>
#include <iomanip>
using namespace std;

class IPv4 {
    friend ostream& operator<<(ostream&, const IPv4&); // 2가지 포맷으로 IP 주소 출력
    friend istream& operator>>(istream&, IPv4&); // IP 주소 입력하여 전용 데이터멤버에 저장
public:
    IPv4() {
        for (int i{0}; i<4; i++) {
            ip[i] = 0;
        }
        addr = 0x0;
    }
private:
    unsigned char ip[4]; // x.x.x.x 형식의 IP 주소에서 각 숫자를 저장하는 문자배열
    unsigned int addr;   // 각 숫자가 2자리 16진수로 변환되어 병합된 8자리 16진수
};

ostream& operator<<(ostream& output, const IPv4& ipv4) {
    output << "IP address in decimal: " << dec << (int)ipv4.ip[0] << '.' << (int)ipv4.ip[1] << '.' << (int)ipv4.ip[2] << '.' << (int)ipv4.ip[3] << "\nIP address in hexadecimal: " << hex << "0X" << uppercase << setfill('0') << setw(8) << ipv4.addr;
    return output;
}

istream& operator>>(istream& input, IPv4& ipv4){
    char c;
    int i{0};
    while (input.get(c) && c != '\n') {
        if (c != '.') {
            ipv4.ip[i] *= 10;
            ipv4.ip[i] += c - '0';
        }
        else {
            i++;
        }
    }

    for (int i{0}; i<4; i++) {
        ipv4.addr = ipv4.addr << 8;
        ipv4.addr = ipv4.addr | ipv4.ip[i];
    }

    return input;
}

int main() {
    cout << "Enter an IP address in the format x.x.x.x (EOF to quit): ";
    IPv4 ipv4;
    while (cin >> ipv4) {
        cout << ipv4;
        ipv4 = IPv4();
        cout << "\n\nEnter an IP address in the format x.x.x.x (EOF to quit): ";
    }

    return 0;
}
