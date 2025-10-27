[TOC]

# Assignment1

| Expression     | How to Say It                     | Common Meaning    |
| :------------- | :-------------------------------- | :---------------- |
| **O(1)**       | “Big O of one”                    | Constant time     |
| **O(log n)**   | “Big O of log n”                  | Logarithmic time  |
| **O(n)**       | “Big O of n”                      | Linear time       |
| **O(n log n)** | “Big O of n log n”                | Linearithmic time |
| **O(n²)**      | “Big O of n squared”              | Quadratic time    |
| **O(n³)**      | “Big O of n cubed”                | Cubic time        |
| **O(2ⁿ)**      | “Big O of two to the n”           | Exponential time  |
| **O(n!)**      | “Big O of n factorial”            | Factorial time    |


## Task-1

| Line | Operation                                | Count       |
| ---- | ---------------------------------------- | ----------- |
| 1    | `currentMin ← A[0]`                      | 1           |
| 2    | `i ← 1`                                  | 1           |
| 3    | `while i ≤ n − 1 do`                     | n           |
| 4    | `if currentMin ≥ A[i] then`              | n - 1       |
| 5    | `currentMin ← A[i]`                      | up to n - 1 |
| 6    | `i ← i + 1`                              | n - 1       |
| 7    | `return currentMin`                      | 1           |

Q: Why does the while condition (`while i <= n-1 do`) execute $n$ times, while the loop body only executes $n-1$ times?

A: The while loop's condition is always checked one final time to determine that it is `false` and the loop must stop

### Best Case

Example: An array sorted in ascending order like [1, 2, 3, 4, 5]

The best case occurs when the if condition on Line 4 (`if currentMin ≥ A[i] then`) is always `false`

$1 + 1 + n + (n-1) + 0 + (n-1) + 1 = {3n + 1}$

Big-O: $O(n)$

### Worst Case

Example: An array sorted in descending order like [5, 4, 3, 2, 1]

The worst case occurs when the if condition on Line 4 (`if currentMin ≥ A[i] then`) is always `true`

$1 + 1 + n + (n-1) + (n-1) + (n-1) + 1 = {4n}$

Big-O: $O(n)$

## Task-2 find the dominant term

### a)

Expand the expression: $2 + 2n + 3n^2$

Big-O: $O(n^2)$

### b)

Expand the expression: $8n^2 + 1.5n$

Big-O: $O(n^2)$

### c)

Divide both terms by $n \log n$

$\frac{n^3 \log n}{n \log n} = n^2$

$\frac{n (\log n)^2}{n \log n} = \log n$

$n^2$ grows faster than $\log n$

Big-O: $O(n^3 \log n)$

## Task-3

### a)

Big-O: $O(n)$

### b)

This is a nested loop

The outer loop runs $n$ times

This inner loop runs $n$ time

Big-O: $O(n^2)$

### c)

* When $i = n$, inner loop runs 1 time ($j=n$)
* When $i = n-1$, inner loop runs 2 times ($j=n-1, n$)
* ...
* When $i = 1$, inner loop runs $n$ times ($j=1, ..., n$)

The total number of operations is the sum $1 + 2 + 3 + ... + n$

This sum is $\frac{n(n+1)}{2}$

Big-O: $O(n^2)$

### d)

The inner loop for (j = i; j <= i; j++) only runs one time when $j=i$

The outer loop runs $n$ times

This inner loop runs 1 time

Big-O: $n \times 1 = O(n)$

### e)

The outer loop runs $n$ times

This inner loop runs $\log n$ times since it is repeatedly divided by 2

Big-O: $n \times O(\log n) = O(n \log n)$

### f)

This is a recursive function with n recursive calls, so the time complexity is $O(n)$

Due to recursion stack, space complexity is also $O(n)$

Time Big-O: $O(n)$
Space Big-O: $O(n)$