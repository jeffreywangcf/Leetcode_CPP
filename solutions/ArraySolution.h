//
// ArraySolution.h
// leetcode_cpp
// 
// Created by Jeffrey Wang on 08/11/2020.
// Copyright © 2020 eagersoft.io. All rights reserved.
//

#ifndef LEETCODE_CPP_ARRAYSOLUTION_H
#define LEETCODE_CPP_ARRAYSOLUTION_H

#include <iostream>
#include <vector>
#include <valarray>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <map>
#include <queue>

using namespace std;


namespace ArraySolution {
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces){
        auto table = map<int, vector<int>>();
        for(auto piece: pieces)
            table[piece[0]] = piece;
        int index = 0;
        while(index < arr.size()){
            if(table.find(arr[index]) == table.end())
                return false;
            auto piece = table[arr[index]];
            for(int i = 0; i < piece.size(); i++)
                if(arr[index++] != piece[i])
                    return false;
        }
        return true;
    }

    bool canBeEqual(vector<int>& target, vector<int>& arr){
        int table[1001] = {0};
        for(int i = 0; i < target.size(); i++){
            table[target[i]]++;
            table[arr[i]]--;
        }
        for(auto num: table)
            if(num != 0)
                return false;
        return true;
    }

    vector<int> sortedSquares(vector<int>& A) {
        int begin = 0;
        while(begin < A.size() && A[begin] < 0)
            begin++;
        for(int i = 0; i < A.size(); i++)
            A[i] *= A[i];
        auto ret = vector<int>();
        int st = begin - 1;
        int gt = begin;
        while(st >= 0 && gt < A.size())
            if(A[gt] < A[st])
                ret.push_back(A[gt++]);
            else
                ret.push_back(A[st--]);
        while(gt < A.size())
            ret.push_back(A[gt++]);
        while(st >= 0)
            ret.push_back(A[st--]);
        return ret;
    }

    int heightChecker(vector<int>& heights) {
        auto sorted = vector<int>();
        sorted.reserve(heights.size());
        for(auto height: heights)
            sorted.push_back(height);
        sort(sorted.begin(), sorted.end());
        int ret = 0;
        for(int i = 0; i < heights.size(); i++)
            if(sorted[i] != heights[i])
                ret++;
        return ret;
    }

    bool canMakeArithmeticProgression(vector<int>& arr) {
        if(arr.size() < 3)
            return true;
        sort(arr.begin(), arr.end());
        int step = arr[1] - arr[0];
        for(int i = 1; i < arr.size() - 1; i++)
            if(arr[i + 1] - arr[i] != step)
                return false;
        return true;
    }

    int minCostToMoveChips(vector<int>& position) {
        int even = 0, odd = 0;
        for(auto pos: position)
            pos % 2 == 0 ? even++ : odd++;
        return even > odd ? odd : even;
    }

    vector<int> luckyNumbers(vector<vector<int>>& matrix) {
        auto ret = vector<int>();
        auto mins = unordered_set<int>();
        for(auto row: matrix){
            int min = INT_MAX;
            for(auto item: row)
                if(item < min)
                    min = item;
            mins.insert(min);
        }
        for(int i = 0; i < matrix[0].size(); i++){
            int max = INT_MIN;
            for(int j = 0; j < matrix.size(); j++)
                if(matrix[j][i] > max)
                    max = matrix[j][i];
            if(mins.find(max) != mins.end())
                ret.push_back(max);
        }
        return ret;
    }

    vector<int> sortArrayByParityII(vector<int>& A) {
        auto ret = vector<int>(A.size());
        int even_index = 0, odd_index = 1;
        for(auto a: A){
            if(a % 2 == 0){
                ret[even_index] = a;
                even_index += 2;
            }else{
                ret[odd_index] = a;
                odd_index += 2;
            }
        }
        return ret;
    }

    vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
        auto ret = vector<int>();
        auto table = multimap<int, int>();
        for(int i = 0; i < mat.size(); i++){
            int count = 0, index = 0;
            while(index < mat[1].size() && mat[i][index++])
                count++;
            table.insert(pair<int, int>(count, i));
        }
        for(auto i = table.begin(); i != table.end() && k-- > 0; i++)
            ret.push_back(i->second);
        return ret;
    }

    double average(vector<int>& salary) {
        int sum = 0, min = salary[0], max = salary[0];
        for(auto s: salary){
            sum += s;
            if(s > max)
                max = s;
            if(s < min)
                min = s;
        }
        return (sum - min - max) / (double) (salary.size() - 2);
    }

    vector<string> commonChars(vector<string>& A) {
        int freq[A.size()][26];
        memset(&freq[0][0], 0, sizeof(freq));
        auto ret = vector<string>();
        for(int i = 0; i < A.size(); i++)
            for(auto a: A[i])
                freq[i][a - 'a']++;
        for(int c = 0; c < 26; c++){
            int min_freq = 100;
            for(int i = 0; i < A.size(); i++)
                if(freq[i][c] < min_freq)
                    min_freq = freq[i][c];
            int index = 0;
            while(index++ < min_freq)
                ret.push_back(string(1, c + 'a'));
        }
        return ret;
    }

    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        auto loc = vector<int>(), ret = vector<int>();
        auto pq = priority_queue<int, vector<int>, greater<>>();
        for(auto a: arr1){
            auto it = find(arr2.begin(), arr2.end(), a);
            if(it == arr2.end())
                pq.push(a);
            else
                loc.push_back(it - arr2.begin());
        }
        sort(loc.begin(), loc.end());
        for(auto i: loc)
            ret.push_back(arr2[i]);
        while(!pq.empty()){
            ret.push_back(pq.top());
            pq.pop();
        }
        return ret;
    }

};


#endif //LEETCODE_CPP_ARRAYSOLUTION_H
