---
title: CS6490 Assignment 2
author: 
- Vishal Vijay Devadiga (CS21BTECH11061)
geometry: margin=1.5cm
documentclass: extarticle
fontsize: 12pt
header-includes:
    - \usepackage{setspace}
    - \onehalfspacing
---

- [A short summary on Scale-Sim](#a-short-summary-on-scale-sim)
  - [Introduction](#introduction)
  - [Implementation Details](#implementation-details)
- [Metrics and Results](#metrics-and-results)
  - [Q3: Analyzing the impact of different DNNs and configurations](#q3-analyzing-the-impact-of-different-dnns-and-configurations)
    - [Mapping Efficiency and Compute Utilization](#mapping-efficiency-and-compute-utilization)
    - [Total Runtime](#total-runtime)
    - [DRAM Bandwidth Utilization and Read/Writes](#dram-bandwidth-utilization-and-readwrites)
    - [SRAM Bandwidth Utilization and Read/Writes](#sram-bandwidth-utilization-and-readwrites)
  - [Changing dataflows](#changing-dataflows)
    - [Total Runtime](#total-runtime-1)
    - [Mapping Efficiency and Compute Utilization](#mapping-efficiency-and-compute-utilization-1)
    - [DRAM Bandwidth Utilization and Read/Writes](#dram-bandwidth-utilization-and-readwrites-1)
    - [SRAM Bandwidth Utilization and Read/Writes](#sram-bandwidth-utilization-and-readwrites-1)
  - [Changing buffer sizes](#changing-buffer-sizes)
    - [DRAM Bandwidth Utilization and Read/Writes](#dram-bandwidth-utilization-and-readwrites-2)
  - [Changing systolic array sizes](#changing-systolic-array-sizes)
    - [Total Runtime](#total-runtime-2)
    - [DRAM Bandwidth Utilization and Read/Writes](#dram-bandwidth-utilization-and-readwrites-3)
- [References](#references)

\newpage

# A short summary on Scale-Sim

## Introduction

**Scale-Sim: SystoliC AcceLErator SIMulator**

Scale-Sim is a cycle accurate simulator for DNN inference on systolic arrays.

It serves to explore both scale-up (increasing compute units) and scale-out (adding more chips) models, enabling the investigation of various systolic array architectures with different memory hierarchies, runtime behaviors, dataflows, and DRAM bandwidth requirements.

The simulator comprises two key components:

- Compute Unit: This unit is based on a parameterized systolic array, with size and aspect ratio as configurable parameters.
- Accelerator Memory System: It includes three double-buffered SRAM memories of specified sizes, dedicated to buffering matrices for two operands and one result.

Before initiating the simulation, Scale-Sim requires three inputs:

- Configuration File: This file outlines the parameters of the systolic array, memory system, dataflow, and DRAM bandwidth.
- Architecture File: It specifies all layers in the DNN along with their respective parameters.
- Logging Path: This path designates where the simulation results will be stored.

![Reference: [Scale - Sim Paper](https://ieeexplore.ieee.org/document/9238602)](./scalesim.png)

## Implementation Details

The simulator operates under the following assumptions:

- The accelerator is consistently compute-bound.
- Processing elements (PEs) are maximally utilized.

It generates cycle-accurate read addresses for elements to ensure uninterrupted operation of the PE array. The resulting output trace includes SRAM write traffic for the output matrix. The simulator analyzes this traffic to calculate the total runtime and assesses array utilization on a per-cycle basis.

Both input matrices and generated elements are managed by dedicated SRAM buffers using a double-buffered mechanism. By parsing SRAM traces, the simulator optimizes the filling of these buffers to prevent any SRAM request from encountering a miss.

DRAM traces, which comprise prefetch requests to SRAM, inform the estimation of interface bandwidth requirements. Further parsing of trace data at both the SRAM and interface levels allows for the determination of compute efficiency and other relevant metrics.

\newpage

# Metrics and Results

![Reference: [Scale - Sim Paper](https://ieeexplore.ieee.org/document/9238602)](./data_flow.png)

![Reference: [Scale - Sim Paper](https://ieeexplore.ieee.org/document/9238602)](./runtime_model.png)

$S_R$ is spatial row, $S_C$ is spatial column. 
$T$ is the number of timesteps.

$N_{ofmap}$ is the number of OFMAP pixels generated by the filter. 

$W_{CONV}$ is number of partial sums generated per output pixel.

$N_{filter}$ is the number of convolutional filters.


If the size of the array is $R \times C$, then the folds are defined as:

- $F_R = \lceil \frac{S_R}{R} \rceil$
- $F_C = \lceil \frac{S_C}{C} \rceil$

Also, $T_F = 2R + C + T - 2$.

Thus, total runtime is $T_F \times F_R \times F_C$.

Note that $N_{ofmap}$ is quite large.

The following metrics were used to analyze the experiments:

- Mapping Efficiency
- Compute Utilization
- DRAM Bandwidth Utilization for Input, Filter, and Output
- SRAM Bandwidth Utilization for Input, Filter, and Output
- DRAM Reads and Writes for Input, Filter, and Output
- SRAM Reads and Writes for Input, Filter, and Output

Overall around 167 graphs were generated for the above metrics.

Mapping Efficiency is defined as Utilized PEs / Total PEs per **iteration**. Thus it is a measure of how well the systolic array is utilized per iteration. 

Compute Utilization is defined as Utilized PEs / Total PEs per **cycle**. Thus it is a measure of how well the systolic array is utilized per cycle.

\newpage
<!--  All graphs are of path "./graph/Q[1-4]/[DNN]_[Metric].png" -->
## Q3: Analyzing the impact of different DNNs and configurations

Six different DNNs were used: mobilenet, resnet18, alexnet, googlenet, fasterRCNN, and yolo_tiny.

Three different configurations were used: eyeriss, googleTPU, and scale.

All the DNNs were run on all the configurations.

### Mapping Efficiency and Compute Utilization

Mapping utilization depends on $S_R, S_C, R, C$.

Compute utilization depends on $S_R, S_C, R, C, T$.

\newpage

![mobilenet_mapping](./graph/Q1/mobilenet_mapping_efficiency.png)

For mobilenet, the mapping efficiency alternates between big and small values due to the number of filters. The pattern of number of filters in mobilenet is like 32, 1, 64, 1, 128, 1, ... and so on. This causes the mapping efficiency to alternate between big and small values since the number of filters is the main factor in determining the mapping efficiency in OS and WS dataflows.

![mobilenet_compute](./graph/Q1/mobilenet_compute_util.png)

We see a similar order in compute utilization as well.

The graph for GoogleTPU is lower in magnitude due to the fact that the systolic array is larger in GoogleTPU than in eyeriss and scale.

\newpage

![resnet18_mapping](./graph/Q1/Resnet18_mapping_efficiency.png)

![resnet18_compute](./graph/Q1/Resnet18_compute_util.png)

A similar order is observed in resnet18 as well.

\newpage

![fasterRCNN_mapping](./graph/Q1/FasterRCNN_mapping_efficiency.png)

![fasterRCNN_compute](./graph/Q1/FasterRCNN_compute_util.png)

A similar order is observed in fasterRCNN as well.

\newpage

![alexnet_mapping](./graph/Q1/alexnet_mapping_efficiency.png)

![alexnet_compute](./graph/Q1/alexnet_compute_util.png)

A similar order is observed in alexnet as well.

\newpage

![googlenet_mapping](./graph/Q1/Googlenet_mapping_efficiency.png)

![googlenet_compute](./graph/Q1/Googlenet_compute_util.png)

A similar order is observed in googlenet as well.

\newpage

![yolo_tiny_mapping](./graph/Q1/yolo_tiny_mapping_efficiency.png)

![yolo_tiny_compute](./graph/Q1/yolo_tiny_compute_util.png)

A similar order is observed in yolo_tiny as well.

\newpage

### Total Runtime

The total runtime is calculated as $T_F \times F_R \times F_C$.

Thus it depends on $S_R, S_C, R, C, T$.

![mobilenet_runtime](./graph/Q1/mobilenet_total_cycles.png)

We can see that the total runtime is highest for eyeriss and lowest for GoogleTPU. This is because the systolic array is larger in GoogleTPU than in eyeriss and scale,

![resnet18_runtime](./graph/Q1/Resnet18_total_cycles.png)

A similar order is observed in resnet18 as well.

\newpage

![fasterRCNN_runtime](./graph/Q1/FasterRCNN_total_cycles.png)

A similar order is observed in fasterRCNN as well.

![alexnet_runtime](./graph/Q1/alexnet_total_cycles.png)

A similar order is observed in alexnet as well.

\newpage

![googlenet_runtime](./graph/Q1/Googlenet_total_cycles.png)

A similar order is observed in googlenet as well.

![yolo_tiny_runtime](./graph/Q1/yolo_tiny_total_cycles.png)

A similar order is observed in yolo_tiny as well.

\newpage

### DRAM Bandwidth Utilization and Read/Writes

![mobilenet_ifmap_dram_bw](./graph/Q1/mobilenet_%20Avg%20IFMAP%20DRAM%20BW.png)

![mobilenet_DRAM_IFMAP_READS](./graph/Q1/mobilenet_%20DRAM%20IFMAP%20Reads.png)

Since the eyeriss configuration has the smallest systolic array, the number of reads of input DRAM is the largest for eyeriss and the number of reads is the smallest for GoogleTPU. 

The bandwidth is the largest for scale because of its dataflow.

\newpage

![mobilenet_filter_dram_bw](./graph/Q1/mobilenet_%20Avg%20FILTER%20DRAM%20BW.png)

![mobilenet_DRAM_Filter_READS](./graph/Q1/mobilenet_%20DRAM%20Filter%20Reads.png)

The number of reads and bandwidth of filter DRAM is the largest for scale because of its dataflow.

\newpage

![mobilenet_ofmap_dram_bw](./graph/Q1/mobilenet_%20Avg%20OFMAP%20DRAM%20BW.png)

![mobilenet_DRAM_OFMAP_WRITES](./graph/Q1/mobilenet_%20DRAM%20OFMAP%20Writes.png)

Since the eyeriss configuration has the smallest systolic array, the number of writes of output DRAM is the largest for eyeriss and the number of writes is the smallest for GoogleTPU.

Also the bandwidth is the largest for GoogleTPU because of its systolic array.

\newpage

Similar orders are observed in resnet18, fasterRCNN, alexnet, googlenet, and yolo_tiny.

![resnet18_ifmap_dram_bw](./graph/Q1/Resnet18_%20Avg%20IFMAP%20DRAM%20BW.png)

![resnet18_DRAM_IFMAP_READS](./graph/Q1/Resnet18_%20DRAM%20IFMAP%20Reads.png)

\newpage

![resnet18_filter_dram_bw](./graph/Q1/Resnet18_%20Avg%20FILTER%20DRAM%20BW.png)

![resnet18_DRAM_Filter_READS](./graph/Q1/Resnet18_%20DRAM%20Filter%20Reads.png)

\newpage

![resnet18_ofmap_dram_bw](./graph/Q1/Resnet18_%20Avg%20OFMAP%20DRAM%20BW.png)

![resnet18_DRAM_OFMAP_WRITES](./graph/Q1/Resnet18_%20DRAM%20OFMAP%20Writes.png)

\newpage

![fasterRCNN_ifmap_dram_bw](./graph/Q1/FasterRCNN_%20Avg%20IFMAP%20DRAM%20BW.png)

![fasterRCNN_DRAM_IFMAP_READS](./graph/Q1/FasterRCNN_%20DRAM%20IFMAP%20Reads.png)

\newpage

![fasterRCNN_filter_dram_bw](./graph/Q1/FasterRCNN_%20Avg%20FILTER%20DRAM%20BW.png)

![fasterRCNN_DRAM_Filter_READS](./graph/Q1/FasterRCNN_%20DRAM%20Filter%20Reads.png)

\newpage

![fasterRCNN_ofmap_dram_bw](./graph/Q1/FasterRCNN_%20Avg%20OFMAP%20DRAM%20BW.png)

![fasterRCNN_DRAM_OFMAP_WRITES](./graph/Q1/FasterRCNN_%20DRAM%20OFMAP%20Writes.png)

\newpage

![alexnet_ifmap_dram_bw](./graph/Q1/alexnet_%20Avg%20IFMAP%20DRAM%20BW.png)

![alexnet_DRAM_IFMAP_READS](./graph/Q1/alexnet_%20DRAM%20IFMAP%20Reads.png)

\newpage

![alexnet_filter_dram_bw](./graph/Q1/alexnet_%20Avg%20FILTER%20DRAM%20BW.png)

![alexnet_DRAM_Filter_READS](./graph/Q1/alexnet_%20DRAM%20Filter%20Reads.png)

\newpage

![alexnet_ofmap_dram_bw](./graph/Q1/alexnet_%20Avg%20OFMAP%20DRAM%20BW.png)

![alexnet_DRAM_OFMAP_WRITES](./graph/Q1/alexnet_%20DRAM%20OFMAP%20Writes.png)

\newpage

![googlenet_ifmap_dram_bw](./graph/Q1/Googlenet_%20Avg%20IFMAP%20DRAM%20BW.png)

![googlenet_DRAM_IFMAP_READS](./graph/Q1/Googlenet_%20DRAM%20IFMAP%20Reads.png)

\newpage

![googlenet_filter_dram_bw](./graph/Q1/Googlenet_%20Avg%20FILTER%20DRAM%20BW.png)

![googlenet_DRAM_Filter_READS](./graph/Q1/Googlenet_%20DRAM%20Filter%20Reads.png)

\newpage

![googlenet_ofmap_dram_bw](./graph/Q1/Googlenet_%20Avg%20OFMAP%20DRAM%20BW.png)

![googlenet_DRAM_OFMAP_WRITES](./graph/Q1/Googlenet_%20DRAM%20OFMAP%20Writes.png)

\newpage

![yolo_tiny_ifmap_dram_bw](./graph/Q1/yolo_tiny_%20Avg%20IFMAP%20DRAM%20BW.png)

![yolo_tiny_DRAM_IFMAP_READS](./graph/Q1/yolo_tiny_%20DRAM%20IFMAP%20Reads.png)

\newpage

![yolo_tiny_filter_dram_bw](./graph/Q1/yolo_tiny_%20Avg%20FILTER%20DRAM%20BW.png)

![yolo_tiny_DRAM_Filter_READS](./graph/Q1/yolo_tiny_%20DRAM%20Filter%20Reads.png)

\newpage

![yolo_tiny_ofmap_dram_bw](./graph/Q1/yolo_tiny_%20Avg%20OFMAP%20DRAM%20BW.png)

![yolo_tiny_DRAM_OFMAP_WRITES](./graph/Q1/yolo_tiny_%20DRAM%20OFMAP%20Writes.png)

\newpage

### SRAM Bandwidth Utilization and Read/Writes

![mobilenet_ifmap_sram_bw](./graph/Q1/mobilenet_%20Avg%20IFMAP%20SRAM%20BW.png)

![mobilenet_SRAM_IFMAP_READS](./graph/Q1/mobilenet_%20SRAM%20IFMAP%20Reads.png)

Here the reads of the input memory is largest for eyeriss because the systolic array is the smallest in eyeriss.

The bandwidth is the largest for GoogleTPU because of its systolic array.

\newpage

![mobilenet_filter_sram_bw](./graph/Q1/mobilenet_%20Avg%20FILTER%20SRAM%20BW.png)

![mobilenet_SRAM_Filter_READS](./graph/Q1/mobilenet_%20SRAM%20Filter%20Reads.png)

Bandwidth of the filter memory is the largest for GoogleTPU because of its systolic array.

Number of reads is the largest for scale because of its dataflow.

\newpage

![mobilenet_ofmap_sram_bw](./graph/Q1/mobilenet_%20Avg%20OFMAP%20SRAM%20BW.png)

![mobilenet_SRAM_OFMAP_WRITES](./graph/Q1/mobilenet_%20SRAM%20OFMAP%20Writes.png)

Here, the number of writes is largest for eyeriss because the systolic array is the smallest in eyeriss.

The bandwidth is the largest for GoogleTPU because of its systolic array.

\newpage

Similar orders are observed in resnet18, fasterRCNN, alexnet, googlenet, and yolo_tiny.

![resnet18_ifmap_sram_bw](./graph/Q1/Resnet18_%20Avg%20IFMAP%20SRAM%20BW.png)

![resnet18_SRAM_IFMAP_READS](./graph/Q1/Resnet18_%20SRAM%20IFMAP%20Reads.png)

\newpage

![resnet18_filter_sram_bw](./graph/Q1/Resnet18_%20Avg%20FILTER%20SRAM%20BW.png)

![resnet18_SRAM_Filter_READS](./graph/Q1/Resnet18_%20SRAM%20Filter%20Reads.png)

\newpage

![resnet18_ofmap_sram_bw](./graph/Q1/Resnet18_%20Avg%20OFMAP%20SRAM%20BW.png)

![resnet18_SRAM_OFMAP_WRITES](./graph/Q1/Resnet18_%20SRAM%20OFMAP%20Writes.png)

\newpage

![fasterRCNN_ifmap_sram_bw](./graph/Q1/FasterRCNN_%20Avg%20IFMAP%20SRAM%20BW.png)

![fasterRCNN_SRAM_IFMAP_READS](./graph/Q1/FasterRCNN_%20SRAM%20IFMAP%20Reads.png)

\newpage

![fasterRCNN_filter_sram_bw](./graph/Q1/FasterRCNN_%20Avg%20FILTER%20SRAM%20BW.png)

![fasterRCNN_SRAM_Filter_READS](./graph/Q1/FasterRCNN_%20SRAM%20Filter%20Reads.png)

\newpage

![fasterRCNN_ofmap_sram_bw](./graph/Q1/FasterRCNN_%20Avg%20OFMAP%20SRAM%20BW.png)

![fasterRCNN_SRAM_OFMAP_WRITES](./graph/Q1/FasterRCNN_%20SRAM%20OFMAP%20Writes.png)

\newpage

![alexnet_ifmap_sram_bw](./graph/Q1/alexnet_%20Avg%20IFMAP%20SRAM%20BW.png)

![alexnet_SRAM_IFMAP_READS](./graph/Q1/alexnet_%20SRAM%20IFMAP%20Reads.png)

\newpage

![alexnet_filter_sram_bw](./graph/Q1/alexnet_%20Avg%20FILTER%20SRAM%20BW.png)

![alexnet_SRAM_Filter_READS](./graph/Q1/alexnet_%20SRAM%20Filter%20Reads.png)

\newpage

![alexnet_ofmap_sram_bw](./graph/Q1/alexnet_%20Avg%20OFMAP%20SRAM%20BW.png)

![alexnet_SRAM_OFMAP_WRITES](./graph/Q1/alexnet_%20SRAM%20OFMAP%20Writes.png)

\newpage

![googlenet_ifmap_sram_bw](./graph/Q1/Googlenet_%20Avg%20IFMAP%20SRAM%20BW.png)

![googlenet_SRAM_IFMAP_READS](./graph/Q1/Googlenet_%20SRAM%20IFMAP%20Reads.png)

\newpage

![googlenet_filter_sram_bw](./graph/Q1/Googlenet_%20Avg%20FILTER%20SRAM%20BW.png)

![googlenet_SRAM_Filter_READS](./graph/Q1/Googlenet_%20SRAM%20Filter%20Reads.png)

\newpage

![googlenet_ofmap_sram_bw](./graph/Q1/Googlenet_%20Avg%20OFMAP%20SRAM%20BW.png)

![googlenet_SRAM_OFMAP_WRITES](./graph/Q1/Googlenet_%20SRAM%20OFMAP%20Writes.png)

\newpage

![yolo_tiny_ifmap_sram_bw](./graph/Q1/yolo_tiny_%20Avg%20IFMAP%20SRAM%20BW.png)

![yolo_tiny_SRAM_IFMAP_READS](./graph/Q1/yolo_tiny_%20SRAM%20IFMAP%20Reads.png)

\newpage

## Changing dataflows

Three different DNNs were used: mobilenet, Resnet18, and FasterRCNN.

Three different dataflows for eyeriss configuration were used: OS, WS, and IS.

### Total Runtime

![mobilenet_runtime](./graph/Q2/mobilenet_total_cycles.png)

We can see that the total runtime is highest for IS in the initial layers. This is because  the number of filters is not a factor in determining the mapping efficiency in IS dataflow, while it is the main factor in determining the mapping efficiency in OS and WS dataflows.

\newpage

![resnet18_runtime](./graph/Q2/Resnet18_total_cycles.png)

A similar order is observed in resnet18 as well.

![fasterRCNN_runtime](./graph/Q2/FasterRCNN_total_cycles.png)

A similar order is observed in fasterRCNN as well.

\newpage

### Mapping Efficiency and Compute Utilization

![mobilenet_mapping](./graph/Q2/mobilenet_mapping_efficiency.png)

For mobilenet, the mapping efficiency is highest for IS dataflow and stays constant. This is because the number of filters is not a factor in determining the mapping efficiency in IS dataflow, while it is the main factor in determining the mapping efficiency in OS and WS dataflows.

![mobilenet_compute](./graph/Q2/mobilenet_compute_util.png)

Here, however we see that all three dataflows have similar compute utilization. This is due to compute utilization being dependent on $T$, that is the number of timesteps too.

\newpage

![resnet18_mapping](./graph/Q2/Resnet18_mapping_efficiency.png)

![resnet18_compute](./graph/Q2/Resnet18_compute_util.png)

A similar order is observed in resnet18 as well.

![fasterRCNN_mapping](./graph/Q2/FasterRCNN_mapping_efficiency.png)

![fasterRCNN_compute](./graph/Q2/FasterRCNN_compute_util.png)

A similar order is observed in fasterRCNN as well.

\newpage

### DRAM Bandwidth Utilization and Read/Writes

![mobilenet_ifmap_dram_bw](./graph/Q2/mobilenet_%20Avg%20IFMAP%20DRAM%20BW.png)

![mobilenet_DRAM_IFMAP_READS](./graph/Q2/mobilenet_%20DRAM%20IFMAP%20Reads.png)

Here the reads and bandwidth of the input memory is lowest for the Input Stationary dataflow because the dataflow dictates that the input memory is read only the minimum number of times and then the same data is used for all the filters.

\newpage

![resnet18_ifmap_dram_bw](./graph/Q2/Resnet18_%20Avg%20IFMAP%20DRAM%20BW.png)

![resnet18_DRAM_IFMAP_READS](./graph/Q2/Resnet18_%20DRAM%20IFMAP%20Reads.png)

A similar order is observed in resnet18 as well.

\newpage

![fasterRCNN_ifmap_dram_bw](./graph/Q2/FasterRCNN_%20Avg%20IFMAP%20DRAM%20BW.png)

![fasterRCNN_DRAM_IFMAP_READS](./graph/Q2/FasterRCNN_%20DRAM%20IFMAP%20Reads.png)

A similar order is observed in fasterRCNN as well.

\newpage

![mobilenet_filter_dram_bw](./graph/Q2/mobilenet_%20Avg%20FILTER%20DRAM%20BW.png)

![mobilenet_DRAM_Filter_READS](./graph/Q2/mobilenet_%20DRAM%20Filter%20Reads.png)

Here the reads and bandwidth of the filter memory is highest for the Input Stationary dataflow because the dataflow dictates that the filter memory is read the maximum number of times.

\newpage

![resnet18_filter_dram_bw](./graph/Q2/Resnet18_%20Avg%20FILTER%20DRAM%20BW.png)

![resnet18_DRAM_Filter_READS](./graph/Q2/Resnet18_%20DRAM%20Filter%20Reads.png)

A similar order is observed in resnet18 as well.

\newpage

![fasterRCNN_filter_dram_bw](./graph/Q2/FasterRCNN_%20Avg%20FILTER%20DRAM%20BW.png)

![fasterRCNN_DRAM_Filter_READS](./graph/Q2/FasterRCNN_%20DRAM%20Filter%20Reads.png)

A similar order is observed in fasterRCNN as well.

\newpage

![mobilenet_ofmap_dram_bw](./graph/Q2/mobilenet_%20Avg%20OFMAP%20DRAM%20BW.png)

![mobilenet_DRAM_OFMAP_WRITES](./graph/Q2/mobilenet_%20DRAM%20OFMAP%20Writes.png)

Here the bandwidth depends on the number of filters and the number of timesteps. Which is why the bandwidth varies like it does for OS graph. The WS and IS dataflow graphs vary similarly but in the opposite direction due to the same reason.

For the number of writes however, the number of writes is lowest for the Output Stationary dataflow because the dataflow dictates that the output memory is written only the minimum number of times.

\newpage

![resnet18_ofmap_dram_bw](./graph/Q2/Resnet18_%20Avg%20OFMAP%20DRAM%20BW.png)

![resnet18_DRAM_OFMAP_WRITES](./graph/Q2/Resnet18_%20DRAM%20OFMAP%20Writes.png)

A similar order is observed in resnet18 as well.

\newpage

![fasterRCNN_ofmap_dram_bw](./graph/Q2/FasterRCNN_%20Avg%20OFMAP%20DRAM%20BW.png)

![fasterRCNN_DRAM_OFMAP_WRITES](./graph/Q2/FasterRCNN_%20DRAM%20OFMAP%20Writes.png)

A similar order is observed in fasterRCNN as well.

\newpage

### SRAM Bandwidth Utilization and Read/Writes

![mobilenet_ifmap_sram_bw](./graph/Q2/mobilenet_%20Avg%20IFMAP%20SRAM%20BW.png)

![mobilenet_SRAM_IFMAP_READS](./graph/Q2/mobilenet_%20SRAM%20IFMAP%20Reads.png)

Here the reads and bandwidth of the input memory is the lowest for the Input Stationary dataflow because the dataflow dictates that the input memory is read only the minimum number of times and then the same data is used for all the filters.

\newpage

![resnet18_ifmap_sram_bw](./graph/Q2/Resnet18_%20Avg%20IFMAP%20SRAM%20BW.png)

![resnet18_SRAM_IFMAP_READS](./graph/Q2/Resnet18_%20SRAM%20IFMAP%20Reads.png)

A similar order is observed in resnet18 as well.

\newpage

![fasterRCNN_ifmap_sram_bw](./graph/Q2/FasterRCNN_%20Avg%20IFMAP%20SRAM%20BW.png)

![fasterRCNN_SRAM_IFMAP_READS](./graph/Q2/FasterRCNN_%20SRAM%20IFMAP%20Reads.png)

A similar order is observed in fasterRCNN as well.

\newpage

![mobilenet_filter_sram_bw](./graph/Q2/mobilenet_%20Avg%20FILTER%20SRAM%20BW.png)

![mobilenet_SRAM_Filter_READS](./graph/Q2/mobilenet_%20SRAM%20Filter%20Reads.png)

Here the reads and bandwidth of the filter memory is the lowest for Weight Stationary dataflow because the dataflow dictates that the filter memory is read the minimum number of times and then the same data is used for all the input.

\newpage

![resnet18_filter_sram_bw](./graph/Q2/Resnet18_%20Avg%20FILTER%20SRAM%20BW.png)

![resnet18_SRAM_Filter_READS](./graph/Q2/Resnet18_%20SRAM%20Filter%20Reads.png)

A similar order is observed in resnet18 as well.

\newpage

![fasterRCNN_filter_sram_bw](./graph/Q2/FasterRCNN_%20Avg%20FILTER%20SRAM%20BW.png)

![fasterRCNN_SRAM_Filter_READS](./graph/Q2/FasterRCNN_%20SRAM%20Filter%20Reads.png)

A similar order is observed in fasterRCNN as well.

\newpage

![mobilenet_ofmap_sram_bw](./graph/Q2/mobilenet_%20Avg%20OFMAP%20SRAM%20BW.png)

![mobilenet_SRAM_OFMAP_WRITES](./graph/Q2/mobilenet_%20SRAM%20OFMAP%20Writes.png)

Here the reads and bandwidth of the output memory is the lowest for the Output Stationary dataflow because the dataflow dictates that the output memory is written only the minimum number of times.

\newpage

![resnet18_ofmap_sram_bw](./graph/Q2/Resnet18_%20Avg%20OFMAP%20SRAM%20BW.png)

![resnet18_SRAM_OFMAP_WRITES](./graph/Q2/Resnet18_%20SRAM%20OFMAP%20Writes.png)

A similar order is observed in resnet18 as well.

\newpage

![fasterRCNN_ofmap_sram_bw](./graph/Q2/FasterRCNN_%20Avg%20OFMAP%20SRAM%20BW.png)

![fasterRCNN_SRAM_OFMAP_WRITES](./graph/Q2/FasterRCNN_%20SRAM%20OFMAP%20Writes.png)

A similar order is observed in fasterRCNN as well.

\newpage

## Changing buffer sizes

Three different DNNs were used: mobilenet, resnet18, and FasterRCNN.

8 different memory sizes were used for eyeriss configuration where input, filter, and output memory sizes were varied in [54KB, 108KB].

Mapping efficiency and compute utilization were constant for different memory sizes.

Total runtime was also constant for different memory sizes.

Strangely, SRAM bandwidth utilization and reads/writes were also constant for different memory sizes.

However, DRAM bandwidth utilization and reads/writes were not constant for different memory sizes.

\newpage

### DRAM Bandwidth Utilization and Read/Writes


![mobilenet_ifmap_dram_bw](./graph/Q3/mobilenet_%20Avg%20IFMAP%20DRAM%20BW.png)

![mobilenet_DRAM_IFMAP_READS](./graph/Q3/mobilenet_%20DRAM%20IFMAP%20Reads.png)

\newpage

![mobilenet_filter_dram_bw](./graph/Q3/mobilenet_%20Avg%20FILTER%20DRAM%20BW.png)

![mobilenet_ofmap_dram_bw](./graph/Q3/mobilenet_%20Avg%20OFMAP%20DRAM%20BW.png)

\newpage

Similar orders are observed in resnet18.

![resnet18_ifmap_dram_bw](./graph/Q3/Resnet18_%20Avg%20IFMAP%20DRAM%20BW.png)

![resnet18_DRAM_IFMAP_READS](./graph/Q3/Resnet18_%20DRAM%20IFMAP%20Reads.png)

\newpage

![resnet18_filter_dram_bw](./graph/Q3/Resnet18_%20Avg%20FILTER%20DRAM%20BW.png)

![resnet18_ofmap_dram_bw](./graph/Q3/Resnet18_%20Avg%20OFMAP%20DRAM%20BW.png)

\newpage

Similar orders are observed in fasterRCNN.

![fasterRCNN_ifmap_dram_bw](./graph/Q3/FasterRCNN_%20Avg%20IFMAP%20DRAM%20BW.png)

![fasterRCNN_DRAM_IFMAP_READS](./graph/Q3/FasterRCNN_%20DRAM%20IFMAP%20Reads.png)

\newpage

![fasterRCNN_filter_dram_bw](./graph/Q3/FasterRCNN_%20Avg%20FILTER%20DRAM%20BW.png)

![fasterRCNN_ofmap_dram_bw](./graph/Q3/FasterRCNN_%20Avg%20OFMAP%20DRAM%20BW.png)

\newpage

## Changing systolic array sizes

Three different DNNs were used: mobilenet, resnet18, and FasterRCNN.

9 different systolic array sizes were used for eyeriss configuration where systolic array height and width were varied in [12, 24, 48] and [14, 28, 56] respectively.

Mapping efficiency and compute utilization were mostly constant for different systolic array sizes.

### Total Runtime

![mobilenet_runtime](./graph/Q4/mobilenet_total_cycles.png)

We can see that the total runtime is highest for the smallest systolic array and lowest for the largest systolic array. This is because the number of PEs is the main factor in determining the total runtime.

\newpage

![resnet18_runtime](./graph/Q4/Resnet18_total_cycles.png)

A similar order is observed in resnet18 as well.

![fasterRCNN_runtime](./graph/Q4/FasterRCNN_total_cycles.png)

A similar order is observed in fasterRCNN as well.

\newpage

### DRAM Bandwidth Utilization and Read/Writes

![mobilenet_ifmap_dram_bw](./graph/Q4/mobilenet_%20Avg%20IFMAP%20DRAM%20BW.png)

![mobilenet_DRAM_IFMAP_READS](./graph/Q4/mobilenet_%20DRAM%20IFMAP%20Reads.png)

Here the bandwidth and reads of the input DRAM memory is dependent on the height of the systolic array. All configurations with the same height have similar bandwidth and reads.

\newpage

![resnet18_ifmap_dram_bw](./graph/Q4/Resnet18_%20Avg%20IFMAP%20DRAM%20BW.png)

![resnet18_DRAM_IFMAP_READS](./graph/Q4/Resnet18_%20DRAM%20IFMAP%20Reads.png)

A similar order is observed in resnet18 as well.

\newpage

![fasterRCNN_ifmap_dram_bw](./graph/Q4/FasterRCNN_%20Avg%20IFMAP%20DRAM%20BW.png)

![fasterRCNN_DRAM_IFMAP_READS](./graph/Q4/FasterRCNN_%20DRAM%20IFMAP%20Reads.png)

A similar order is observed in fasterRCNN as well.

\newpage

![mobilenet_filter_dram_bw](./graph/Q4/mobilenet_%20Avg%20FILTER%20DRAM%20BW.png)

![mobilenet_DRAM_Filter_READS](./graph/Q4/mobilenet_%20DRAM%20Filter%20Reads.png)

Here the reads of the filter DRAM memory remains constant for different systolic array sizes. However, the bandwidth is dependent on the area of the systolic array. All configurations with the same area have similar bandwidth.

\newpage

![resnet18_filter_dram_bw](./graph/Q4/Resnet18_%20Avg%20FILTER%20DRAM%20BW.png)

![resnet18_DRAM_Filter_READS](./graph/Q4/Resnet18_%20DRAM%20Filter%20Reads.png)

A similar order is observed in resnet18 as well.

\newpage

![fasterRCNN_filter_dram_bw](./graph/Q4/FasterRCNN_%20Avg%20FILTER%20DRAM%20BW.png)

![fasterRCNN_DRAM_Filter_READS](./graph/Q4/FasterRCNN_%20DRAM%20Filter%20Reads.png)

A similar order is observed in fasterRCNN as well.

\newpage

![mobilenet_ofmap_dram_bw](./graph/Q4/mobilenet_%20Avg%20OFMAP%20DRAM%20BW.png)

![mobilenet_DRAM_OFMAP_WRITES](./graph/Q4/mobilenet_%20DRAM%20OFMAP%20Writes.png)

Here writes of the output DRAM memory depend on the height of the systolic array. All configurations with the same width have similar writes.

Also the bandwidth of the output DRAM buffer is dependent on the width of the systolic array. All configurations with the same width have similar bandwidth.

\newpage

![resnet18_ofmap_dram_bw](./graph/Q4/Resnet18_%20Avg%20OFMAP%20DRAM%20BW.png)

![resnet18_DRAM_OFMAP_WRITES](./graph/Q4/Resnet18_%20DRAM%20OFMAP%20Writes.png)

A similar order is observed in resnet18 as well.

\newpage

![fasterRCNN_ofmap_dram_bw](./graph/Q4/FasterRCNN_%20Avg%20OFMAP%20DRAM%20BW.png)

![fasterRCNN_DRAM_OFMAP_WRITES](./graph/Q4/FasterRCNN_%20DRAM%20OFMAP%20Writes.png)

A similar order is observed in fasterRCNN as well.

\newpage

# References

Note that the Scale-Sim paper and the Scale-Sim Github repository are the primary sources of information for this report.

Also the text below are clickable links to the respective sources.

- [Scale - Sim Paper](https://ieeexplore.ieee.org/document/9238602)
- [Scale - Sim Github](https://github.com/scalesim-project/scale-sim-v2)