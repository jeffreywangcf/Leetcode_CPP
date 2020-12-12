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
#include <numeric>
#include <list>

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

    vector<int> sumEvenAfterQueries(vector<int>& A, vector<vector<int>>& queries) {
        auto ret = vector<int>();
        int sum = 0;
        for(auto a: A)
            if(a % 2 == 0)
                sum += a;
        for(auto query: queries){
            int before = A[query[1]];
            if(before % 2 == 0)
                sum -= before;
            A[query[1]] += query[0];
            if(A[query[1]] % 2 == 0)
                sum += A[query[1]];
            ret.push_back(sum);
        }
        return ret;
    }

    vector<vector<int>> matrixReshape(vector<vector<int>>& nums, int r, int c) {
        const int y = nums.size();
        const int x = nums[0].size();
        if((y == r && x == c) || (y * x != r * c))
            return nums;
        vector<vector<int>> ret(r, vector<int>(c, 0));
        for(int i = 0; i <x * y; i++)
            ret[i / c][i % c] = nums[i / x][i % x];
        return ret;
    }

    char slowestKey(vector<int>& releaseTimes, string keysPressed) {
        int max_time = releaseTimes[0];
        char max_key = keysPressed[0];
        for(int i = 1; i < releaseTimes.size(); i++){
            auto t = releaseTimes[i] - releaseTimes[i - 1];
            if(t > max_time){
                max_key = keysPressed[i];
                max_time = t;
            }else if(t == max_time && keysPressed[i] > max_key){
                max_key = keysPressed[i];
                max_time = t;
            }
        }
        return max_key;
    }

    int findSpecialInteger(vector<int>& arr) {
        auto table = unordered_map<int, int>();
        for(auto num: arr){
            table[num]++;
            if(table[num] > arr.size() / 2)
                return num;
        }
        return -1;
    }

    int majorityElement(vector<int>& nums) {
        //A Linear Time Majority Vote Algorithm
        int ret = -1, count = 0;
        for(auto num: nums){
            if(count == 0){
                ret = num;
                count++;
            }
            else
                num == ret ? count++ : count--;
        }
        return ret;
    }

    //helper function
    int getMaxFrequency(const string &str){
        int table[26] = {0};
        for(auto c: str)
            table[c - 'a']++;
        for(int freq : table)
            if(freq != 0)
                return freq;
        return 0;
    }

    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        auto table = map<int, int>();
        auto ret = vector<int>();
        for(auto &word : words)
            table[getMaxFrequency(word)]++;
        for(const auto &query: queries){
            int target = getMaxFrequency(query);
            int count = 0;
            for(auto pair: table)
                if(pair.first > target)
                    count += pair.second;
            ret.push_back(count);
        }
        return ret;
    }

    int countElements(vector<int>& arr) {
        int table[1002] = {0};
        int ret = 0;
        for(auto a: arr)
            table[a]++;
        for(auto a: arr)
            if(table[a + 1] != 0)
                ret += 1;
        return ret;
    }

    vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
        // sum1 - x + y = sum2 + x - y
        //2y = 2x + sum2 - sum1
        //y = x + (sum2 - sum1)/2
        int sum1 = accumulate(A.begin(), A.end(), 0);
        int sum2 = accumulate(B.begin(), B.end(), 0);
        unordered_set<int> table(B.begin(), B.end());
        for(auto a: A){
            int target = a + (sum2 - sum1) / 2;
            if(table.find(target) != table.end())
                return {a, target};
        }
        return {0, 0};
    }

    bool isMajorityElement(vector<int>& nums, int target) {
        int count = 0, sz = nums.size();
        for(const auto &num: nums)
            if(num == target)
                if(++count > (sz / 2))
                    return true;
        return false;
    }

    bool isMonotonic(vector<int>& A) {
        bool increasing = true, decreasing = true;
        for(int i = 0; i < A.size() - 1; i++){
            if(A[i + 1] > A[i])
                decreasing = false;
            if(A[i + 1] < A[i])
                increasing = false;
            if(!increasing && !decreasing)
                return false;
        }
        return true;
    }

    int maxProfitII(vector<int>& prices) {
        int ret = 0;
        for(int i = 0; i < prices.size() - 1; i++)
            if(prices[i + 1] > prices[i])
                ret += prices[i + 1] - prices[i];
        return ret;
    }

    vector<int> arrayRankTransform(vector<int>& arr) {
        auto table = unordered_map<int, int>();
        set<int> sorted(arr.begin(), arr.end());
        int rank = 1;
        for(auto num: sorted)
            table[num] = rank++;
        for(auto &a: arr)
            a = table[a];
        return arr;
    }

    int distanceBetweenBusStops(vector<int>& distance, int start, int destination) {
        int cw = 0, ccw = 0, cw_index = start, ccw_index = start;
        while(cw_index != destination){
            cw += distance[cw_index++];
            if(cw_index == distance.size())
                cw_index = 0;
        }
        while(ccw_index != destination){
            if(ccw_index == 0)
                ccw_index = distance.size();
            ccw += distance[--ccw_index];
        }
        return min(cw, ccw);
    }

    int findShortestSubArray(vector<int>& nums) {
        auto table = unordered_map<int, int>();
        for(auto num: nums)
            table[num]++;
        auto max_pair = pair<int, int>(-1, -1);
        for(auto p: table)
            if(p.second > max_pair.second)
                max_pair = p;
        int ret = nums.size();
        for(auto p: table){
            if(p.second == max_pair.second){
                int first = -1, last = -1;
                int freq_count = 0;
                for(int i = 0; freq_count < p.second; i++){
                    if(nums[i] == p.first){
                        if(first == -1)
                            first = i;
                        last = i;
                        freq_count++;
                    }
                }
                int interval = last - first + 1;
                if(interval < ret)
                    ret = interval;
            }
        }
        return ret;
    }

    vector<vector<int>> generate(int numRows) {
        auto ret = vector<vector<int>>(numRows);
        if(numRows == 0)
            return ret;
        ret[0].push_back(1);
        if(numRows == 1)
            return ret;
        ret[1].insert(ret[1].end(), 2, 1);
        if(numRows == 2)
            return ret;
        for(int row = 2; row < numRows; row++){
            ret[row].push_back(1);
            for(int i = 1; i < row; i++)
                ret[row].push_back(ret[row - 1][i - 1] + ret[row - 1][i]);
            ret[row].push_back(1);
        }
        return ret;
    }

    int findMaxConsecutiveOnes(vector<int>& nums) {
        int max = 0, current = 0, index = 0;
        while(index < nums.size()){
            if(nums[index] == 1){
                current = 1;
                while((++index < nums.size()) && nums[index] == 1)
                    current++;
                if(current > max)
                    max = current;
            }else{
                index++;
            }
        }
        return max;
    }

    int findKthPositive(vector<int>& arr, int k) {
        int index = 0, posNum = 0;
        while(++posNum){
            if(index < arr.size() && posNum == arr[index])
                index++;
            else{
                if(--k == 0)
                    return posNum;
            }
        }
        return posNum;
    }

    string stringShift(string s, vector<vector<int>>& shift) {
        int totalShift = 0;
        string ret(s.size(), ' ');
        for(auto sh: shift)
            totalShift += sh[0] ? sh[1] : -sh[1];
        if(totalShift == 0)
            return s;
        for(int i = 0; i < s.size(); i++){
            int newIndex = (i + abs(totalShift)) % s.size();
            if(totalShift > 0)
                ret[newIndex] = s[i];
            else
                ret[i] = s[newIndex];
        }
        return ret;
    }

    string tictactoe(vector<vector<int>>& moves) {
        int rows[3] = {0}, cols[3] = {0};
        int d1 = 0, d2 = 0;
        bool isAPlaying = true;
        for(auto move: moves){
            int x = move[0], y = move[1];
            if(isAPlaying){
                rows[x]++;
                cols[y]++;
                if(x == y)
                    d1++;
                if(x == (2 - y))
                    d2++;
            }else{
                rows[x]--;
                cols[y]--;
                if(x == y)
                    d1--;
                if(x == (2 - y))
                    d2--;
            }
            if(rows[x] == 3 || cols[y] == 3 || d1 == 3 || d2 == 3)
                return "A";
            if(rows[x] == -3 || cols[y] == -3 || d1 == -3 || d2 == -3)
                return "B";
            isAPlaying = !isAPlaying;
        }
        if(moves.size() < 9)
            return "Pending";
        return "Draw";
    }

    void duplicateZeros(vector<int>& arr) {
        auto ret = vector<int>();
        int index = 0;
        while(ret.size() <= arr.size()){
            if(arr[index] != 0){
                ret.push_back(arr[index++]);
                continue;
            }
            ret.push_back(arr[index]);
            ret.push_back(arr[index++]);
        }
        arr = vector<int>(ret.begin(), ret.begin() + arr.size());
    }

    vector<int> getRow(int rowIndex) {
        vector<int> ret{1}, current{1};
        for(int i = 1; i <= rowIndex; i++){
            ret.push_back(1);
            for(int j = 1; j < i; j++)
                ret[j] = current[j] + current[j - 1];
            current = ret;
        }
        return ret;
    }

    int maxProfitI(vector<int>& prices) {
        int diff = 0, minVal = INT_MAX;
        for(const auto &price : prices){
            minVal = min(minVal, price);
            diff = max(diff, price - minVal);
        }
        return diff;
    }

    int minCostClimbingStairs(vector<int>& cost) {
        for(int i = 2; i < cost.size(); i++)
            cost[i] += min(cost[i - 1], cost[i - 2]);
        return min(cost[cost.size() - 1], cost[cost.size() - 2]);
    }

    vector<int> transformArray(vector<int>& arr) {
        while(true){
            bool change = false;
            auto aux = vector<int>(arr.size());
            aux[0] = arr[0];
            aux[arr.size() - 1] = arr[arr.size() - 1];
            for(int i = 1; i < arr.size() - 1; i++){
                if(arr[i - 1] > arr[i] && arr[i] < arr[i + 1]){
                    aux[i] = arr[i] + 1;
                    change = true;
                }else if(arr[i - 1] < arr[i] && arr[i] > arr[i + 1]){
                    aux[i] = arr[i] - 1;
                    change = true;
                }else{
                    aux[i] = arr[i];
                }
            }
            arr = aux;
            if(!change)
                break;
        }
        return arr;
    }

    vector<vector<int>> largeGroupPositions(string s) {
        auto ret = vector<vector<int>>();
        int left = 0, right = 0;
        while(right < s.size()){
            left = right;
            while(right + 1 < s.size() && s[right + 1] == s[left])
                right++;
            if(right - left > 2)
                ret.push_back({left, right});
        }
        return ret;
    }

    bool canThreePartsEqualSum(vector<int>& A) {
        auto sum = accumulate(A.begin(), A.end(), 0);
        if(sum % 3 != 0)
            return false;
        int partSum = sum / 3, temp = 0, ret = 0;
        for(auto a: A){
            temp += a;
            if(temp == partSum){
                temp = 0;
                ret++;
            }
        }
        if(ret > 2)
            return true;
        return false;
    }

    int getMaximumGenerated(int n) {
        if(n == 0)
            return 0;
        auto aux = vector<int>(n + 2, 0);
        aux[1] = 1;
        int max_num = 1;
        for(int i = 1; i < (n + 1) / 2; i++){
            aux[2 * i] = aux[i];
            aux[2 * i + 1] = aux[i] + aux[i + 1];
            max_num = max(max_num, max(aux[2 * i + 1], aux[2 * i]));
        }
        return max_num;
    }

    int numPairsDivisibleBy60(vector<int>& time) {
        int ret = 0;
        int table[60] = {0};
        for(auto t: time){
            auto rem = t % 60;
            if(rem == 0)
                ret += table[rem];
            else
                ret += table[60 - rem];
            table[rem]++;
        }
        return ret;
    }

    vector<bool> prefixesDivBy5(vector<int>& A) {
        //will overflow
//        auto ret = vector<bool>(A.size());
//        int val = 0;
//        for(int i = 0; i < A.size(); i++){
//            val = (val * 2) + A[i];
//            ret[i] = val % 5 == 0;
//        }
//        return ret;

        //https://leetcode.com/problems/binary-prefix-divisible-by-5/discuss/265601/Detailed-Explanation-using-Modular-Arithmetic-O(n)
        auto ret = vector<bool>(A.size());
        int val = 0;
        for(int i = 0; i < A.size(); i++){
            val = ((val * 2) + A[i]) % 5;
            ret[i] = val == 0;
        }
        return ret;
    }

    int maxSubArray(vector<int>& nums) {
        int maxVal = INT_MIN, sum = 0;
        for(auto num: nums){
            sum += num;
            maxVal = max(maxVal, sum);
            if(sum < 0)
                sum = 0;
        }
        return maxVal;
    }

    int maximumProduct(vector<int>& nums) {
        int min1 = INT_MAX, min2 = INT_MAX;
        int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN;
        for(auto num: nums){
            if(num > max1){
                max3 = max2;
                max2 = max1;
                max1 = num;
            }else if(num > max2){
                max3 = max2;
                max2 = num;
            }else if(num > max3){
                max3 = num;
            }
            if(num < min1){
                min2 = min1;
                min1 = num;
            }else if(num < min2){
                min2 = num;
            }
        }
        return max((max1 * max2 * max3), (min1 * min2 * max1));
    }

    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        int ret = 0;
        auto table = unordered_map<int, int>();
        for(auto domino: dominoes){
            int key = max(domino[0], domino[1]) * 10 + min(domino[1], domino[0]);
            table[key]++;
        }
        for(auto pair: table)
            if(pair.second > 1)
                ret += (pair.second * (pair.second - 1)) / 2;
        return ret;
    }

    int findLengthOfLCIS(vector<int>& nums) {
        if(nums.size() < 2)
            return nums.size();
        int ret = 1, current = 1;
        for(int i = 1; i < nums.size(); i++)
            if(nums[i] > nums[i - 1])
                ret = max(ret, ++current);
            else
                current = 1;
        return ret;
    }

    int pivotIndex(vector<int>& nums) {
        auto sum = accumulate(nums.begin(), nums.end(), 0);
        auto left = 0;
        for(int i = 0; i < nums.size(); i++){
            left += nums[i];
            sum -= nums[i];
            if(left == sum)
                return i;
        }
        return -1;
    }

    vector<int> addToArrayForm(vector<int>& A, int K) {
        for(int i = A.size() - 1; i >= 0 && K >= 0; i--){
            A[i] += K;
            K = A[i] / 10;
            A[i] %= 10;
        }
        while(K > 0){
            A.insert(A.begin(), K % 10);
            K /= 10;
        }
        return A;
    }

    bool checkStraightLine(vector<vector<int>>& coordinates) {
        if(coordinates.size() <= 2)
            return true;
        vector<int> slope = {coordinates[1][0] - coordinates[0][0],
                     coordinates[1][1] - coordinates[0][1]
        };
        for(int i = 2; i < coordinates.size(); i++){
            vector<int> diff = {coordinates[i][0] - coordinates[1][0],
                         coordinates[i][1] - coordinates[1][1]
            };
            if(diff[0] * slope[1] != diff[1] * slope[0])
                return false;
        }
        return true;
    }

    vector<int> plusOne(vector<int>& digits) {
        for(int i = digits.size() - 1; i >= 0; i--){
            if(digits[i] == 9)
                digits[i] = 0;
            else{
                digits[i]++;
                return digits;
            }
        }
        digits[0]++;
        digits.push_back(0);
        return digits;
    }

    int dominantIndex(vector<int>& nums) {
        int firstMax = INT_MIN, secondMax = INT_MIN, index = -1;
        for(int i = 0; i < nums.size(); i++){
            if(nums[i] > firstMax){
                secondMax = firstMax;
                firstMax = nums[i];
                index = i;
            }else if(nums[i] > secondMax){
                secondMax = nums[i];
            }
        }
        if(firstMax / 2 >= secondMax)
            return index;
        return -1;
    }

    int searchInsert(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while(left < right){
            int mid = left + (right - left) / 2;
            if(target > nums[mid])
                left = mid + 1;
            else
                right = mid;
        }
        return left;
    }

    bool containsPattern(vector<int>& arr, int m, int k) {
        int count = 0;
        for(int i = 0; i + m < arr.size(); i++){
            if(arr[i] != arr[i + m]){
                count = 0;
                continue;
            }
            if(++count == (k - 1) * m)
                return true;
        }
        return false;
    }

    double findMaxAverage(vector<int>& nums, int k) {
        int i = 0, j = k - 1;
        double sum = accumulate(nums.begin(), nums.begin() + k, 0);
        double last = sum;
        while(++j < nums.size()){
            last = last - nums[i] + nums[j];
            sum = max(sum, last);
            i++;
        }
        return sum / k;
    }

    vector<string> summaryRanges(vector<int>& nums) {
        auto ret = vector<string>();
        int i = 0, j = 0;
        while(j < nums.size()){
            while(j + 1 < nums.size() && nums[j + 1] == nums[j] + 1)
                j++;
            if(j == i)
                ret.push_back(to_string(nums[i]));
            else
                ret.push_back(to_string(nums[i]) + "->" + to_string(nums[j]));
            i = ++j;
        }
        return ret;
    }

    bool checkIfExist(vector<int>& arr) {
        if(count(arr.begin(), arr.end(), 0) > 1)
            return true;
        for(auto a: arr)
            if(a && (find(arr.begin(), arr.end(), 2*a) != arr.end()))
                return true;
        return false;
    }

    bool hasGroupsSizeX(vector<int>& deck) {
        auto table = unordered_map<int, int>();
        int ret = 0;
        for(auto d: deck)
            table[d]++;
        for(auto p: table)
            ret = gcd(p.second, ret);
        return ret > 1;
    }

    bool validMountainArray(vector<int>& arr) {
        if(arr.size() < 3 || arr[0] >= arr[1])
            return false;
        bool ascending = true;
        for(int i = 2; i < arr.size(); i++)
            if(arr[i] < arr[i - 1])
                ascending = false;
            else if(arr[i] == arr[i - 1] || !ascending)
                return false;
        return !ascending;
    }

    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        flowerbed.insert(flowerbed.begin(), 0);
        flowerbed.insert(flowerbed.end(), 0);
        for(int i = 1; i < flowerbed.size() - 1; i++){
            if(flowerbed[i - 1] + flowerbed[i] + flowerbed[i + 1] == 0){
                n--;
                flowerbed[i] = 1;
            }
        }
        return n <= 0;
    }

    bool checkPossibility(vector<int>& nums) {
        int count = 0;
        nums.insert(nums.begin(), 0);
        for(int i = 2; i < nums.size(); i++){
            if(nums[i] < nums[i - 1]){
                count++;
                if(nums[i - 2] <= nums[i])
                    nums[i - 1] = nums[i];
                else
                    nums[i] = nums[i - 1];
            }
        }
        return count <= 1;
    }

    int numTeams(vector<int>& rating) {
        int ret = 0;
        for(int j = 1; j < rating.size() - 1; j++){
            int leftSmall = 0, rightSmall = 0;
            int leftLarge = 0, rightLarge = 0;
            for(int i = 0; i < j; i++)
                if(rating[i] < rating[j])
                    leftSmall++;
                else if(rating[i] > rating[j])
                    leftLarge++;
            for(int k = j + 1; k < rating.size(); k++)
                if(rating[j] < rating[k])
                    rightLarge++;
                else if(rating[j] > rating[k])
                    rightSmall++;
            ret += leftSmall * rightLarge + leftLarge * rightSmall;
        }
        return ret;
    }

    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        auto table = unordered_map<int, priority_queue<int>>();
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                table[i - j].push(mat[i][j]);
        for(int i = m - 1; i >= 0; i--){
            for(int j = n - 1; j >= 0; j--){
                mat[i][j] = table[i - j].top();
                table[i - j].pop();
            }
        }
        return mat;
    }

    vector<int> deckRevealedIncreasing(vector<int>& deck) {
        sort(deck.begin(), deck.end());
        auto deq = deque<int>();
        deq.push_front(deck.back());
        deck.pop_back();
        while(!deck.empty()){
            int temp = deq.back();
            deq.pop_back();
            deq.push_front(temp);
            deq.push_front(deck.back());
            deck.pop_back();
        }
        return vector<int>(deq.begin(), deq.end());
    }

    vector<vector<int>> candyCrush(vector<vector<int>>& board) {
        int m = board.size(), n = board[0].size();
        bool flag = false;
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n - 2; j++){
                int a = abs(board[i][j]), b = abs(board[i][j + 1]), c = abs(board[i][j + 2]);
                if(a == b && b == c && a != 0){
                    board[i][j] = board[i][j + 1] = board[i][j + 2] = -a;
                    flag = true;
                }
            }
        }
        for(int i = 0; i < m - 2; i++){
            for(int j = 0; j < n; j++){
                int a = abs(board[i][j]), b = abs(board[i + 1][j]), c = abs(board[i + 2][j]);
                if(a == b && b == c && a != 0){
                    board[i][j] = board[i][j + 1] = board[i][j + 2] = -a;
                    flag = true;
                }
            }
        }
        for(int j = 0; j < n - 2; j++){
            int fall = m - 1;
            for(int i = m - 1; i >= 0; i--)
                if(board[i][j] > 0)
                    board[fall--][j] = board[i][j];
            while(fall >= 0)
                board[fall--][j] = 0;
        }
        return flag ? candyCrush(board) : board;
    }

    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        auto ret = vector<vector<int>>();
        vector<vector<bool>> table(8, vector<bool>(8, false));
        for(auto queen: queens)
            table[queen[0]][queen[1]] = true;

        for(int i = king[0] - 1; i >= 0; i--){  //top
            if (table[i][king[1]]){
                ret.push_back({i, king[1]});
                break;
            }
        }
        for(int i = king[0] + 1; i < 8; i++){  //bottom
            if (table[i][king[1]]){
                ret.push_back({i, king[1]});
                break;
            }
        }
        for(int j = king[1] - 1; j >= 0; j--){  //left
            if (table[king[0]][j]){
                ret.push_back({king[0], j});
                break;
            }
        }
        for(int j = king[1] + 1; j < 8; j++){  //right
            if (table[king[0]][j]){
                ret.push_back({king[0], j});
                break;
            }
        }
        for(int i = king[0] - 1, j = king[1] - 1; i >= 0 && j >= 0; i--, j--){  //top left
            if (table[i][j]){
                ret.push_back({i, j});
                break;
            }
        }
        for(int i = king[0] - 1, j = king[1] + 1; i >= 0 && j < 8; i--, j++){  //top right
            if (table[i][j]){
                ret.push_back({i, j});
                break;
            }
        }
        for(int i = king[0] + 1, j = king[1] - 1; i < 8 && j >= 0; i++, j--){  //bottom left
            if (table[i][j]){
                ret.push_back({i, j});
                break;
            }
        }
        for(int i = king[0] + 1, j = king[1] + 1; i < 8 && j < 8; i++, j++){  //bottom right
            if (table[i][j]){
                ret.push_back({i, j});
                break;
            }
        }

        return ret;
    }

    vector<int> findDuplicates(vector<int>& nums) {
        auto ret = vector<int>();
        for(int i = 0; i < nums.size(); i++){
            int index = abs(nums[i]) - 1;
            nums[index] = -nums[index];
            if(nums[index] > 0)
                ret.push_back(index + 1);
        }
        return ret;
    }
}


#endif //LEETCODE_CPP_ARRAYSOLUTION_H
