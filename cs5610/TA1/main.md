---
title: Computational Number Theory - Assignment 1
author: 
- Vishal Vijay Devadiga (CS21BTECH11061)
geometry: margin=1.5cm
documentclass: extarticle
fontsize: 12pt
header-includes:
    - \usepackage{setspace}
    - \onehalfspacing
---

# Question 1

**Find an integer solution of $6x + 10y = 2$**

## Solution

Let $d = gcd(6, 10) = 2$. Then, $2 \mid 2$ and $2 \mid 6$ and $2 \mid 10$. So, $2 \mid 6x + 10y$.

By Bezout's Lemma, there exists $x_0, y_0 \in \mathbb{Z}$ such that $6x_0 + 10y_0 = 2$.

Using the Extended Euclidean Algorithm, we get:

$$ (6x + 6y) + 4y = 2 $$
$$ 6(x + y) + 4y = 2 $$
$$ 6a + 4y = 2 $$

where $a = x + y$.

$$ 2a + 4(a + y) = 2 $$
$$ 2a + 4b = 2 $$

where $b = a + y$.

A simple solution to this equation is $a = 1$ and $b = 0$.
Backtracking, we get:

$$ a = 1, b = 0 $$
$$ y = b - a = \boxed{-1} $$
$$ x = a - y = \boxed{2} $$

Therefore, an integer solution to the given equation is $(x, y) = (2, -1)$.

# Question 2

**Find an integer solution of $6x + 10y + 15z = 1$**

## Solution

Let $d = gcd(6, 10, 15) = 1$. Then, $1 \mid 1$ and $1 \mid 6$ and $1 \mid 10$ and $1 \mid 15$. So, $1 \mid 6x + 10y + 15z$.

By Bezout's Lemma, there exists $x_0, y_0, z_0 \in \mathbb{Z}$ such that $6x_0 + 10y_0 + 15z_0 = 1$.

Using the Extended Euclidean Algorithm, we get:

$$ 6(x + y + z) + 4y + 9z = 1 $$
$$ 6a + 4y + 9z = 1 $$

where $a = x + y + z$.

$$ 2a + 4(a+y+z) + 5z = 1 $$
$$ 2a + 4b + 5z = 1 $$

where $b = a + y + z$.

$$ 2(a+b+z) + 2b + 3z = 1 $$
$$ 2c + 2b + 3z = 1 $$

where $c = a + b + z$.

$$ 2(c+b+z) + z = 1 $$
$$ 2d + z = 1 $$

where $d = c + b + z$.

A simple solution to this equation is $d = 0$ and $z = 1$.
Backtracking, we get:

$$ d = 0, z = 1 $$

# Question 3

**Show that if $a,m,n$ are natural numbers with $a > 1$ then,** $$ gcd(a^m - 1, a^n - 1) = a^{gcd(m,n)} - 1 $$

## Solution

Let $d = gcd(m, n)$. Then, $d \mid m$ and $d \mid n$.

$$ a^m - 1 = a^{dq} - 1 $$
$$ a^n - 1 = a^{dp} - 1 $$

where $q = \frac{m}{d}$ and $p = \frac{n}{d}$.

$$ a^m - 1 = (a^d)^q - 1 $$
$$ a^n - 1 = (a^d)^p - 1 $$

To show that $a*d - 1$ is the greatest common divisor of $a^m - 1$ and $a^n - 1$, 

# Question 4

**Describe all integer solutions of $2x + 3y + 5z = 0$**

## Solution

