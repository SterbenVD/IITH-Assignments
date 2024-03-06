# Smart Exchange: Trading Higher-cost Memory Storage/Access for Lower-cost Computation

Presented in 2020 ACM/IEEE 47th Annual International Symposium on Computer Architecture (ISCA'20)

## Abstract

SmartExchange is an algorithm-hardware co-design framework to trade higher-cost memory storage/access for lower-cost computation. 
This allows for energy-efficient inference of DNNs.

Integrates 3 compression ideas: Pruning, Decomposition, Quantization into a single framework.

Grealty reduces the energy consumption in data movement and storage.

On the hardware level, boosts energy efficieny by 6.7x and reduces latency by 19.2x over state-of-the-art DNN accelerators.

## Introduction

Resource-constrained devices like mobile phones, IoT devices, etc. are unable to run large DNNs due to energy and storage constraints.

How to alleviate heavy data movement?

MAC operations are parallelizable, but incur high energy cost due to data movement. Eg: DianNao consumes 95% of its energy in data movement associated with DRAM access.

In this paper:

Decompose the weight matrixx into product of 2 matrices, that is the Basis matrix and the Coefficient matrix.

Coefficient matrix is sparse, that is, it has a lot of zero elements. It is also readily quantized, that is, the non-zero elements are power-of-2.

This turns the MAC operations into a series of shift and add operations, which are much more energy efficient.

There is $\leq 2$% loss in accuracy.

## Background

### Basics:

Moderns DNNS have CONV, pooling, FC layers.

CONV and FC layers can be described as:

$$ O[c_o][e][f] = \sigma(\sum_{c_i=0}^{C - 1} \sum_{k_r=0}^{R - 1} \sum_{k_s=0 }^{S - 1} W[c_o][c_i][k_r][k_s] \cdot I[c_i][eU + k_r][fU + k_s] + B[c_i]) $$

Where:

- $0 \leq c_o < M$
- $0 \leq e < E$
- $0 \leq f < F$

Here:

- $W$ is the weight matrix
- $I$ is the input matrix
- $B$ is the bias matrix
- $O$ is the output matrix
- $C$ is the number of input channels
- $M$ is the number of output channels
- $E$ is the height of the input
- $F$ is the width of the input
- $R$ is the height of the filter
- $S$ is the width of the filter
- $U$ is the stride
- $\sigma$ is the activation function

DNNs like MobileNet and EfficientNet introduce depthwise CONV layers(Depth wise convolution and Pointwise convolution) and Squeeze-and-Excitation layers.

### Model Compression:

#### Pruning/Sparsity:

Zero out the weights that are below a certain threshold(Near Zero) 

#### Decomposition

Weight Decomposition Low-rank decomposition.

#### Quantization

Reduce the bit width of data thus simplify operations

### Motivation

Data access SRAM take 9.5x more energy than MAC operations. Access of data from DRAM takes 700x more energy than MAC operations.

Rather than enforcing element-wise sparsity on the weight matrix, we can decompose the weight matrix into a product of 2 matrices, that is, the Basis matrix and the Coefficient matrix and then enforce sparsity on the decomposed matrices.

## SmartExchange Problem/Algorithm

This algorithm can be incorportated into the DNN re-training process to achieve more promising trade-offs between accuracy and resource usage.

### Problem Formulation

Let $W \in \mathbb{R}^{M \times N}$ be the weight matrix of a layer in a DNN.

We want to find a decomposition of $W$ into a product of 2 matrices, that is, the Basis matrix $B \in \mathbb{R}^{M \times r}$ and the Coefficient matrix $C _e\in \mathbb{R}^{r \times N}$ such that:

$$ W \approx C_eB $$

Where: $r < \min(M, N)$

The reconstruction error is given by: $|| W - C_eB ||_F^2$

where $||.||_F$ is the Frobenius norm. Frobenius norm is the square root of the sum of the squares of the elements of the matrix.

The set {$C_e, B$} is called the SmartExchange representation of the weight matrix $W$.

Compression Rate = $\frac{\text{Total Bits to store Ce and B}}{\text{Total Bits to store W}}$

### Basis Matrix

The Basis matrix $B$ is a dense matrix and is used to capture the essential information of the weight matrix $W$. It is usually constructed to be very small in size.

### Coefficient Matrix

The Coefficient matrix $C_e$ is a sparse matrix. It is very large in size and has the following properties:

- It has a lot of zero elements: Highly sparse
- It is readily quantized: The non-zero elements are power-of-2

This is different from previous works where quantized values are learned from the training process.

### Objective Function

The problem can be written as a minimization problem:

$$ argmin_{B, C_e} || W - C_eB ||_F^2 $$ 

such that: $\sum_j || C_e[:, j] ||_0 \leq S_c, C_e[i, j] \in \Omega_P, \forall \{i,j\} |P| \leq N_p$

Where:

- $S_c$ is the sparsity constraint, that is, controls the number of non-zero elements in the Coefficient matrix $C_e$
- $N_p$ is the number of power-of-2 values in the Coefficient matrix $C_e$, that is, controls the bit-width required to represent the non-zero elements in the Coefficient matrix $C_e$
- $P$ is an integer set whose cardinality $|P| \leq N_p$
- $\Omega_P$ is the set of power-of-2 values in the set $P$, that is, $\Omega_P = \{2^p | p \in P\}$

### Algorithm

The algorithm is an efficient heuristic algorithm that iterates between objective fitting and feasible set projection.

```
1: Sparsify Ce in a channel-wise manner;
2: Initialize Ce and B; Iteration = 0;
3: while ‖δ (Ce)‖ ≥ tol or iteration < tol maximum:
4: Step 1: Quantize Ce to powers of 2;
5: Step 2: Fitting B and Ce;
6: iteration = iteration + 1;
7: Step 3: Sparsity Ce in a vector-wise manner;
8: Re-quantize Ce and re-fit B.
```

#### Quantizing $C_e$

Projects the nonzero elements in $C_e$ to $\Omega_P$.

Normalize each column in $C_e$ to have a unit norm in order to avoid the scaling ambiguity. ?

Round each non zero element in $C_e$ to the nearest power of 2.

Define $\delta(C_e)$ as the difference between the original $C_e$ and the quantized $C_e$.

#### Fitting $B$ and $C_e$

First fit B by solving $argmin_B || W - C_eB ||_F^2$ and then fit $C_e$ by solving $argmin_{C_e} || W - C_eB ||_F^2$.

#### Sparsifying $C_e$

Introduce both channel-wise and vector-wise sparsity to $C_e$.

Prune channels whose scaling factors in batch normalization layers is lower than a certain threshold(manually set for each layer).

In practice, apply channel sparsity in the first training epoch. It is observed that the channel sparsity does not change much.

Then zero out element in $C_e$ whose absolute value is below a certain threshold($S_c$ which is manually set for each layer).

#### Re-quantizing $C_e$ and re-fitting $B$

Re-quantize $C_e$ and re-fit $B$ with the updated $C_e$.

### Application to DNNs

In all expiriments, $C_e$ is initialized to be $W$ and $B$ is initialized to be $I$. ?

#### Post-training SmartExchange

The value of $r$ is a hyperparameter that needs to be tuned. Remember that $r$ is the rank of the Basis matrix $B$.

Smaller $r$ leads to more aggressive compression and more loss in accuracy.

In practice, where $R \times S$ is the CONV layer kernel size and $R = S$, $r$ is set to be $S$. ?

##### FC Layer

Here, $W \in \mathbb{R}^{M \times C}$, where ?

Reshape each row of $W$ into a 2D matrix $\tilde{W_i} \in \mathbb{R}^{C / S \times S}$. Then apply SmartExchange to $\tilde{W_i}$. If $C$ is not a multiple of $S$, then zero pad the matrix.

When $C >> S$, the reconstruction error might tend to be large due to imbalanced dimensions. To alleviate this, slice $\tilde{W_i}$ into smaller matrices along the first dimension.

##### CONV Layer

Here, $W \in \mathbb{R}^{M \times C \times R \times S}$.

Case 1: $R = S > 1$. Reshape $M$ filters in $W$ into matrices of shape $(S \times C, S)$, on which SmartExchange is applied.
If $S \times C >> S$, then slice the matrix into smaller matrices along the first dimension.

Case 2: $R = S = 1$. Reshape the weight matrix into a 2D matrix of shape $(M, C)$ and apply SmartExchange by treating it as a FC layer.

##### Results

The above procudure is easily parallelizable along the axis of output channels.

When applied on a VGG19 network pre-trained on CIFAR-10, with $\theta = 4 \times 10^{-3}$, $tol = 10^{-10}$, and a maximum iteration of 30, it takes about 30 seconds to perform the algorithm on the network.

Without re-training, there is $3.21$% loss in accuracy and $10x$ overall compression rate.

#### Re-training SmartExchange

After the post-training SmartExchange, the network is re-trained to remedy the accuracy loss.

Since the un-regularized re-training will break the structure of $C_e$, the alternating approach is used, that is:

- Re-training for one epoch
- Apply SmartExchange to ensure $C_e$ structure is maintained

## Smart Exchange Accelerator

SmartExchange's potential cannot be fully exploited by existing DNN accelerators due to the following reasons:

1) Required rebuilding operations to restore weights
2) Coefficient matrix's vector-wise sparsity is not made use of

