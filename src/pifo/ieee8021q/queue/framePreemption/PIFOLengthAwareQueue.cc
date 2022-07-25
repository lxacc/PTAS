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

#include "pifo/ieee8021q/queue/framePreemption/PIFOLengthAwareQueue.h"

namespace nesting {

Define_Module(PIFOLengthAwareQueue);

PIFOLengthAwareQueue::~PIFOLengthAwareQueue() {
    cancelEvent(&requestPacketMsg);
    while (!queue.isEmpty()) {
        delete queue.pop();
    }
    queue.clear();
}

void PIFOLengthAwareQueue::initialize() {
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
    tsAlgorithm = getModuleFromPar<nesting::TSAlgorithm>(
            par("transmissionSelectionAlgorithmModule"), this);

    // statistics
    emit(queueLengthSignal, queue.getLength());
}

void PIFOLengthAwareQueue::handleMessage(cMessage* msg) {
    EV_INFO << "PIFOLengthAwareQueue::handleMessage " << endl;
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

void PIFOLengthAwareQueue::enqueue(cPacket* packet) {
    if (availableBufferCapacity >= packet->getBitLength()) {
        emit(enqueuePkSignal, packet->getTreeId());
        numPacketsEnqueued++;
        queue.insert(packet);
        availableBufferCapacity -= packet->getBitLength();
        handlePacketEnqueuedEvent(packet);
    } else {
        emit(dropPkByQueueSignal, packet->getTreeId());
        numPacketsDropped++;
        handlePacketEnqueuedEvent(packet);
        delete packet;
    }
    emit(queueLengthSignal, queue.getLength());
}

cPacket* PIFOLengthAwareQueue::dequeue() {
    if (queue.isEmpty()) {
        return nullptr;
    }

    cPacket* packet = static_cast<cPacket*>(queue.pop());
    availableBufferCapacity += packet->getBitLength();
    
    emit(queueLengthSignal, queue.getLength());

    return packet;
}

void PIFOLengthAwareQueue::handleRequestPacketEvent(uint64_t maxBits) {
    ASSERT(!isEmpty(maxBits));

    cPacket* nextPacket = static_cast<cPacket*>(queue.front());
    EV_INFO << getFullPath() << ": Packet requested with max length of "
                    << maxBits << "bits. Next packet has "
                    << static_cast<uint64_t>(nextPacket->getBitLength())
                    << "bits." << endl;

    cPacket* packetToSend = dequeue();

    emit(dequeuePkSignal, packetToSend->getTreeId());
    emit(queueingTimeSignal, simTime() - packetToSend->getArrivalTime());
    
    send(packetToSend, "out");
}

void PIFOLengthAwareQueue::handlePacketEnqueuedEvent(cPacket* packet) {
    EV_TRACE << getFullPath() << ": Handle packet-enqueued event." << endl;
    tsAlgorithm->packetEnqueued();
}

bool PIFOLengthAwareQueue::isEmpty(uint64_t maxBits) {
    if (queue.isEmpty()) {
        return true;
    }

    cPacket* nextPacket = static_cast<cPacket*>(queue.front());

    // Overhead 8Byte from preamble
    unsigned preambleSize = 8*8;
    return static_cast<uint64_t>(nextPacket->getBitLength() + preambleSize) > maxBits;
}

void PIFOLengthAwareQueue::requestPacket(uint64_t maxBits) {
    Enter_Method("requestPacket(maxBits)");
    maxTransmittableBits = maxBits;
    cancelEvent(&requestPacketMsg);
    scheduleAt(simTime(), &requestPacketMsg);
}
bool PIFOLengthAwareQueue::isExpressQueue() {
    return expressQueue;
}
}
// namespace nesting
