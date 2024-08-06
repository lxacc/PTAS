# PTAS: A High-Performance TAS in TSN Networks
This repository contains a module of PTAS with inet and nesting in OMNeT++.

## Introduction<br>
PIFO-based Time-Aware Shaper (PTAS) is a novel TAS scheme for massive concurrent flows. In PTAS, a
PIFO queue is responsible for sorting and buffering all time-triggered flows. 

Through frame sorting rather than conventional isolation, the PTAS efficiently provides a deterministic transmission
guarantee for concurrent flows

## Compatibility<br>
The current version of the PTAS module has been tested with OMNeT++ version 5.5.1, INET version 4.1.2 and 
[NeSTiNg](https://gitlab.com/ipvs/nesting) under Ubuntu16.04.

## Getting Started
+ Download and install OMNeT++ version 5.5.1 at https://omnetpp.org/.
+ Clone and unzip nesting follow the instructions at https://gitlab.com/ipvs/nesting/-/blob/master/README.md.

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
+ Import  `INET`,`NeSTiNg `,and `PTAS` packages into your workspace.
    * `File -> Import`
    * select `General>Existing Projects into Workspace option `and `Next>`
    *  under `Select root directory` add your previously chosen workspace directory
    * select `inet`, `nesting` and `ptas` projects and `Finish`
+ The three projects should appear in the Project Explorer

## Build and run

### Build
+ First, right click ptas project and click on `Properties`
+ Under `Project References`, select `inet` and `nesting`, Apply and Close (Important)
+ Each project can be set to release or debug build by right click and `Build Configurations -> Set Active`
+ Right click each project (in the order `inet, nesting, ptas`) and Build Project      
+ You can now run the simulation  


### Run simulation
+ Navigate into `ptas > simulations` in the project explorer
+ Right-click `paper_test_ptas_7hop.ini` and choose `Run As` (or `Debug As` depending on the build configuration) OMNeT++ Simulation
+ After finishing the simulation, find the statistics file in `result-dir` and export the end-to-end delay data. These data are the source for the figures in the paper

### Change parameters
+ `[Flow24.ned](https://github.com/lxacc/PTAS/blob/main/simulations/Flow24.ned)` is the topology used for simulation. In the topology, `RobotController` is the source of time-triggered flows, and `RobotArm` is the destination. 24 RobotControllers are set to simulate a multi-access scenario with massive concurrent flows
+ If a new topology is needed, please modify `Flow24.ned`
+ `[paper_test_ptas_7hop.ini](https://github.com/lxacc/PTAS/blob/main/simulations/paper_test_ptas_7hop.ini)`, `[paper_test_spq_7hop.ini](https://github.com/lxacc/PTAS/blob/main/simulations/paper_test_spq_7hop.ini)`, and `[paper_test_tas_7hop.ini](https://github.com/lxacc/PTAS/blob/main/simulations/paper_test_tas_7hop.ini)` are the configurations of the proposed PTAS and the benchmarks
+ In `simulations/xml`, there are flow and gate configurations in PTAS, TAS, and SPQ with 4, 8, 12, 16, 20, and 24 flows. Each flow is set with the following parameters
```
  <schedules>
    <defaultcycle>1000us</defaultcycle>
    <host name="robotController1">
      <cycle>1000us</cycle>
      <entry>
        <start>0us</start>
        <queue>7</queue>
        <dest>00:00:00:00:01:01</dest>
        <size>95B</size>
        <burst>2</burst>
        <flowId>1</flowId>
      </entry>
    </host>
  </schedules>
```
The load of one flow can be calculated according to the `<size> (frame length)`, `<burst> (number of frames in a cycle)`, and `<cycle>`
+ When running with different numbers of flows, please modify the xml's name in the corresponding `.ini`, such as  
```
  **.filteringDatabase.database = xmldoc("**xml/PTASRouting24.xml**", "/filteringDatabases/")

  **.switchA.eth[24].queue.gateController.initialSchedule = xmldoc("**xml/Flow24_ptas.xml**", "/schedules/switch[@name='switchA']/port[@id='24']/schedule")
  ...

  **.robotController*.trafGenSchedApp.initialSchedule = xmldoc("**xml/Flow24_ptas.xml**")
```