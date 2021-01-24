#include <iostream>
#include "util.h"
#include "solutions/CommonSolution.h"
#include "solutions/ArraySolution.h"

int main() {
    vector<string> testcase = {"bella","label","roller"};
    vector<string> ret = ArraySolution::commonChars(testcase);
    Util::printVector(ret);
    return 0;
}
