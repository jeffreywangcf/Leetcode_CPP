#include <iostream>
#include "util.h"
#include "solutions/CommonSolution.h"
#include "solutions/ArraySolution.h"

int main() {
    vector<string> testcase = {"bella","label","roller"};
    vector<string> ret = ArraySolution::commonChars(testcase);
    Util::printVector(ret);

    auto a = priority_queue<int, vector<int>, greater<>>();
    a.push(1);
    a.push(0);
    a.push(3);
    while(!a.empty()){
        cout << a.top() << endl;
        a.pop();
    }


    return 0;
}
