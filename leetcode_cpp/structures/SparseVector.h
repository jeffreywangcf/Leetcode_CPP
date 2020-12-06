//
// SparseVector.h
// leetcode_cpp
// 
// Created by Jeffrey Wang on 12/06/2020.
// Copyright © 2020 eagersoft.io. All rights reserved.
// 


#ifndef LEETCODE_CPP_SPARSEVECTOR_H
#define LEETCODE_CPP_SPARSEVECTOR_H

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class SparseVector {
public:
    unordered_map<int, int> table;

    SparseVector(vector<int> &nums) {
        for(int i = 0; i < nums.size(); i++)
            if(nums[i])
                this->table[i] = nums[i];
    }

    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& other) {
        int ret = 0;
        for(auto pair: this->table)
            ret += pair.second * other.table[pair.first];
        return ret;
    }
};

#endif //LEETCODE_CPP_SPARSEVECTOR_H
