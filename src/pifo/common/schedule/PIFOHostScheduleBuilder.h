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

#ifndef PIFO_COMMON_SCHEDULE_HOSTSCHEDULEBUILDER_H_
#define PIFO_COMMON_SCHEDULE_HOSTSCHEDULEBUILDER_H_

#include <omnetpp.h>



#include "inet/linklayer/ethernet/EtherFrame_m.h"
#include "inet/linklayer/common/EtherType_m.h"
#include "inet/linklayer/common/MacAddressTag_m.h"

#include "nesting/ieee8021q/Ieee8021q.h"
//#include "nesting/linklayer/common/Ieee8021QCtrl.h"
#include "nesting/common/schedule/HostScheduleBuilder.h"
#include "pifo/common/schedule/PIFOHostSchedule.h"

using namespace omnetpp;
//using namespace nesting;
namespace nesting {

/**
 * @deprecated
 * Utility class to build schedules from e.g. XML files.
 */
class PIFOHostScheduleBuilder final {
public:
    /**
     * Creates a schedule for a host containing sendtime, size and the object to be sent
     *
     * TODO link to XML file specification
     */
    static PIFOHostSchedule<Ieee8021QCtrl>* createHostScheduleFromXML(
            cXMLElement *xml, cXMLElement *rootXml);
};

} // namespace nesting

#endif /* NESTING_COMMON_SCHEDULE_HOSTSCHEDULEBUILDER_H_ */
