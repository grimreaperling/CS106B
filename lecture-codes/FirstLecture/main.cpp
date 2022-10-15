/*
 * File: main.cpp
 * --------------
 * Blank C++ project configured to use Stanford cslib and Qt
 */
#include <cmath>
#include "console.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;
/*
 * M
 * MA
 * MAR
 * MART
 * MARTY
 *  ARTY
 *   RTY
 *    TY
 *     Y
 */
void nameDiamond(string s){
    //first half of the diamond
    for(int i = 0; i <= s.length(); i++){
        cout << s.substr(0, i) << endl;
    }
    for(int i = 0; i < s.length(); i++){
        for(int j = 0; j <= i; j++)
            cout << " " ;
        cout << s.substr(i+1) <<endl;
    }
}
void quadratic(int a, int b, int c, double& root1, double& root2){
    double d = sqrt(b*b - 4*a*c);
    root1 = (-b + d)/(2*a);
    root2 = (-b - d)/(2*a);
}

int main()
{
      string s ="MARTY";
      nameDiamond(s);
//    double root1, root2;
//    string s = "Hello";
//    int age = stringToInteger("48");
//    string name = getLine("Type your name: ");
//    s.append(" Stepp"); //the string is mutable in c++
//    s.erase(3,2);
//    cout << s << " " << name << " " << age << endl;
//    int a = getInteger("PLease input the first parameter!");
//    int b = getInteger("PLease input the second parameter!");
//    int c = getInteger("PLease input the third parameter!");
//    quadratic(a, b, c, root1, root2);
//    cout << "The roots are "<< root1 << " and " << root2 << endl;
    return 0;
}
