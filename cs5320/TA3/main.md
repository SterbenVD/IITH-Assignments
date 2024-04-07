---
title: CS5320 Theory Assignment - 3
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

## Early-stopping algorithm for Consensus under Crash Failures

Modify the Consensus Algorithm for Crash Failures (synchronous system) to terminate within $f + 1$ rounds when the actual number of stop-failures ($f_a$) is lower the f.

The Algorithm gives a consensus algorithm for $n$ processes, where up to $f$ processes, where $f < n$, may fail in the fail-stop model.
Here, the consensus variable $x$ is integer-valued. Each process has an initial value $x_i$.

If up to $f$ failures are to be tolerated, then the algorithm has f + 1 rounds.

Modify this algorithm to include an early stopping mechanism where the algorithm terminated when the actual number of stop failures $f_a$ is less then $f$.

## Solution

# Question 2

## Generalizing the Consensus Problem with binary inputs to work with multi-valued inputs

Assume that you have a solution to the Consensus Problem problem that works with binary inputs.

Can you use this to solve the Consensus Problem to work with multi-valued inputs.

## Solution
