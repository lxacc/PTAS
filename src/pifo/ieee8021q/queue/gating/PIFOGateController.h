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

#ifndef PIFO_MAIN_GATECONTROLLER_H_
#define PIFO_MAIN_GATECONTROLLER_H_

#include <omnetpp.h>

#include <memory>
#include <string>
#include <vector>

#include "pifo/common/schedule/PIFOSchedule.h"

#include "inet/common/ModuleAccess.h"
#include "inet/common/InitStages.h"
#include "inet/linklayer/ethernet/EtherMacFullDuplex.h"

#include "pifo/common/schedule/PIFOScheduleFactory.h"

#include "nesting/linklayer/framePreemption/EtherMACFullDuplexPreemptable.h"
#include "nesting/ieee8021q/Ieee8021q.h"
#include "nesting/ieee8021q/queue/TransmissionSelection.h"
#include "nesting/ieee8021q/queue/gating/TransmissionGate.h"
#include "nesting/common/time/IClock.h"
#include "nesting/common/time/IClockListener.h"

using namespace omnetpp;
//using namespace nesting;

class TransmissionGate;
class EtherMACFullDuplexPreemptable;

namespace nesting {
// Schedule<GateBitvector>* Schedule;
/**
 * See the NED file for a detailed description
 */
class PIFOGateController: public GateController {
private:
    /** Current schedule. Is never null. */
    PIFOSchedule<GateBitvector>* currentSchedule;

    /**
     * Next schedule to load after the current schedule finishes it's cycle.
     * Can be null.
     */
    PIFOSchedule<GateBitvector>* nextSchedule;

    /** Index for the current entry in the schedule. */
    unsigned int scheduleIndex;

    /**
     * Clock reference, needed to get the current time and subscribe
     * clock events.
     */
    IClock* clock;

    /**
     * Specifies the cycle start time.
     */
    simtime_t cycleStart;

    /** Reference to transmission gate vector module */
    std::vector<nesting::TransmissionGate*> transmissionGates;

    nesting::EtherMACFullDuplexPreemptable* preemptMacModule;
    inet::EtherMacFullDuplex* macModule;
    std::string switchString;
    std::string portString;
    simtime_t lastChange;

    cMessage updateScheduleMsg = cMessage("updateSchedulePifo") ;
protected:
    /** @see cSimpleModule::initialize(int) */
    virtual void initialize(int stage) override;

    /** Schedules the next tick */
    virtual simtime_t scheduleNextTickEvent();

    /** @see cSimpleModule::numInitStages() */
    virtual int numInitStages() const override;

    /** @see cSimpleModule::handleMessage(cMessage*) */
    virtual void handleMessage(cMessage *msg) override;

    /** Opens all transmission gates. */
    virtual void openAllGates(); // TODO use setGateStates internal

    virtual void setGateStates(GateBitvector bitvector, bool release);

    virtual void updateSchedule() override;

public:
    virtual ~PIFOGateController();
//    std::string Gatename = "testing"; // test

    /** @see IClockListener::tick(IClock*) */
    virtual void tick(IClock *clock, short kind) override;

    /** Calculate the maximum bit size that can be transmitted until the next gate state change.
     *  Returns an unsigned integer value.
     **/
    virtual unsigned int calculateMaxBit(int gateIndex);

    /** extracts and loads the correct schedule from xml file, or an empty one if none is defined */
    virtual void loadScheduleOrDefault(cXMLElement* xml);

    virtual bool currentlyOnHold();

    PIFOSchedule<GateBitvector>* getCurrentSchedule() {
        return currentSchedule;
    }

    unsigned int getScheduleIndex() const {
        return scheduleIndex;
    }
};

} // namespace nesting

#endif
