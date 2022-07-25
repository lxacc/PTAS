//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package pifo.simulations;

import ned.DatarateChannel;
import pifo.pifo.node.ethernet.VlanEtherHostQ;
import pifo.pifo.node.ethernet.VlanEtherHostSched;
import pifo.pifo.node.ethernet.VlanEtherSwitchPreemptable;


network Flow24
{
    @display("bgb=3297.51,1887.8401");
    types:
        channel C extends DatarateChannel
        {
            delay = 0us;
            datarate = 1Gbps;
        }
    submodules:
        switchA: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=817.01996,654.07495");
            gates:
                ethg[25];
        }
        switchB: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=1105.38,425.385");
            gates:
                ethg[3];
        }
        switchC: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=1530.765,152.145");
            gates:
                ethg[3];
        }
        switchD: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=2130.03,152.145");
            gates:
                ethg[3];
        }        
        switchE: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=2747.925,152.145");
            gates:
                ethg[3];
        }
        switchF: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=2747.925,515.43");
            gates:
                ethg[26];
        }
        switchG: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=2130.03,465.75003");
            gates:
                ethg[2];
        }
        
        workstation1: VlanEtherHostQ {
            @display("p=1105.38,155.25");
        }
        backupServer: VlanEtherHostQ {
            @display("p=3123.6301,155.25");
        }



        robotController1: VlanEtherHostSched {
            @display("p=794.88,117.990005");
        }
        robotController2: VlanEtherHostSched {
            @display("p=515.43,117.990005");
        }
        robotController3: VlanEtherHostSched {
            @display("p=239.085,117.990005");
        }
        robotController4: VlanEtherHostSched {
            @display("p=714.15,326.02502");
        }
        robotController5: VlanEtherHostSched {
            @display("p=512.325,326.02502");
        }
        robotController6: VlanEtherHostSched {
            @display("p=239.085,326.02502");
        }
        robotController7: VlanEtherHostSched {
            @display("p=487.48502,537.16504");
        }
        robotController8: VlanEtherHostSched {
            @display("p=211.14,537.16504");
        }
        robotController9: VlanEtherHostSched {
            @display("p=211.14,723.465");
        }
        robotController10: VlanEtherHostSched {
            @display("p=211.14,915.97504");
        }
        robotController11: VlanEtherHostSched {
            @display("p=211.14,1114.6951");
        }
        robotController12: VlanEtherHostSched {
            @display("p=211.14,1304.1001");
        }
        robotController13: VlanEtherHostSched {
            @display("p=593.055,1304.1001");
        }
        robotController14: VlanEtherHostSched {
            @display("p=915.97504,1304.1001");
        }
        robotController15: VlanEtherHostSched {
            @display("p=211.14,1505.925");
        }
        robotController16: VlanEtherHostSched {
            @display("p=589.95,1505.925");
        }
        robotController17: VlanEtherHostSched {
            @display("p=915.97504,1505.925");
        }
        robotController18: VlanEtherHostSched {
            @display("p=1226.4751,1505.925");
        }
        robotController19: VlanEtherHostSched {
            @display("p=189.405,1723.275");
        }
        robotController20: VlanEtherHostSched {
            @display("p=444.015,1723.275");
        }
        robotController21: VlanEtherHostSched {
            @display("p=673.78503,1648.755");
        }
        robotController22: VlanEtherHostSched {
            @display("p=915.97504,1723.275");
        }
        robotController23: VlanEtherHostSched {
            @display("p=1142.64,1670.4901");
        }
        robotController24: VlanEtherHostSched {
            @display("p=1347.5701,1723.275");
        }



        roboticArm1: VlanEtherHostQ {
            @display("p=1800.9,1061.91");
        }
        roboticArm2: VlanEtherHostQ {
            @display("p=2061.72,1061.91");
        }
        roboticArm3: VlanEtherHostQ {
            @display("p=2285.28,1061.91");
        }
        roboticArm4: VlanEtherHostQ {
            @display("p=2527.47,1061.91");
        }
        roboticArm5: VlanEtherHostQ {
            @display("p=2844.1802,1061.91");
        }
        roboticArm6: VlanEtherHostQ {
            @display("p=3123.6301,1061.91");
        }
        roboticArm7: VlanEtherHostQ {
            @display("p=1800.9,1282.365");
        }
        roboticArm8: VlanEtherHostQ {
            @display("p=2058.615,1279.26");
        }
        roboticArm9: VlanEtherHostQ {
            @display("p=2285.28,1279.26");
        }
        roboticArm10: VlanEtherHostQ {
            @display("p=2496.4202,1279.26");
        }
        roboticArm11: VlanEtherHostQ {
            @display("p=2844.1802,1257.525");
        }
        roboticArm12: VlanEtherHostQ {
            @display("p=3123.6301,1257.525");
        }
        roboticArm13: VlanEtherHostQ {
            @display("p=1800.9,1481.0851");
        }
        roboticArm14: VlanEtherHostQ {
            @display("p=2058.615,1481.0851");
        }
        roboticArm15: VlanEtherHostQ {
            @display("p=2285.28,1481.0851");
        }
        roboticArm16: VlanEtherHostQ {
            @display("p=2496.4202,1481.0851");
        }
        roboticArm17: VlanEtherHostQ {
            @display("p=2844.1802,1481.0851");
        }
        roboticArm18: VlanEtherHostQ {
            @display("p=3123.6301,1481.0851");
        }
        roboticArm19: VlanEtherHostQ {
            @display("p=1782.27,1723.275");
        }
        roboticArm20: VlanEtherHostQ {
            @display("p=2027.5651,1710.8551");
        }
        roboticArm21: VlanEtherHostQ {
            @display("p=2297.7002,1710.8551");
        }
        roboticArm22: VlanEtherHostQ {
            @display("p=2515.05,1710.8551");
        }
        roboticArm23: VlanEtherHostQ {
            @display("p=2825.55,1710.8551");
        }
        roboticArm24: VlanEtherHostQ {
            @display("p=3061.53,1710.8551");
        }


        workstation2: VlanEtherHostQ {
            @display("p=1530.765,515.43");
        }
        workstation3: VlanEtherHostQ {
            @display("p=1865.0651,722.09375");
        }
        workstation4: VlanEtherHostQ {
            @display("p=2455.1187,400.24625");
        }

    connections:
        robotController1.ethg <--> C <--> switchA.ethg[0];
        robotController2.ethg <--> C <--> switchA.ethg[1];
        robotController3.ethg <--> C <--> switchA.ethg[2];
        robotController4.ethg <--> C <--> switchA.ethg[3];
        robotController5.ethg <--> C <--> switchA.ethg[4];
        robotController6.ethg <--> C <--> switchA.ethg[5];
        robotController7.ethg <--> C <--> switchA.ethg[6];
        robotController8.ethg <--> C <--> switchA.ethg[7];
        robotController9.ethg <--> C <--> switchA.ethg[8];
        robotController10.ethg <--> C <--> switchA.ethg[9];
        robotController11.ethg <--> C <--> switchA.ethg[10];
        robotController12.ethg <--> C <--> switchA.ethg[11];
        robotController13.ethg <--> C <--> switchA.ethg[12];
        robotController14.ethg <--> C <--> switchA.ethg[13];
        robotController15.ethg <--> C <--> switchA.ethg[14];
        robotController16.ethg <--> C <--> switchA.ethg[15];
        robotController17.ethg <--> C <--> switchA.ethg[16];
        robotController18.ethg <--> C <--> switchA.ethg[17];
        robotController19.ethg <--> C <--> switchA.ethg[18];
        robotController20.ethg <--> C <--> switchA.ethg[19];
        robotController21.ethg <--> C <--> switchA.ethg[20];
        robotController22.ethg <--> C <--> switchA.ethg[21];
        robotController23.ethg <--> C <--> switchA.ethg[22];
        robotController24.ethg <--> C <--> switchA.ethg[23];


        roboticArm1.ethg <--> C <--> switchF.ethg[0];
        roboticArm2.ethg <--> C <--> switchF.ethg[1];
        roboticArm3.ethg <--> C <--> switchF.ethg[2];
        roboticArm4.ethg <--> C <--> switchF.ethg[3];
        roboticArm5.ethg <--> C <--> switchF.ethg[4];
        roboticArm6.ethg <--> C <--> switchF.ethg[5];
        roboticArm7.ethg <--> C <--> switchF.ethg[6];
        roboticArm8.ethg <--> C <--> switchF.ethg[7];
        roboticArm9.ethg <--> C <--> switchF.ethg[8];
        roboticArm10.ethg <--> C <--> switchF.ethg[9];
        roboticArm11.ethg <--> C <--> switchF.ethg[10];
        roboticArm12.ethg <--> C <--> switchF.ethg[11];
        roboticArm13.ethg <--> C <--> switchF.ethg[12];
        roboticArm14.ethg <--> C <--> switchF.ethg[13];
        roboticArm15.ethg <--> C <--> switchF.ethg[14];
        roboticArm16.ethg <--> C <--> switchF.ethg[15];
        roboticArm17.ethg <--> C <--> switchF.ethg[16];
        roboticArm18.ethg <--> C <--> switchF.ethg[17];
        roboticArm19.ethg <--> C <--> switchF.ethg[18];
        roboticArm20.ethg <--> C <--> switchF.ethg[19];
        roboticArm21.ethg <--> C <--> switchF.ethg[20];
        roboticArm22.ethg <--> C <--> switchF.ethg[21];
        roboticArm23.ethg <--> C <--> switchF.ethg[22];
        roboticArm24.ethg <--> C <--> switchF.ethg[23];

        workstation1.ethg <--> C <--> switchB.ethg[0];
        workstation2.ethg <--> C <--> switchC.ethg[0];
        workstation3.ethg <--> C <--> switchG.ethg[0];
        workstation4.ethg <--> C <--> switchE.ethg[0];
        backupServer.ethg <--> C <--> switchF.ethg[25];

        //switch connect
        switchA.ethg[24] <--> C <--> switchB.ethg[1];
        switchB.ethg[2] <--> C <--> switchC.ethg[1];
        switchC.ethg[2] <--> C <--> switchD.ethg[1];
        switchD.ethg[2] <--> C <--> switchE.ethg[1];
        switchE.ethg[2] <--> C <--> switchF.ethg[24];
        switchD.ethg[0] <--> C <--> switchG.ethg[1];
}
