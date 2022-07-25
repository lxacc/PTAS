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

#ifndef __MAIN_PIFOQUEUE_H_
#define __MAIN_PIFOQUEUE_H_

#include <omnetpp.h>
#include <list>

#include "inet/common/ModuleAccess.h"
#include "inet/common/queue/IQueueAccess.h"

#include "nesting/ieee8021q/Ieee8021q.h"
#include "nesting/ieee8021q/queue/transmissionSelectionAlgorithms/TSAlgorithm.h"
#include "nesting/ieee8021q/queue/framePreemption/IPreemptableQueue.h"
#include "pifo/ieee8021q/queue/framePreemption/PIFOLengthAwareQueue.h"
#include "pifo/common/schedule/PIFOSchedule.h"
using namespace omnetpp;
using namespace inet;
//using namespace nesting;
namespace nesting {

class TSAlgorithm;

/**
 * See the NED file for a detailed description.
 */
//class PIFOQueue: public cSimpleModule, public LengthAwareQueue {
class PIFOQueue:  public PIFOLengthAwareQueue {
//protected:
//    /**
//     * Reference to transmission-selection-algorithm module
//     */
//    TSAlgorithm* tsAlgorithm;
//
//    /**
//     * Available buffer capacity in Bits.
//     */
//    long availableBufferCapacity;
//
//    /**
//     * True if frame preemption is enabled, false otherwise.
//     */
//    bool framePreemptionEnabled;
//
//    bool expressQueue;
//
//    long numPacketsReceived = 0;
//
//    long numPacketsDropped = 0;
//
//    long numPacketsEnqueued = 0;
//
//    uint64_t maxTransmittableBits = 0;
//
//    /**
//     * Internal queue datastructure.
//     */
//    cQueue queue;
//
//    /**
//     * Output gate reference.
//     */
//    cGate *outGate;
//
//    cMessage requestPacketMsg = cMessage("requestPacket");
//
//    simsignal_t rcvdPkSignal;
//    simsignal_t enqueuePkSignal;
//    simsignal_t dequeuePkSignal;
//    simsignal_t dropPkByQueueSignal;
//    simsignal_t queueingTimeSignal;
//    simsignal_t queueLengthSignal;

protected:
//    virtual void initialize() override;
    virtual void initialize() override;

    cGate *outGate;
/**  Gateschedule. Is never null. */
    PIFOSchedule<GateBitvector>* gateSchedule;
    /** Index for the current entry in the schedule. */
    unsigned int scheduleIndex;
    cModule *PifoQueuing;
    std::map <std::string,std::vector<int>> destMac_indexmap;
    std::map <std::string,std::vector<int>> flow_indexmap;
    std::map <short,std::vector<int>> VlanId_indexmap;
//  EV_INFO << "Gatename: " <<  gatecontroller->Gatename << endl;
    std::map<std::string,long> TxTimeList;
    double Rate = 1* 1e9 * 1e-12; // rate = 1Gbit/s = 1bit/ns = 0.001bit/ps
    std::vector<long> rank_vector;
    int first_flag = 1;
    std::string flowflag;//destmac+vlanid
    long CycleTime;
//
    virtual void handleMessage(cMessage* msg) override;

    virtual void enqueue(cPacket* packet) override;
    virtual int getFlowid(cPacket* packet);
    virtual long rankCompute(cPacket* packet);
    virtual std::map <std::string,std::vector<int>> getDestMacMap(PIFOSchedule<GateBitvector>* gatecurrentSchedule);
    virtual std::map <short,std::vector<int>> getVlanIdMap(PIFOSchedule<GateBitvector>* gatecurrentSchedule);
    virtual std::map <std::string,std::vector<int>> getflowMap(PIFOSchedule<GateBitvector>* gatecurrentSchedule);
    virtual std::string getflowflag(std::string destmac,short vlanId);
    virtual void flowEntryinit();
    virtual long getStarttime(int indexs);
    virtual long getEndtime(int indexs);
//    virtual cPacket* dequeue();
//
//    virtual void handleRequestPacketEvent(uint64_t maxBits);
//
//    virtual void handlePacketEnqueuedEvent(cPacket* packet);

public:
    virtual ~PIFOQueue();

//    virtual bool isEmpty(uint64_t maxBits);
//
//    virtual void requestPacket(uint64_t maxBits);
//
//    virtual bool isExpressQueue();
};

} // namespace nesting

#endif