### Design Principles and Considerations

#### Minimizing Overhead of Rebuilding Weights

To reduce the overhead of rebuilding weights, it is critical to ensure that the location and time of rebuilding units and process is properly designed.

Thus, the SmartExchange accelerator should try to:

1) Store the Basis Matrix $B$ close to the rebuild engine (RE) that restores the weights
2) Place the RE close to or within the processing elements (PE)
3) Use a weight-stationary dataflow for basis matrix

First, the algorithm decomposes the weight matrix $((C \times R) \times S)$ into coefficient matrix $C_e$ of size $(C \times R) \times S$ and basis matrix $B$ of size $S \times S$.

Each element in the basis matrix is reused $C \times R$ times in rebuilding the weights, whereas each element in the coefficient matrix is reused only $S$ times. Thus, the basis matrix should be stored close to the RE and the PEs. It should also be stored in the local memories within REs for minimizing the overhead of data movement.

Second, the RE should be placed close to or within the PEs for minimizing the overhead of data movement costs of rebuilding weights.

Third, the weight-stationary dataflow is used as the basis matrices are reused most frequently. It should stay in PEs until all corresponding elements in the coefficient matrix are rebuilt.

#### Exploiting Vector-wise Sparsity

The SmartExchange algorithm introduces vector-wise sparsity to the coefficient matrix $C_e$. Naturally the corresponding weight vectors in the input tensor are also sparse, which can be used to skip both memory access and computation of the corresponding zero activations. Skipping memory access and computation of zero activations can save energy and reduce latency.

