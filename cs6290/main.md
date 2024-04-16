# Streaming Algorithm for Graph Spanners - Single Pass and Constant Processing Time per Edge

## Table of Contents
- [Streaming Algorithm for Graph Spanners - Single Pass and Constant Processing Time per Edge](#streaming-algorithm-for-graph-spanners---single-pass-and-constant-processing-time-per-edge)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Algorithm](#algorithm)
    - [Forming the initial $k$ clusters](#forming-the-initial-k-clusters)
      - [Analysis](#analysis)
    - [Overview of the algorithm](#overview-of-the-algorithm)
    - [Processing an edge $(u, v)$](#processing-an-edge-u-v)
    - [Prune(u,i)](#pruneui)
    - [Time Complexity](#time-complexity)
    - [Analysis](#analysis-1)
      - [Stretch of the spanner](#stretch-of-the-spanner)
  - [Conclusion](#conclusion)

\newpage

## Introduction

Spanner: Sparse subgraph that approximately preserves all pairwise distances

$\alpha$-spanner:  Graph $G$ such that for every pair of vertices $u, v \in V$, the distance between $u$ and $v$ in $G$ is at most $\alpha$ times the distance between $u$ and $v$ in $G^*$, where $G^*$ is the original graph

$\alpha$: the stretch factor

Computing the smallest $\alpha$ spanner is NP-hard.

Streaming model: The input graph is given as a stream of edges, and the algorithm processes the edges one by one.

Cluster: Subset of vertices.

Clustering: Union of disjoint clusters

Algorithm below: Single pass, amortized constant processing time per edge, and produces a $(2k-1)$-spanner of expected size $O(kn^{1 + 1/k})$.

Center: A unique vertex that is the center of a cluster.

## Algorithm

The algorithm at each stage will maintain a $(2k-1)$-spanner of the graph induced by the edges seen so far.

Thus, the algorithm can be thought of as a partial dynamic, that is, incremental algorithm.

Idea of the algorithm is to find a suitable clustering.

Let $\mathcal{C}[v]$ denote the centre of cluster containing $v$. If $v$ is a center, then $\mathcal{C}[v] = v$ and if $v$ is not in a cluster, then $\mathcal{C}[v] = 0$.

A cluster $c$ is said to be adjacent to a vertex $u$ if there is an edge between $u$ and $v$ such that $v \in c$.

### Forming the initial $k$ clusters

- $S_0 \leftarrow V ; S_k \leftarrow \emptyset$

- For $i \in \{1, \ldots, k-1\}$:
    - $S_i$ is formed by selecting each vertex $v \in S_{i-1}$ independently with probability $n^{-1/k}$.
- For (each $v \in V$ and $i \in \{0, 1, \ldots, k-1\}$):  
    - If $v \in S_i$, then
        - $\mathcal{C_i}[v] \leftarrow v$
    - Else
        - $\mathcal{C_i}[v] \leftarrow 0$

#### Analysis

Let $l_c(v)$ be the highest level $i < k$ such that $v$ appears as center in some cluster in $C_i$.

For each cluster in $C_i$, is a singleton set storing only its center, and a small fraction of cluster centers are selected randomly to be centers of the next level.

For each cluster $c'$ in $C_{i+1}$, there exists a unique sampled cluster c at level $i$ such that $c \subseteq c'$ and vice versa.

A cluster $c$ at is a sampled cluster at level $i$ if and only if $c$ is a subset of a cluster at level $i+1$, that is, its center is a center of a cluster at level $i+1$.

### Overview of the algorithm

Let $l(u) denote the highest level such that $u$ appears as a member of some cluster in $C_i$.

$l(u)$ is initialized to $l_c(u)$ for each $u \in V$.

Each vertex $u \in V$ waits at its present level $l(u)$ for an opportunity to move to a higher level.

When an edge $(u, v)$ is processed, let $l(u) \leq l(v)$ without loss of generality.

Let $c$ be the cluster containing $v$ at level $l(u)$. $c'$ be the cluster containing $c$ at level $l(u) + 1$. $u$ adds the edge to the spanner, moves to level $l(u) + 1$, and becomes a member of $c'$. If $c'$ is also a sampled cluster, then $u$ moves to level $l(u) + 2$ and so on.

Data structures:

- $l_c(v)$: Level of the cluster containing $v$. Initially, $l_c(v) = 0$ for each $v \in V$. After forming the initial $k$ clusters, $l_c(v) = i$ if $v$ is a member of a cluster at level $i$.
- $l(u)$: Level of vertex $u$. Initially, $l(u) = l_c(u)$ for each $u \in V$.
- $k$ arrays $\mathcal{C_i}$, each has a max size of $n$.
- $\epsilon(u)$: One edge per unsampled cluster at level $l(u)$ which is adjacent to $u$.
- $Temp(u)$: Temporary storage for edges adjacent to $u$ that are not yet processed. Pruned once the number of edges in $Temp(u)$ equals the number of edges in $\epsilon(u)$.
- $\epsilon_S$: Set of edges in the spanner.
- $A$: Array to keep track of edges that are pruned.

Note that for each vertex $u \in V$, $|Temp(u)| < |\epsilon(u)|$ always, except just before pruning when $|Temp(u)| = |\epsilon(u)|$.

### Processing an edge $(u, v)$

- If $l(u) > l(v)$, swap $u$ and $v$.
- $i \leftarrow l(u)$
- $x \leftarrow \mathcal{C_i}[v]$
- $h \leftarrow l_c(x)$
- If $h > i$, then
  - For $j \in \{i+1, i+2, \ldots, h\}$:
    - $C_j[u] \leftarrow x$
  - l(u) $\leftarrow h$
  - $\epsilon_S \leftarrow \epsilon_S \cup Temp(u) \cup \epsilon (u)$
  - $Temp(u) \leftarrow \emptyset$
  - $\epsilon(u) \leftarrow \{ (u,v) \}$
- Else
  - $Temp(u) \leftarrow Temp(u) \cup \{ (u,v) \}$ 
  - If $|Temp(u)| = |\epsilon (u)|$, Prune(u,i)

### Prune(u,i)

- For each $(u, w) \in \epsilon(u)$, $A[\mathcal{C_i}[w]] \leftarrow 1$
- For each $(u, v) \in Temp(u)$,
  - If $A[\mathcal{C_i}[v]] = 0$
    - $A[\mathcal{C_i}[v]] \leftarrow 1$
    - $\epsilon(u) \leftarrow \epsilon(u) \cup \{ (u,v) \}$
  - $Temp(u) \leftarrow Temp(u) \setminus \{ (u,v) \}$
- For each $(u, w) \in \epsilon(u)$, $A[\mathcal{C_i}[w]] \leftarrow 0$

### Time Complexity

### Analysis

We define two sets of edges:

- $\epsilon^+$ = $\bigcup_{u \in V} \epsilon(u) \cup \epsilon_S$
- $Temp$ = $\bigcup_{u \in V} Temp(u)$

#### Stretch of the spanner

**Lemma**: Let $c'$ be any cluster in $C_i$. Each vertex $u \in c'$ is connected to its center $v$ by a path of length at most $i$ edges from $\epsilon^+$

**Proof**: By induction on i.

Let $v$ be the center of $c'$ and $u \in c'$. If $i = 0$, that is, $c'$ is a singleton cluster, then $u = v$ and the claim is trivially true.

Let $u \not= v$. $u$ became member of $c'$ in this method: $u$ was a member of a cluster $c$ at some lower levle and an edge $(u, w)$ was processed such that $w$ belonged to $c'$. By induction hypothesis, $w$ is connected to $v$ by a path of length at most $i-1$ edges. Thus, $u$ is connected to $v$ by a path of length at most $i$ edges since the edge $(u, w)$ is added to $\epsilon(u)$. 

**Lemma**: The expected stretch of the spanner is at most $2k-1$.

**Proof**: Any any stage of the algorithm, let $(u,v)$ be an edge that appeared in the stream.

If the edge is added to the spanner, then distance between $u$ and $v$ is the same as the original graph.

If the edge is not added to the spanner, that is, it was pruned at level $i$, then $u$ and $w$ is connected in the spanner such that $w$ and $v$ are part of the same cluster at level $i$. Thus, the distance between $u$ and $v$ is at most $2i+1$ as per the previous lemma(path between $u,w,x,v$).

As $i < k$, the expected stretch of the spanner is at most $2k-1$.

\newpage

## Conclusion

Given any $k \in \mathbb{N}$, a $(2k−1)$-spanner of expected size $O(min(m, kn^{1+1/k}))$ for an unweighted graph can be computed in streaming model in one pass with $O(m)$ time to process the entire stream. 

The working memory required is $O(kn^{1+1/k})$.