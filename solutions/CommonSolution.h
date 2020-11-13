//
// CommonSolution.h
// leetcode_cpp
// 
// Created by Jeffrey Wang on 16/11/2020.
// Copyright © 2020 eagersoft.io. All rights reserved.
// 

//
// Created by Jeffery Wang on 11/16/20.
//

#ifndef LEETCODE_CPP_COMMONSOLUTION_H
#define LEETCODE_CPP_COMMONSOLUTION_H

#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<map>

namespace CommonSolution {
    int numJewelsInStones(string J, string S) {
        if(J.length() == 0 || S.length() == 0)
            return 0;
        bool *target_table = new bool[123]();
        int res = 0;
        for(auto &j: J)
            target_table[int(j)] = true;
        for(auto &s: S)
            if(target_table[int(s)])
                res++;
        delete[] target_table;
        return res;
    }

    int uniqueMorseRepresentations(vector<string>& words) {
        const vector<string> table = {".-","-...","-.-.","-..",".","..-.","--.","....",
                                      "..",".---","-.-",".-..","--","-.","---",".--.",
                                      "--.-",".-.","...","-","..-","...-",".--","-..-",
                                      "-.--","--.."};
        set<string> res = set<string>();
        for(auto iter = words.begin(); iter != words.end(); iter++){
            string current = "";
            for(auto character: *iter){
                int cInInt = int(character) - 97;
                string morseCode = table[cInInt];
                current += morseCode;
            }
            res.insert(current);
        }
        return int(res.size());
    }

    int arrayPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int res = 0;
        for(int i = 0; i < nums.size(); i += 2){
            res += nums[i];
        }
        return res;
    }

    vector<string> subdomainVisits(vector<string>& cpdomains) {
        auto table = map<string, int>();
        auto res = vector<string>();
        string segment;
        for(auto const &item: cpdomains){
            const auto splitIndex = item.find(' ', 0);
            auto value = stoi(item.substr(0, splitIndex));
            string currentString = item.substr(splitIndex + 1, item.length());
            while(true){
                if(table.find(currentString) == table.end()){   //not found
                    table[currentString] = value;
                }else{    //found
                    table[currentString] += value;
                }
                if(currentString.find('.') != currentString.npos) {
                    auto firstDotIndex = currentString.find('.', 0);
                    auto nextString = currentString.substr(firstDotIndex + 1, currentString.length());
                    currentString = nextString;
                }else{
                    break;
                }
            }
        }
        for(auto const &pairs: table){
            auto resStr = to_string(pairs.second) + " " + pairs.first;
            res.push_back(resStr);
        }
        return res;
    }

    vector<int> numberOfLines(vector<int>& widths, string S) {
        auto lineNeeds = 1;
        auto currentWidth = 0;
        auto res = vector<int>();
        for(auto const &character: S){
            auto cInInt = int(character);
            int widthForCurrentCharacter = widths[cInInt - 97];
            if(currentWidth + widthForCurrentCharacter > 100){
                lineNeeds++;
                currentWidth = widthForCurrentCharacter;
            }else {
                currentWidth += widthForCurrentCharacter;
            }
        }
        res.push_back(lineNeeds);
        res.push_back(currentWidth);
        return res;
    }

    int findComplement(int num) {
        string binNum = bitset<32>(num).to_string();
        string binRes("");
        const int firstOneIndex = int(binNum.find('1', 0));
        for(int i = firstOneIndex; i < binNum.length(); i++){
            binRes += string(binNum[i] == '1' ? "0" : "1");
        }
        int res = stoi(binRes, nullptr, 2);
        return res;
    }

    string toLowerCase(string str) {
        for(int i = 0; i < str.length(); i++){
            if(int(str[i]) <= 90 and int(str[i]) >= 65){
                str[i] += 32;
            }
        }
        return str;
    }

    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
        auto ret = std::vector<std::vector<int>>(A.size(), std::vector<int>(A[0].size()));
        for(auto i = 0; i < A.size(); i++)
            for(auto j = 0; j < A[i].size(); j++)
                ret[i][j] = A[i][A[i].size() - 1 - j] == 1 ? 0 : 1;
        return ret;
    }

    vector<int> finalPrices(vector<int>& prices) {
        auto ret = vector<int>();
        for(int i = 0; i < prices.size(); i++){
            int discount = 0;
            int j = i + 1;
            while(j < prices.size()){
                if(prices[j] <= prices[i]){
                    discount = prices[j];
                    break;
                }
                j += 1;
            }
            ret.push_back(prices[i] - discount);
        }
        return ret;
    }

    vector<int> sortArrayByParity(vector<int>& A) {
        for(int i = 0, j = 0; i < A.size(); i++){
            if(A[i] % 2 == 0){
                swap(A[i], A[j]);
                j++;
            }
        }
        return A;
    }

    int sumOfDigits(vector<int>& A) {
        int min = *min_element(A.begin(), A.end());
        int ret = 0;
        while(min > 0){
            ret += min % 10;
            min /= 10;
        }
        return ret % 2 == 0 ? 1 : 0;
    }

    vector<int> replaceElements(vector<int>& arr) {
        int mx = -1;
        for(int i = arr.size() - 1; i >= 0; i--){
            int temp = arr[i];
            arr[i] = mx;
            mx = max(temp, mx);
        }
        return arr;
    }

    int repeatedNTimes(vector<int>& A) {
        auto table = map<int, int>();
        for(auto a: A) {
            if(table.find(a) != table.end())
                return a;
            else
                table[a] = 1;
        }
        return -1;
    }

    vector<int> diStringMatch(string S) {
        auto ret = vector<int>();
        int max = S.size();
        int min = 0;
        for(char s: S)
            ret.push_back(s == 'I' ? min++ : max--);
        ret.push_back(min);
        return ret;
    }
}


#endif //LEETCODE_CPP_COMMONSOLUTION_H
