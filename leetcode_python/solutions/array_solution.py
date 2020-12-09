#
# array_solution.py
# leetcode_python
# 
# Created by Jeffrey Wang on 07/12/2020.
# Copyright © 2020 eagersoft.io. All rights reserved.
#

from collections import Counter
import sys


def minWindow(s: str, t: str) -> str:
    table = Counter(t)
    cur_table = Counter()
    lower = upper = 0
    best_lower = 0
    best_upper = len(s)

    for upper, char in enumerate(s):
        cur_table[char] += 1
        while cur_table & table == table:
            if upper - lower < best_upper - best_lower:
                best_upper = upper
                best_lower = lower
            cur_table[s[lower]] -= 1
            lower += 1

    if best_upper - best_lower < len(s):
        return s[best_lower:best_upper + 1]
    return ""


def isPalindrome(s: str) -> bool:
    lower = 0
    upper = len(s) - 1
    while lower < upper:
        if not s[lower].isalnum():
            lower += 1
        elif not s[upper].isalnum():
            upper -= 1
        else:
            if s[lower].lower() != s[upper].lower():
                return False
            lower += 1
            upper -= 1
    return True