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

#include "pifo/ieee8021q/queue/framePreemption/PIFOQueue.h"
#include "pifo/common/schedule/PIFOSchedule.h"

#include "nesting/linklayer/vlan/EnhancedVlanTag_m.h"
#include "nesting/common/FlowMetaTag_m.h"
#include "nesting/ieee8021q/queue/QueuingFrames.h"
#include "nesting/ieee8021q/Ieee8021q.h"

#include "../gating/PIFOGateController.h"
#define Unit SIMTIME_PS// simtime to long 10-12
//#include "nesting/ieee8021q/queue/framePreemption/sys_inc.h"
//#include "/usr/local/include/list.h"
//#include </usr/src/linux-headers-4.15.0-142/include/linux/list.h>

namespace nesting {

Define_Module(PIFOQueue);

PIFOQueue::~PIFOQueue() {
    cancelEvent(&requestPacketMsg);
    while (!queue.isEmpty()) {
        delete queue.pop();
    }
    queue.clear();
}

void PIFOQueue::initialize() {
    rcvdPkSignal = registerSignal("rcvdPk");
    enqueuePkSignal = registerSignal("enqueuePk");
    dequeuePkSignal = registerSignal("dequeuePk");
    dropPkByQueueSignal = registerSignal("dropPkByQueue");
    queueingTimeSignal = registerSignal("queueingTime");
    queueLengthSignal = registerSignal("queueLength");

    queue.setName(par("queueName"));
    availableBufferCapacity = par("bufferCapacity");
    expressQueue = par("expressQueue");
    WATCH(numPacketsReceived);
    WATCH(numPacketsDropped);
    WATCH(numPacketsEnqueued);
    WATCH(availableBufferCapacity);

    // module references
    tsAlgorithm = getModuleFromPar<TSAlgorithm>(
            par("transmissionSelectionAlgorithmModule"), this);

    // statistics
    emit(queueLengthSignal, queue.getLength());
}
//
void PIFOQueue::handleMessage(cMessage* msg) {
    EV_INFO << "PIFOQueue::handleMessage ***************************" << endl;
    if (msg->isSelfMessage()) {
        if (msg == &requestPacketMsg) {
            handleRequestPacketEvent(maxTransmittableBits);
        }
    } else {
        cPacket* packet = check_and_cast<cPacket*>(msg);
        emit(rcvdPkSignal, packet->getTreeId()); // getting tree id, because it doenn't get changed when packet is copied
        numPacketsReceived++;
        enqueue(packet);
    }
}


void PIFOQueue::enqueue(cPacket* packet) {
    //TODO
    long rank = this->rankCompute(packet);
    EV_INFO << "PIFOQueue enqueue*******************************" <<endl;
    EV_INFO << "PIFOQueue enqueue*******************************" <<endl;
    EV_INFO << "PIFOQueue enqueue*******************************" <<endl;
    EV_INFO << "PIFOQueue enqueue*******************************" <<endl;
    EV_INFO << "PIFOQueue enqueue*******************************" <<endl;

    //insert
    if (availableBufferCapacity >= packet->getBitLength()) {
        if (!queue.isEmpty()) {

//            //existing packets in queue
//            int pflowid = this->getFlowid(packet);
//            int queuelen = queue.getLength();
//            if(queuelen<rank_vector.size()){
//                EV_INFO << "some packets dequeued " << endl;
//            }
//            cQueue *q_ptr = &queue;
// //           int iterflag =0;
//            for (cQueue::Iterator iter(*q_ptr); !iter.end(); iter++) {
////                EV_ERROR << getFullPath() << "new iterate " << endl;
//                cPacket *msg = (cPacket *)(*iter);
//                int mflowid = this->getFlowid(msg);
////                EV_ERROR << getFullPath() << ": current itre "
////                                << itreflag++<< ": current flowid "
////                                << pflowid << "Iterator flowid "
////                                << mflowid
////                                << endl;
//
//                if (pflowid < mflowid)
//                {
//                    queue.insertBefore(msg, packet);
////                    EV_ERROR << getFullPath() << "insert before done " << endl;
//                    break;
//                }
//                iter++;
//                if(iter.end())
//                {
//                    queue.insert(packet);
////                    EV_ERROR << getFullPath() << "insert last done " << endl;
//                }
////                else
////                    EV_ERROR << getFullPath() << "no end " << endl;
//                iter--;
//            }
////            itreflag =0;
//
//
//
//        }
//        else{
//            queue.insert(packet);
//            rank_vector.clear();
//        }

            cQueue *q_ptr = &queue;
            int iterflag =0;

            //existing packets in queue
            unsigned  queuelen = 0;
            for (cQueue::Iterator iter(*q_ptr); !iter.end(); iter++) {
                queuelen++;
            }
            if(queuelen<rank_vector.size()){
                EV_INFO << "some packets dequeued " << endl;
                rank_vector.erase(rank_vector.begin(),rank_vector.begin()+rank_vector.size() - queuelen);
            }


            for (cQueue::Iterator iter(*q_ptr); !iter.end(); iter++) {
//                EV_ERROR << getFullPath() << "new iterate " << endl;
                cPacket *msg = (cPacket *)(*iter);
                long msgrank = rank_vector.at(iterflag);
                iterflag++;
//                EV_ERROR << getFullPath() << ": current itre "
//                                << itreflag++<< ": current flowid "
//                                << pflowid << "Iterator flowid "
//                                << mflowid
//                                << endl;

                if (rank < msgrank)
                {
                    queue.insertBefore(msg, packet);
                    rank_vector.insert(rank_vector.begin() + iterflag -1, rank);
//                    EV_ERROR << getFullPath() << "insert before done " << endl;
                    break;
                }
                iter++;
                if(iter.end())
                {
                    queue.insert(packet);
                    rank_vector.push_back(rank);
//                    EV_ERROR << getFullPath() << "insert last done " << endl;
                }
//                else
//                    EV_ERROR << getFullPath() << "no end " << endl;
                iter--;
            }

        }
        else{
            queue.insert(packet);
            rank_vector.clear();
            rank_vector.push_back(rank);
        }

    //below is origin
        emit(enqueuePkSignal, packet->getTreeId());
        numPacketsEnqueued++;
//        queue.insert(packet);
        availableBufferCapacity -= packet->getBitLength();
        handlePacketEnqueuedEvent(packet);
    }
    else {
        emit(dropPkByQueueSignal, packet->getTreeId());
        numPacketsDropped++;
        handlePacketEnqueuedEvent(packet);
        delete packet;
    }
    emit(queueLengthSignal, queue.getLength());
}

int PIFOQueue::getFlowid(cPacket* packet) {

    const Packet* dataMessage = dynamic_cast<const Packet*>(packet);
    const auto& smsg = dataMessage->peekData();
    int flowid = 0;
    for (auto& region : smsg->getAllTags<FlowMetaTag>()) {
        flowid = region.getTag()->getFlowId();
    }
    return flowid;
}

void PIFOQueue::flowEntryinit(){

    outGate = gate("out");
    //    EV_INFO << outGate->getOwnerModule()->getParentModule()->getNedTypeName() << endl;
    PifoQueuing = outGate->getOwnerModule()->getParentModule();
    PIFOGateController *gatecontroller = (PIFOGateController *)(PifoQueuing->getSubmodule("gateController"));
    EV_INFO << "Submodule: " << PifoQueuing->getSubmodule("gateController")->getFullPath() <<endl;
    gateSchedule = gatecontroller->getCurrentSchedule();

//    unsigned LengthOfSchedule = gateSchedule->getControlListLength();
//    EV << "length " <<  LengthOfSchedule << endl;

    scheduleIndex = gatecontroller->getScheduleIndex();
//    EV << "index = " << gatecontroller->getScheduleIndex()<< ": vlanId = " << gateSchedule->getVlanId(scheduleIndex) << endl;
}

long PIFOQueue::rankCompute(cPacket* packet) {
    if(1 == first_flag){
        flowEntryinit();
        destMac_indexmap = this->getDestMacMap(gateSchedule);
        VlanId_indexmap = this->getVlanIdMap(gateSchedule);
        flow_indexmap = this->getflowMap(gateSchedule);
        CycleTime = gateSchedule->getCycleTime().inUnit(Unit);
        first_flag = 0;
    }

    long rank = -1;
//     just for debug test
    std::map <std::string,std::vector<int>> maps = flow_indexmap;
    std::map<std::string,long> TxList = TxTimeList;

    // SimTime  ArriveTime = simTime(); convert may lost the precision
    long ArriveTime = simTime().inUnit(Unit);
    EV  << " time: " << ArriveTime << "\n";
    long packet_length = packet->getBitLength();


   // EV << packet->addTag<MacAddressReq>();
    inet::Packet * recpacket = check_and_cast<inet::Packet *>(packet);
    const auto& frame = recpacket->peekAtFront<inet::EthernetMacHeader>();

   const inet::Ieee8021qHeader* qHeader;
   VlanTagType vlanTagType;//unknow parment

   QueuingFrames *PifoQueueFrames =  (QueuingFrames *)PifoQueuing->getSubmodule("queuingFrames");

   if (PifoQueueFrames->par("vlanTagType").stdstringValue() == "c") {
           vlanTagType = C_TAG;
           qHeader = frame->getCTag();
       } else {
           vlanTagType = S_TAG;
           qHeader = frame->getSTag();
       }


//
////   if (par("vlanTagType").stdstringValue() == "c") {
//          vlanTagType = C_TAG; // vlanTagType = default("c");
//          qHeader = frame->getCTag();
////      } else {
////          vlanTagType = S_TAG;
////          qHeader = frame->getSTag();
////      }

   short vlanId;
   if (!qHeader) {
       vlanId = kDefaultVID;
   } else {
       vlanId = qHeader->getVid();
   }
      EV << " VlanID: " << vlanId ;

    MacAddress mac = frame->getDest();
    std::string mac_str = mac.str();
    EV_INFO << "packet's destmac: " << mac_str <<endl;
//    if(mac_str == "00-00-00-00-01-08"){
//        EV << "----00-00-00-00-01-08" <<endl ;
//        std::string path = PifoQueuing->getFullPath() ;
//        EV << PifoQueuing->getFullPath() << endl;
//    }
    std::string flowflag = this->getflowflag(mac_str, vlanId);


    long lastTxTime = TxTimeList[flowflag];

    if(floor(lastTxTime/(CycleTime)) < floor((ArriveTime) /(CycleTime))){
        lastTxTime = 0;//basetime = 0
    }
    long offset_lastTxTime = lastTxTime % (CycleTime) ;
    long offset_ArriveTime = ArriveTime % (CycleTime) ;

   // int FlowNum = destmac_indexmap.size();

    std::vector<int> indexs;

    if(flow_indexmap.find(flowflag) == flow_indexmap.end()){
        indexs = flow_indexmap[this->getflowflag(Default_Mac, Default_VlanId)]; //default xml entry matched for other packet, whose DestMacaddress isn't in switch's xml entry
    }
    else{
        indexs = flow_indexmap[flowflag];//Flow matched
    }


    std::vector<int>::iterator iter;
    iter = indexs.begin();
    long win_start;
    long win_end;
    while(indexs.end() != iter){
            win_start = getStarttime(*iter);
            win_end = getEndtime(*iter);
            if((offset_ArriveTime < offset_lastTxTime) && (offset_lastTxTime < ( win_end - packet_length/Rate)) ){
                    rank = lastTxTime;
            }
            else if((offset_lastTxTime < offset_ArriveTime) && ( (offset_ArriveTime) < win_start )){
                    rank = win_start + ArriveTime - offset_ArriveTime;
            }
            else if((offset_lastTxTime < offset_ArriveTime) && ( (offset_ArriveTime) < ( win_end - packet_length/Rate))){
                    rank = ArriveTime;
            }
       ++iter;
   }
   if (-1 == rank){
       rank = getStarttime(*(indexs.begin())) + ArriveTime - offset_ArriveTime + CycleTime;
   }


   TxTimeList[mac_str] = rank + packet_length/Rate;

   EV_INFO << "packet_rank : " << rank <<endl;
   return rank;
}

long PIFOQueue::getStarttime(int indexs){
    simtime_t starttime = 0;
    for(int index=0;index<indexs;index++){
        starttime += gateSchedule->getTimeInterval(index);
    }
    return starttime.inUnit(Unit);
}

long PIFOQueue::getEndtime(int indexs){
    simtime_t starttime = 0;
       for(int index=0;index<=indexs;index++){
           starttime += gateSchedule->getTimeInterval(index);
       }
       return starttime.inUnit(Unit);
}

std::map <std::string,std::vector<int>> PIFOQueue::getflowMap(PIFOSchedule<GateBitvector>* gateSchedule){
    std::map <std::string,std::vector<int>> flowmap;
    std::string flowflag;
    for(unsigned index = 0;index<gateSchedule->getControlListLength();index++){
        flowflag = this->getflowflag(gateSchedule->getMacAddress(index), gateSchedule->getVlanId(index));
        flowmap[flowflag].push_back(index);
       }
    return flowmap;
}

std::string PIFOQueue::getflowflag(std::string destmac,short vlanId){
    std::string flowflag;
    flowflag = destmac + std::to_string(vlanId);
    return flowflag;

}

std::map <std::string,std::vector<int>> PIFOQueue::getDestMacMap(PIFOSchedule<GateBitvector>* gateSchedule){
    std::map <std::string,std::vector<int>> destmacmap;
    for(unsigned index = 0;index<gateSchedule->getControlListLength();index++){
        destmacmap[gateSchedule->getMacAddress(index)].push_back(index);
       }
    return destmacmap;
}

std::map <short,std::vector<int>> PIFOQueue::getVlanIdMap(PIFOSchedule<GateBitvector>* gateSchedule){
    std::map <short,std::vector<int>> VlanIdmap;
    for(unsigned index = 0;index<gateSchedule->getControlListLength();index++){
        short vlanid = gateSchedule->getVlanId(index);
        VlanIdmap[vlanid].push_back(index);
       }
    return VlanIdmap;
}



// error
//  std::vector<int> vectors_intersection(std::vector<int> v1, std::vector<int> v2) {
//    std::vector<int> v;
//    sort(v1.begin(), v1.end());
//    sort(v2.begin(), v2.end());
//    set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v));//求交集
//    return v;
//}


//cPacket* PIFOQueue::dequeue() {
//    if (queue.isEmpty()) {
//        return nullptr;
//    }
//
//    cPacket* packet = static_cast<cPacket*>(queue.pop());
//    availableBufferCapacity += packet->getBitLength();
//
//    emit(queueLengthSignal, queue.getLength());
//
//    return packet;
//}
//
//void PIFOQueue::handleRequestPacketEvent(uint64_t maxBits) {
//    ASSERT(!isEmpty(maxBits));
//
//    cPacket* nextPacket = static_cast<cPacket*>(queue.front());
//    EV_INFO << getFullPath() << ": Packet requested with max length of "
//                    << maxBits << "bits. Next packet has "
//                    << static_cast<uint64_t>(nextPacket->getBitLength())
//                    << "bits." << endl;
//
//    cPacket* packetToSend = dequeue();
//
//    emit(dequeuePkSignal, packetToSend->getTreeId());
//    emit(queueingTimeSignal, simTime() - packetToSend->getArrivalTime());
//
//    send(packetToSend, "out");
//}
//
//void PIFOQueue::handlePacketEnqueuedEvent(cPacket* packet) {
//    EV_TRACE << getFullPath() << ": Handle packet-enqueued event." << endl;
//    tsAlgorithm->packetEnqueued();
//}
//
//bool PIFOQueue::isEmpty(uint64_t maxBits) {
//    if (queue.isEmpty()) {
//        return true;
//    }
//
//    cPacket* nextPacket = static_cast<cPacket*>(queue.front());
//
//    // Overhead 8Byte from preamble
//    unsigned preambleSize = 8*8;
//    return static_cast<uint64_t>(nextPacket->getBitLength() + preambleSize) > maxBits;
//}
//
//void PIFOQueue::requestPacket(uint64_t maxBits) {
//    Enter_Method("requestPacket(maxBits)");
//    maxTransmittableBits = maxBits;
//    cancelEvent(&requestPacketMsg);
//    scheduleAt(simTime(), &requestPacketMsg);
//}
//bool PIFOQueue::isExpressQueue() {
//    return expressQueue;
//}
}
// namespace nesting
