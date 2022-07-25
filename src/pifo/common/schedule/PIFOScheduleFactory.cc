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

#include "inet/networklayer/common/L3AddressResolver.h"

#include <cstring>
#include <stdexcept>
#include <sstream>
#include <string>
#include "PIFOScheduleFactory.h"



namespace nesting {

PIFOSchedule<GateBitvector>* PIFOScheduleFactory::createGateBitvectorSchedule(cXMLElement *xml)
{
    PIFOSchedule<GateBitvector>* schedule = new PIFOSchedule<GateBitvector>();

    const char* cycleTime = xml->getAttribute("cycleTime");
    if (cycleTime != nullptr) {
        schedule->setCycleTime(SimTime::parse(cycleTime));
    }

    std::vector<cXMLElement*> entries = xml->getChildrenByTagName("entry");
    for (cXMLElement* entry : entries) {
        // Get length
        const char* lengthCString =
                entry->getFirstChildWithTag("length")->getNodeValue();
        simtime_t length = simTime().parse(lengthCString);

        // Get bitvector
        const char* bitvectorCString =
                entry->getFirstChildWithTag("bitvector")->getNodeValue();
        std::string originalVector = std::string(bitvectorCString);
        GateBitvector bitvector = GateBitvector(originalVector);

        // Get dest mac address
        std::string mac = Default_Mac;
        cXMLElement* MacXmlElement = entry->getFirstChildWithTag("macaddress");
        if (MacXmlElement == nullptr){
            EV << "MAc is empty, it's default value is : " << Default_Mac << endl;
        }
        else{
        mac = MacXmlElement->getNodeValue();
        }

        // Get vlanId
        short vlanId = Default_VlanId;
        cXMLElement* VlanXmlElement = entry->getFirstChildWithTag("vlanId");
        if (VlanXmlElement == nullptr){
            EV << "vlanId is empty, it's default value is : " << Default_VlanId << endl;
        }
        else{
        vlanId = atoi(VlanXmlElement->getNodeValue());
        }

        schedule->addControlListEntry(length, bitvector, mac, vlanId);

        EV << "**** PIFOScheduleFactory::createGateBitvectorSchedule :****" <<  "\n" ;
        EV << " length: " << length << " bitvector: " << bitvector  << " destmac: " << mac << " vlanId: " << vlanId  << endl;
    }

    if (schedule->getSumTimeIntervals() > schedule->getCycleTime()) {
        EV_WARN << "PIFOSchedule total Length is greater than Cycle length" <<endl;
    }

    return schedule;
}

PIFOSchedule<GateBitvector>* PIFOScheduleFactory::createGateSchedule(cXMLElement *xml)
{
    PIFOSchedule<GateBitvector>* schedule = new PIFOSchedule<GateBitvector>();

    // Parse BaseTime, CycleTime, CycleTimeExtension
    schedule->setBaseTime(getBaseTimeAttribute(xml));
    schedule->setCycleTime(getCycleTimeAttribute(xml));
    schedule->setCycleTimeExtension(getCycleTimeExtensionAttribute(xml));

    // Parse schedule entries
    std::vector<cXMLElement*> entries = xml->getChildrenByTagName("event");
    for (cXMLElement* entry : entries) {
        GateBitvector gateBitvector = getGateBitvectorAttribute(entry);
        simtime_t timeInterval = getTimeIntervalAttribute(entry);
       // std::string mac = getMacaddress
        schedule->addControlListEntry(timeInterval, gateBitvector);
    }

    return schedule;
}

PIFOSchedule<GateBitvector>* PIFOScheduleFactory::createDefaultBitvectorSchedule(cXMLElement *xml)
{
    PIFOSchedule<GateBitvector>* schedule = new PIFOSchedule<GateBitvector>();
    const char* lengthCString =
            xml->getFirstChildWithTag("defaultcycle")->getNodeValue();
    simtime_t length = simTime().parse(lengthCString);
    std::string gateString(kMaxSupportedQueues, '1');
    GateBitvector bitvector = GateBitvector(gateString);
    schedule->addControlListEntry(length, bitvector);
    schedule->setCycleTime(length);
    return schedule;
}

PIFOSchedule<SendDatagramEvent>* PIFOScheduleFactory::createDatagramSchedule(cXMLElement *xml)
{
    PIFOSchedule<SendDatagramEvent>* schedule = new PIFOSchedule<SendDatagramEvent>();

    // Parse BaseTime, CycleTime, CycleTimeExtension
    schedule->setBaseTime(getBaseTimeAttribute(xml));
    schedule->setCycleTime(getCycleTimeAttribute(xml));
    schedule->setCycleTimeExtension(getCycleTimeExtensionAttribute(xml));

    // Parse schedule entries
    std::vector<cXMLElement*> entries = xml->getChildrenByTagName("event");
    for (cXMLElement* entry : entries) {
        SendDatagramEvent evt;
        evt.setDestAddress(getDestAddressAttribute(entry));
        evt.setDestPort(getDestPortAttribute(entry));
        evt.setPriorityCodePoint(getPriorityCodePointAttribute(entry));
        evt.setDropEligible(getDropEligibleIndicatorAttribute(entry));
        evt.setVlanId(getVlanIdAttribute(entry));
        evt.setPayloadSize(getPayloadSizeAttribute(entry));
        simtime_t timeInterval = getTimeIntervalAttribute(entry);
        schedule->addControlListEntry(timeInterval, evt);
    }

    return schedule;
}

simtime_t PIFOScheduleFactory::getBaseTimeAttribute(cXMLElement* xml)
{
    const char* baseTime = xml->getAttribute("baseTime");
    if (baseTime != nullptr) {
        return SimTime::parse(baseTime);
    } else {
        return SimTime::ZERO;
    }
}

simtime_t PIFOScheduleFactory::getCycleTimeAttribute(cXMLElement* xml)
{
    const char* cycleTime = xml->getAttribute("cycleTime");
    if (cycleTime == nullptr) {
        throw cRuntimeError("No \"CycleTime\" attribute defined in XML element!");
    }
    return SimTime::parse(cycleTime);
}

simtime_t PIFOScheduleFactory::getCycleTimeExtensionAttribute(cXMLElement* xml)
{
    const char* cycleTimeExtension = xml->getAttribute("cycleTimeExtension");
    if (cycleTimeExtension != nullptr) {
        return SimTime::parse(cycleTimeExtension);
    } else {
        return SimTime::ZERO;
    }
}

GateBitvector PIFOScheduleFactory::getGateBitvectorAttribute(cXMLElement* xml)
{
    const char* gateStates = xml->getAttribute("gateStates");
    if (gateStates == nullptr) {
        throw cRuntimeError("No \"GateStates\" attribute defined in XML element!");
    }
    return GateBitvector(gateStates);
}

simtime_t PIFOScheduleFactory::getTimeIntervalAttribute(cXMLElement* xml)
{
    const char* timeInterval = xml->getAttribute("timeInterval");
    if (timeInterval == nullptr) {
        throw cRuntimeError("No \"TimeInterval\" attribute defined in XML element!");
    }
    return SimTime::parse(timeInterval);
}

L3Address PIFOScheduleFactory::getDestAddressAttribute(cXMLElement* xml)
{
    const char* destAddress = xml->getAttribute("destAddress");
    if (destAddress == nullptr) {
        throw cRuntimeError("No \"DestAddress\" attribute defined in XML element!");
    }
    return L3AddressResolver().resolve(destAddress);
}

uint64_t PIFOScheduleFactory::getDestPortAttribute(cXMLElement* xml)
{
    const char* destPort = xml->getAttribute("destPort");
    if (destPort == nullptr) {
        throw cRuntimeError("No \"DestPort\" attribute defined in XML element!");
    }
    return atoi(destPort);
}

uint64_t PIFOScheduleFactory::getPriorityCodePointAttribute(cXMLElement* xml)
{
    const char* pcp = xml->getAttribute("pcp");
    if (pcp != nullptr) {
        return atoi(pcp);
    } else {
        return SendDatagramEvent().getPriorityCodePoint();
    }
}

bool PIFOScheduleFactory::getDropEligibleIndicatorAttribute(cXMLElement* xml)
{
    const char* de = xml->getAttribute("de");
    if (de != nullptr) {
        return parseBool(de);
    } else {
        return SendDatagramEvent().isDropEligible();
    }
}

uint64_t PIFOScheduleFactory::getVlanIdAttribute(cXMLElement* xml)
{
    const char* vid = xml->getAttribute("vid");
    if (vid != nullptr) {
        return atoi(vid);
    } else {
        return SendDatagramEvent().getVlanId();
    }
}

b PIFOScheduleFactory::getPayloadSizeAttribute(cXMLElement* xml)
{
    const char* payloadSize = xml->getAttribute("payloadSize");
    if (payloadSize == nullptr) {
        throw cRuntimeError("No \"PayloadSize\" attribute defined in XML element!");
    } 
    return b(static_cast<int64_t>(std::ceil(cNedValue::parseQuantity(payloadSize, "b"))));
}

bool PIFOScheduleFactory::parseBool(const char* cstring)
{
    if (std::strcmp(cstring, "True") == 0 || std::strcmp(cstring, "true") == 0|| std::strcmp(cstring, "1") == 0) {
        return true;
    } else if (std::strcmp(cstring, "false") == 0 || std::strcmp(cstring, "False") == 0 || std::strcmp(cstring, "0") == 0) {
        return false;
    } else {
        std::ostringstream buffer;
        buffer << "Failed to parse bool value from string \"" << cstring << "\".";
        throw cRuntimeError(buffer.str().c_str());
    }
}

} // namespace nesting
