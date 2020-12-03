//
// parking_system.rs
// leetcode_rust
// 
// Created by Jeffrey Wang on 28/10/2020.
// Copyright © 2020 eagersoft.io. All rights reserved.
// 


pub struct ParkingSystem {
    pub spaces: Vec<i32>
}

#[allow(dead_code)]
impl ParkingSystem {

    pub fn new(big: i32, medium: i32, small: i32) -> Self {
        Self{
            spaces: vec![big, medium, small]
        }
    }

    pub fn add_car(&mut self, car_type: i32) -> bool {
        if self.spaces[(car_type - 1) as usize] > 0{
            self.spaces[(car_type - 1) as usize] -= 1;
            return true;
        }
        return false;
    }
}