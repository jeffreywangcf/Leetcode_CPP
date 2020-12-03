//
// main.rs
// leetocde_rust
//
// Created by Jeffrey Wang on 28/10/2020.
// Copyright © 2020 eagersoft.io. All rights reserved.
//


mod solutions;
mod structure;


#[allow(dead_code)]
fn main() {
    let _testcase: Vec<Vec<i32>> = vec![
        vec![1, 2, 3],
        vec![4, 5, 6],
        vec![7, 8, 9],
    ];
    let _test_str = String::from("abcabcabc");
    let result = solutions::Solutions::generate_the_string(10);
    println!("{}", result);

}