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

#include "PIFOHostScheduleBuilder.h"

namespace nesting {

PIFOHostSchedule<Ieee8021QCtrl>* PIFOHostScheduleBuilder::createHostScheduleFromXML(
        cXMLElement *xml, cXMLElement *rootXml) {
    PIFOHostSchedule<Ieee8021QCtrl>* schedule = new PIFOHostSchedule<Ieee8021QCtrl>();

    // extract cycle time of host
    simtime_t cycle = simTime().parse(
            xml->getFirstChildWithTag("cycle")->getNodeValue());
    schedule->setCycle(cycle);

    std::vector<cXMLElement*> entries = xml->getChildrenByTagName("entry");
    for (cXMLElement* entry : entries) {
        // Get time
        const char* timeCString =
                entry->getFirstChildWithTag("start")->getNodeValue();
        simtime_t time = simTime().parse(timeCString);
        if (time > cycle) {
            throw cRuntimeError("Frame is scheduled after its host cycle ends!");
        }
        // Get size
        const char* sizeCString = entry->getFirstChildWithTag("size")->getNodeValue();
        unsigned size = static_cast<unsigned>(std::ceil(cNedValue::parseQuantity(sizeCString, "B")));

        // extract busrt number of host modified by renjie
        const char* BurstCString = entry->getFirstChildWithTag("burst")->getNodeValue();
        unsigned numPacketsPerBurst = atoi(BurstCString);

        // Get Ieee8021QCtrl
        Ieee8021QCtrl header;
        header.q1Tag = VLANTagReq();
        header.macTag = inet::MacAddressReq();
        const char* queueCString =
                entry->getFirstChildWithTag("queue")->getNodeValue();
        header.q1Tag.setPcp(atoi(queueCString));

        short vlanId;
        cXMLElement* vlanIdXmlElement = entry->getFirstChildWithTag("vlanId") ;
        if (vlanIdXmlElement == nullptr){
            vlanId = kDefaultVID; //kDefaultVID;
        }
        else{
            vlanId = atoi(vlanIdXmlElement->getNodeValue());
        }

        const char* addressCString =
                entry->getFirstChildWithTag("dest")->getNodeValue();

        inet::MacAddress destination = inet::MacAddress(addressCString);
        header.macTag.setDestAddress(destination);
        // etherctrl.setTagged(true); no tagged in Ieee802_1QHeader
        header.q1Tag.setVID(vlanId);
        header.q1Tag.setDe(false);

        const char* flowIdCString = entry->getFirstChildWithTag("flowId")->getNodeValue();
        header.flowId = atoi(flowIdCString);

        schedule->addEntry(time, size, numPacketsPerBurst, header);
    }

    return schedule;
}

} // namespace nesting

