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
#include <unordered_map>
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

    int countCharacters(vector<string>& words, string chars) {
        int ret = 0;
        auto table = unordered_map<char, int>();
        for(auto c: chars)
            table[c]++;
        for(const auto& word: words){
            bool flag = true;
            auto cp_table = unordered_map<char, int>();
            for(auto c: word)
                cp_table[c]++;
            for(auto c: word){
                if(table[c] < cp_table[c]){
                    flag = false;
                    break;
                }
            }
            if(flag)
                ret += word.size();
        }
        return ret;
    }

    int fib(int N) {
        if(N < 2){
            return N;
        }
        int a = 0, b = 1, sum = 1;
        while(N-- > 2){
            a = b;
            b = sum;
            sum = a + b;
        }
        return sum;
    }

    int largestUniqueNumber(vector<int>& A) {
        int table[1001] = {}, i = -1;
        for(auto a: A)
            table[a]++;
        for(i = 1000; i >= 0 && table[i] != 1; i--);
        return i;
    }

    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        auto ret = vector<vector<int>>();
        int min_dis = INT_MAX;
        for(int i = 1; i < arr.size(); i++){
            int dis = arr[i] - arr[i - 1];
            if(dis < min_dis){
                min_dis = dis;
                ret.clear();
                ret.push_back({arr[i - 1], arr[i]});
            }else if(dis == min_dis){
                ret.push_back({arr[i - 1], arr[i]});
            }
        }
        return ret;
    }

    double trimMean(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        int to_remove = (int) (arr.size() * 0.05);
        int sum = 0;
        for(int i = to_remove; i < arr.size() - to_remove; i++)
            sum += arr[i];
        return (double) sum / (double) (arr.size() - to_remove * 2);
    }

    vector<int> frequencySort(vector<int>& nums) {
        auto table = map<int, int>();
        auto ret = vector<int>();
        for(auto num: nums)
            table[num]++;
        auto freq = vector<pair<int, int>>();
        for(auto p: table)
            freq.push_back({p.second, -p.first}); //negative sign for decreasing
        sort(freq.begin(), freq.end());
        for(auto f: freq)
            cout << f.first << " " << f.second << endl;
        for(auto f: freq)
            ret.insert(ret.end(), f.first, -f.second);
        return ret;
    }

    bool threeConsecutiveOdds(vector<int>& arr) {
        int count = 0;
        for(auto a: arr){
            if(a % 2 == 1)
                count++;
            else
                count = 0;
            if(count >= 3)
                return true;
        }
        return false;
    }

    int fixedPoint(vector<int>& A) {
        for(int i = 0; i < A.size(); i++)
            if(i == A[i])
                return i;
        return -1;
    }

    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        for(int i = 0; i < matrix.size() - 1; i++)
            for(int j = 0; j < matrix[0].size() - 1; j++)
                if(matrix[i][j] != matrix[i + 1][j + 1])
                    return false;
        return true;
    }

    int findLucky(vector<int>& arr) {
       int table[501] = {0};
       for(auto a: arr)
           table[a]++;
       auto max = -1;
       for(int i = 1; i < 501; i++)
           if(table[i] == i && i > max)
               max = i;
       return max;
    }

    int minStartValue(vector<int>& nums) {
        auto sum = 0, min_sum = 0;
        for(auto num: nums){
            sum += num;
            min_sum = min(min_sum, sum);
        }
        return 1 - min_sum;
    }

    int numSpecial(vector<vector<int>>& mat) {
        int row_sum[mat.size()];
        int col_sum[mat[0].size()];
        for(int i = 0; i < mat.size(); i++){
            row_sum[i] = 0;
            for(auto num: mat[i])
                row_sum[i] += num;
        }
        for(int i = 0; i < mat[0].size(); i++){
            col_sum[i] = 0;
            for(int j = 0; j < mat.size(); j++)
                col_sum[i] += mat[j][i];
        }
        int ret = 0;
        for(int i = 0; i < mat.size(); i++)
            for(int j = 0; j < mat[0].size(); j++)
                if(mat[i][j] == 1 && row_sum[i] == 1 && col_sum[j] == 1)
                    ret++;
        return ret;
    }

    int specialArray(vector<int>& nums) {
        int table[1001] = {0};
        for(auto num: nums)
            table[num]++;
        auto total = nums.size();
        for(int i = 0; i < 1001; i++){
            if(total == i)
                return i;
            total -= table[i];
        }
        return -1;
    }

    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        const int n_row = grid.size();
        const int n_col = grid[0].size();
        vector<vector<int>> ret(n_row, vector<int>(n_col, 0));
        for(int i = 0; i < n_row; i++){
            for(int j = 0; j < n_col; j++){
                const int n_i = (i + (j + k) / n_col) % n_row;
                const int n_j = (j + k) % n_col;
                ret[n_i][n_j] = grid[i][j];
            }
        }
        return ret;
    }

    int twoSumLessThanK(vector<int>& A, int K) {
        int max = -1;
        for(int i = 0; i < A.size() - 1; i++)
            for(int j = i + 1; j < A.size(); j++)
                if(A[i] + A[j] < K && A[i] + A[j] > max)
                    max = A[i] + A[j];
        return max;
    }
};


#endif //LEETCODE_CPP_ARRAYSOLUTION_H
