#include "work_packet.h"

WorkPacket::WorkPacket(int _id) {
    id = _id;
}

WorkPacket::~WorkPacket() {
}

int WorkPacket::getId() {
    return id;
}