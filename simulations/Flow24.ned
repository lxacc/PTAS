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
    @display("bgb=4122.1235,2207.5437");
    types:
        channel C extends DatarateChannel
        {
            delay = 0us;
            datarate = 1Gbps;
        }
    submodules:
        switchA: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=949.0375,598.3063");
            gates:
                ethg[25];
        }
        switchB: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=1369.915,350.73126");
            gates:
                ethg[3];
        }
        switchC: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=1704.1412,202.18625");
            gates:
                ethg[3];
        }
        switchD: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=2166.2812,202.18625");
            gates:
                ethg[3];
        }
        switchE: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=2583.0325,288.8375");
            gates:
                ethg[3];
        }
        switchF: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=2888.375,598.3063");
            gates:
                ethg[26];
        }
        switchG: VlanEtherSwitchPreemptable {
            parameters:
                @display("p=2166.2812,598.3063");
            gates:
                ethg[2];
        }

        workstation1: VlanEtherHostQ {
            @display("p=1369.915,717.9675");
        }
        backupServer: VlanEtherHostQ {
            @display("p=3400.03,602.4325");
        }



        robotController1: VlanEtherHostSched {
            @display("p=251.70125,1184.2338");
        }
        robotController2: VlanEtherHostSched {
            @display("p=474.51874,1184.2338");
        }
        robotController3: VlanEtherHostSched {
            @display("p=730.34625,1184.2338");
        }
        robotController4: VlanEtherHostSched {
            @display("p=977.92126,1184.2338");
        }
        robotController5: VlanEtherHostSched {
            @display("p=1233.7488,1225.4962");
        }
        robotController6: VlanEtherHostSched {
            @display("p=1600.985,1225.4962");
        }
        robotController7: VlanEtherHostSched {
            @display("p=251.70125,1448.3137");
        }
        robotController8: VlanEtherHostSched {
            @display("p=524.03375,1448.3137");
        }
        robotController9: VlanEtherHostSched {
            @display("p=759.23,1448.3137");
        }
        robotController10: VlanEtherHostSched {
            @display("p=1006.805,1477.1975");
        }
        robotController11: VlanEtherHostSched {
            @display("p=1262.6324,1477.1975");
        }
        robotController12: VlanEtherHostSched {
            @display("p=1600.985,1477.1975");
        }
        robotController13: VlanEtherHostSched {
            @display("p=251.70125,1704.1412");
        }
        robotController14: VlanEtherHostSched {
            @display("p=524.03375,1704.1412");
        }
        robotController15: VlanEtherHostSched {
            @display("p=779.86127,1704.1412");
        }
        robotController16: VlanEtherHostSched {
            @display("p=1043.9413,1704.1412");
        }
        robotController17: VlanEtherHostSched {
            @display("p=1303.895,1704.1412");
        }
        robotController18: VlanEtherHostSched {
            @display("p=1600.985,1704.1412");
        }
        robotController19: VlanEtherHostSched {
            @display("p=284.71124,1980.6");
        }
        robotController20: VlanEtherHostSched {
            @display("p=528.16,1980.6");
        }
        robotController21: VlanEtherHostSched {
            @display("p=779.86127,1980.6");
        }
        robotController22: VlanEtherHostSched {
            @display("p=1043.9413,1992.9788");
        }
        robotController23: VlanEtherHostSched {
            @display("p=1303.895,1980.6");
        }
        robotController24: VlanEtherHostSched {
            @display("p=1600.985,1980.6");
        }



        roboticArm1: VlanEtherHostQ {
            @display("p=2261.185,1332.7788");
        }
        roboticArm2: VlanEtherHostQ {
            @display("p=2587.1587,1332.7788");
        }
        roboticArm3: VlanEtherHostQ {
            @display("p=2875.9963,1345.1575");
        }
        roboticArm4: VlanEtherHostQ {
            @display("p=3193.7175,1345.1575");
        }
        roboticArm5: VlanEtherHostQ {
            @display("p=3511.4387,1345.1575");
        }
        roboticArm6: VlanEtherHostQ {
            @display("p=3792.0237,1345.1575");
        }
        roboticArm7: VlanEtherHostQ {
            @display("p=2261.185,1551.47");
        }
        roboticArm8: VlanEtherHostQ {
            @display("p=2583.0325,1551.47");
        }
        roboticArm9: VlanEtherHostQ {
            @display("p=2875.9963,1563.8488");
        }
        roboticArm10: VlanEtherHostQ {
            @display("p=3164.8337,1563.8488");
        }
        roboticArm11: VlanEtherHostQ {
            @display("p=3511.4387,1539.0913");
        }
        roboticArm12: VlanEtherHostQ {
            @display("p=3792.0237,1539.0913");
        }
        roboticArm13: VlanEtherHostQ {
            @display("p=2261.185,1749.53");
        }
        roboticArm14: VlanEtherHostQ {
            @display("p=2583.0325,1749.53");
        }
        roboticArm15: VlanEtherHostQ {
            @display("p=2875.9963,1761.9088");
        }
        roboticArm16: VlanEtherHostQ {
            @display("p=3164.8337,1761.9088");
        }
        roboticArm17: VlanEtherHostQ {
            @display("p=3511.4387,1761.9088");
        }
        roboticArm18: VlanEtherHostQ {
            @display("p=3792.0237,1761.9088");
        }
        roboticArm19: VlanEtherHostQ {
            @display("p=2240.5537,1992.9788");
        }
        roboticArm20: VlanEtherHostQ {
            @display("p=2554.1487,1980.6");
        }
        roboticArm21: VlanEtherHostQ {
            @display("p=2888.375,1992.9788");
        }
        roboticArm22: VlanEtherHostQ {
            @display("p=3181.3389,1992.9788");
        }
        roboticArm23: VlanEtherHostQ {
            @display("p=3490.8076,1992.9788");
        }
        roboticArm24: VlanEtherHostQ {
            @display("p=3726.0037,1992.9788");
        }


        workstation2: VlanEtherHostQ {
            @display("p=1704.1412,602.4325");
        }
        workstation3: VlanEtherHostQ {
            @display("p=2166.2812,924.28");
        }
        workstation4: VlanEtherHostQ {
            @display("p=2587.1587,602.4325");
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
