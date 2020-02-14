#include "JDTestService.h"
#include "CodalDmesg.h"

using namespace codal;

JDTestService::JDTestService(ManagedString serviceName, JDServiceMode m) : JDService(JD_SERVICE_IDENTIFIER_CONTROL_TEST, m), name(serviceName)
{
}

int JDTestService::handlePacket(JDPacket* p)
{
    DMESG("REC N: %d F: %d->%d N: %s M: %c%c%c", *((uint32_t*)p->data), (uint32_t)p->device_identifier, p->service_number, this->name.toCharArray(), (this->mode == ClientService) ? "C":"", (this->mode == HostService) ? "H":"", (this->mode == BroadcastService) ? "B":"");
    return DEVICE_OK;
}

void JDTestService::sendTestPacket(uint32_t value)
{
    if (!this->device)
        return;
    DMESG("SEND: %d FROM: %d", value, (uint32_t)this->device->device_identifier);
    send((uint8_t*)&value, sizeof(uint32_t));
}