Commonly used methods for encoding weights sparsity, such as run-length coding(RLC), 1-bit direct weight indexing and Compressed Sparse Row(CSR) store both alues and sparsity encoding indexes of weights.

SmartExchange alogrithm's vector-wise sparsity reduces both sparsity encoding indexes and skipping control overheads.

The accelerator can further make use of bit-level and vector-wise sparsity to improve energy efficiency and reduce latency. 

Booth encoding is the most commonly used method for bit-level sparsity. ?

For a compact model like MobileNetV2, the bit-level sparsity is 79.8% under 8bit precision and 66% with 4bit Booth encoding. The vector-wise sparsity is up to 27.1% in last serveral CONV layers with 3x3 kernel size.

Resulting performance improvement is proportional to bit level activation sparsity.

If activations at one row all become zero, fetching the corresponding weight vectors could be skipped.

#### Support for compact models

Compact models like MobileNetV2 and EfficientNet adopt depth-wise CONV and squeeze-and-excitation layers, other than traditional 2D CONV laters, which reduce data reuse opportunities. ?

### SmartExchange Accelerator Architecture

#### Overview

3D PE array with total of $dim_M$ PE slices, input/index/output global buffers associated with an index selector for sparsity and an controller.

Index selector basically check whether the vector is zero-coefficent or not.

The accelerator communicates with an off-chip DRAM through DMA.

The accelerator has the following properties:

