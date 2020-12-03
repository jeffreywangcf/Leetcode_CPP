//
// solutions.rs
// leetocde_rust
// 
// Created by Jeffrey Wang on 28/10/2020.
// Copyright © 2020 eagersoft.io. All rights reserved.
//

#[allow(unused_imports)]
use std::collections::{BTreeMap, BinaryHeap, HashSet, HashMap};
use std::hash::Hash;

pub struct Solutions{

}

#[allow(dead_code)]
impl Solutions{
    pub fn min_time_to_visit_all_points(points: Vec<Vec<i32>>) -> i32 {
        let mut ret = 0;
        for i in 0..points.len() - 1{
            let dx = (points[i+1][0] - points[i][0]).abs();
            let dy = (points[i+1][1] - points[i][1]).abs();
            ret += dx + dy - std::cmp::min(dx, dy);
        }
        return ret;
    }

    pub fn sum_odd_length_subarrays(arr: Vec<i32>) -> i32 {
        let mut ret: i32 = 0;
        for length in (1..arr.len() + 1).step_by(2){
            let mut start = 0;
            while start + length <= arr.len(){
                let cur_arr = &arr[start..start+length];
                ret += cur_arr.iter().sum::<i32>();
                start += 1;
            }
        }
        return ret;
    }

    pub fn high_five(items: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let mut table = BTreeMap::new();
        let mut ret: Vec<Vec<i32>> = Vec::new();
        for item in items {
            let heap = table.entry(item[0]).or_insert(BinaryHeap::new());
            heap.push(item[1]);
        }
        for (id, scores) in table.iter_mut(){
            let mut sum = 0;
            for _ in 0..5{
                sum += scores.pop().unwrap();
            }
            ret.push(vec![*id, (sum / 5_i32) as i32])
        }
        return ret;
    }

    pub fn count_good_triplets(arr: Vec<i32>, a: i32, b: i32, c: i32) -> i32 {
        let mut ret = 0;
        for i in 0..arr.len(){
            for j in i+1..arr.len(){
                for k in j+1..arr.len(){
                    if (arr[i] - arr[j]).abs() <= a && (arr[j] - arr[k]).abs() <= b
                        && (arr[i] - arr[k]).abs() <= c{
                        ret += 1;
                    }
                }
            }
        }
        return ret;
    }

    pub fn arrays_intersection(arr1: Vec<i32>, arr2: Vec<i32>, arr3: Vec<i32>) -> Vec<i32> {
        let mut i = 0;
        let mut j = 0;
        let mut k = 0;
        let len= arr1.len();
        let mut ret = vec![];
        while i < len && j < len && k < len{
            if arr1[i] == arr2[j] && arr2[j] == arr3[k]{
                ret.push(arr1[i]);
                i += 1;
                j += 1;
                k += 1;
                continue;
            }
            let max= std::cmp::max(std::cmp::max(arr1[i], arr2[j]), arr3[k]);
            while i < len && arr1[i] < max{
                i += 1;
            }
            while j < len && arr2[j] < max{
                j += 1;
            }
            while k < len && arr3[k] < max{
                k += 1;
            }
        }
        return ret;
    }

    pub fn diagonal_sum(mat: Vec<Vec<i32>>) -> i32 {
        let mut ret = 0;
        for i in 0..mat.len(){
            ret += mat[i][i];
            ret += mat[i][mat.len() - i - 1];
        }
        if mat.len() % 2 == 1{
            ret -= mat[mat.len() / 2][mat.len() / 2];
        }
        return ret;
    }

    pub fn remove_outer_parentheses(s: String) -> String {
        let mut ret = String::new();
        let mut flag = 0;
        for i in 0..s.len(){
            if "(".eq(&s[i..i+1]){
                if flag > 0{
                    ret += "(";
                }
                flag += 1;
            }else {
                // current char: ")"
                if flag > 1{
                    ret += ")";
                }
                flag -= 1;
            }
        }
        return ret;
    }

    pub fn is_armstrong(n: i32) -> bool {
        let mut nn = n;
        let mut sum = 0;
        let mut nums: Vec<i32> = Vec::new();
        while nn > 0{
            nums.push(nn % 10);
            nn /= 10;
        }
        for num in &nums{
            sum += num.pow(nums.len() as u32);
        }
        return sum == n;
    }

    pub fn maximum69_number(num: i32) -> i32 {
        let mut n = num;
        let mut numbers: Vec<i32> = Vec::new();
        while n > 0{
            numbers.push(n % 10);
            n /= 10;
        }
        let mut ret = num;
        for to_flip in 0..numbers.len(){
            let mut sum: i32 = 0;
            for i in 0..numbers.len(){
                if i == to_flip{
                    sum += 10_i32.pow(i as u32) * if numbers[i] == 9 {6} else {9};
                }else{
                    sum += 10_i32.pow(i as u32) * numbers[i];
                }
            }
            if sum > ret{
                ret = sum;
            }
        }
        return ret;
    }

    pub fn busy_student(start_time: Vec<i32>, end_time: Vec<i32>, query_time: i32) -> i32 {
        let mut ret = 0;
        for i in 0..start_time.len(){
            if start_time[i] <= query_time && query_time <= end_time[i]{
                ret += 1;
            }
        }
        return ret;
    }

    pub fn dest_city(paths: Vec<Vec<String>>) -> String {
        let mut set: HashSet<String> = HashSet::new();
        for path in paths.iter(){
            set.insert(path[0].clone());
        }
        for path in paths.iter(){
            if !set.contains(&path[1]){
                return path[1].clone();
            }
        }
        return String::new();
    }

    pub fn count_letters(s: String) -> i32 {
        let str = String::from(" ") + &s + &String::from(" ");
        let mut ret = 0;
        let mut count = 1;
        for i in 1..str.len() - 1 {
            if str.chars().nth(i) == str.chars().nth(i - 1) {
                count += 1
            } else {
                count = 1
            }
            ret += count;
        }
        return ret;
    }

    pub fn sum_zero(n: i32) -> Vec<i32> {
        let mut ret: Vec<i32> = Vec::new();
        if n % 2 == 1 {
            ret.push(0);
        }
        let mut count = 1;
        while ret.len() != n as usize {
            ret.push(count);
            ret.push(-count);
            count += 1;
        }
        return ret;
    }

    pub fn max_product(nums: Vec<i32>) -> i32 {
        let mut n1 = -1;
        let mut n2 = -1;
        for num in nums{
            if num > n1{
                n2 = n1;
                n1 = num;
            }else if num > n2{
                n2 = num;
            }
        }
        return (n1 - 1) * (n2 - 1);
    }

    pub fn generate_the_string(n: i32) -> String {
        if n % 2 == 1{
            return "a".repeat(n as usize);
        }
        let leading: String = "a".repeat((n - 1) as usize);
        return leading + "b";
    }

    pub fn count_negatives(grid: Vec<Vec<i32>>) -> i32 {
        let mut ret = 0;
        for line in grid.iter(){
            for i in (0..line.len()).rev(){
                if line[i] >= 0{
                    break;
                }
                ret += 1;
            }
        }
        return ret;
    }
}