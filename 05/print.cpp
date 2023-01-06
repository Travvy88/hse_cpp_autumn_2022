#include <iostream>

using namespace std;

void print() {
    cout << endl;
}

void print(const int& t) {
    cout << t << endl;
}


void print(const float& t) {
    cout << t << endl;
}


template <typename First, typename... Rest> 
void print(const First& first, const Rest&... rest) {
    cout << first << ", ";
    print(rest...); // recursive call using pack expansion syntax
}

int main()
{
    print(10, 2.0, "rrr");
}