1) RE design which is inserted within PE lines to reduce the overhead of rebuilding weights
2) Hybrid dataflow: 1D row stationary datflow is adopted within each PE line for maximizing weight and input reuses, while each PE slice uses an output stationary dataflow for maximizing output partial sum reuses.
3) Index Selector: Selects non-zero coefficient and activation vector pairs. Skips memory access and computation associated with sparse rows of the coefficient matrix and activations.
4) Data-type driven memory partition in order to use matched bandwidths, that is for example, a bigger bandwidth for the weights and a smaller bandwidth for the outputs. This reduces the unit energy cost of SRAM access. There are separated centralized Global buffers to store inputs,outputs, weights and indexes respectively and distributed SRAMs among PEs to store weights(coefficient matrices and basis matrices).
5) Bit-serial multiplier based MAC array in each PE line to make use of the bit-level sparsity together with Booth encoder.

#### PE slices and dataflow

3D PE slice array with $dim_M$ PE slices, where same weight filter is used within each PE slice. ?

Each PE slice has $dim_C$ PE lines where partial sums are accumulated using adder trees. 

A total of $dim_M$ consecutive output channels($dim_M$ weight filters) are processed in parallel to maximize reuse of input activations.

Each PE line includes an array of $dim_F$ MACs, one FIFO (using double buffers), and two REs units, where the REs at the left restore the original weights in a row-wise manner. Each PE line processes one or multiple 1D CONV operations, similar to 1D stationary similar to Eyeriss except now each rebuld weight of one row is streamed temporally along the MACs for processing one row of input activations.

In particular, this 1D CONV operation is repeated to complete one 2D CONV computation in $\leq S \times R$ cycles with:

1) Each weight element is shared among all the MACs in each cycle
2) Intermediate partial sums of 2D CONV are accumulated locally in each MAC unit.

#### RE design

REs contain an RF(register file) of size $S \times S$ to store one basis matrix and a shift-andd-add unit to rebuild weights.

A MUX is used to fetch coefficient matrices, basis matrices or original weights. This allows time divsion to reduce weight bandwidth requirement.

First the basis matrix is fetched and stored in the RF until all the corresponding coefficient matrix elements are fetched and rebuilt.

Original weights are fetched when SmartExchange is not applied.

Computation stalls if the next basis matrix is fetched after finishing the coefficient matrix fetching and current basis matrix used in rebuilding weights.

Leverage the 2 REs in ping-pong manner to avoid stalls.

#### Handling of Compact Models

????

#### Coefficient Matrix Indexing

To encode sparse coefficients:

1) 1-bit direct indexing where 0 represents zero coefficients and 1 represents non-zero coefficients.
2) RLC indexing for number of zero coefficient rows. ?

Since SmartExchange enforces channel-wise sparsity, and then vector-wise sparsity, zero coefficients are clustered within some regions, thus 1-bit direct indexing is used.

#### Buffer Design

Large buffers are required due to unkonwn sparsity patterns.

Row pairs of non-zero input activations and coefficient matrices are selected from the input GB and index GB and then sent to the PE array and output is stored in the output GB.

Input GB: Vanilla design requires $dim_C \times dim_F \times bits_{in} \times input_{rows}$ to be fetched for dealing with dynamic sparsity patterns. ?

In contrast, the design leads to $\geq 1/S$ reduction in required bandwidth, which is $dim_C \times dim_F \times bits_{in}$ inputs every $S +$ "Booth encoded non zero activation bits" cycles 

All FIFOs are implemented in a ping-pong manner using double buffers.

The adopted 1-D row stationary dataflow within each PE line relaxes the bandwidth requirement because each input activation is reused $S$ times.

Bit-serials multipliers take $\geq 1$ cycles to finish element-wise multiplication.

Output/Weight/Index GB: Adopt an FIFO to buffer outputs from each PE slice before writing back to GB, that is, a cache between the PE array and the output GB. Since each output is calculated over several clock cycles. ?

#### Software-Hardware Inference

Deploying the algorithm-based DNN from DL frameworks(PyTorch) into SmartExchange accelerator. A pre-trained model passes through a parser that helps in extracting parameters and layer information, which is then used by the compiler to determine the dataflow and generate sparse index and instructions for configuring PE array, memory data rrangements and runtime scheduling. These instructions are loaded into the accelerator's controller.

## Evaluation

## Related Works
Compression-aware DNN accelerators: 