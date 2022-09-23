# PTAS: A High-Performance TAS in TSN Networks
This repository contains a module of PTAS with inet and nesting in OMNeT++.

## Introduction<br>
PIFO-based Time-Aware Shaper (PTAS) is a novel TAS scheme for massive concurrent flows. In PTAS, a
PIFO queue is responsible for sorting and buffering all time-triggered flows. 

PTAS resolves the flow interleaving caused by concurrent flows. Meanwhile, the employment of only one PIFO queue frees the shaping
capability of PTAS from the limitation of the number of hardware queues.

## Compatibility<br>
The current version of the PTAS module has been tested with OMNeT++ version 5.5.1, INET version 4.1.2 and 
[NeSTiNg](https://gitlab.com/ipvs/nesting) under Ubuntu16.04.

## Getting Started
+ Download and install OMNeT++ version 5.5.1 at https://omnetpp.org/ .
+ Clone and unzip nesting fllow the instructions at https://gitlab.com/ipvs/nesting/-/blob/master/README.md.

```
  $ git clone https://gitlab.com/ipvs/nesting.git
```
+ Clone and unzip INET version 4.1.2 framework.

```
  $ git clone https://github.com/inet-framework/inet.git
  $ git checkout -b v4.1.2 v4.1.2
```
+ Clone and unzip PTAS module.

```
  $ git clone https://github.com/lxacc/PTAS.git
```
+ Make sure the directory is like

```
  <workspace>
  ├── nesting
  ├── inet
  └── ptas
```

## Create a Project in OMNeT++
+ Launch OMNet++ IDE and set the workspace to the directory where packages have been downloaded in the previous step
+ Import  `INET`,`NeSTiNg `,and `PATS` packages into your workspace.
    * `File -> Import`
    * select `General>Existing Projects into Workspace option `and `Next>`
    *  under `Select root directory` add your previously chosen workspace directory
    * select `inet`, `nesting` and `ptas` projects and `Finish`
+ The three projects should appear in the Project Explorer

## Build and run
