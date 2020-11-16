//
// util.cpp
// leetcode_cpp
// 
// Created by Jeffrey Wang on 16/11/2020.
// Copyright © 2020 eagersoft.io. All rights reserved.
// 

#include "util.h"
#include <iostream>
#include <vector>

using namespace std;

template<class T>
void Util::printVector(vector<T> v) {
    cout << "{ ";
    for(auto item: v)
        cout << item << ", ";
    cout << "}" << endl;
}