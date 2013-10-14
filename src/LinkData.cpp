#include "LinkData.hpp"

LinkData::LinkData() {}
LinkData::~LinkData() {}

void LinkData::Add(GameObject::StaticLinkable* objectFrom, LinkFunction func, GameObject::StaticLinkable* objectTo) {
    Link link;
    link.func = func;
    link.objectFrom = objectFrom;
    link.objectTo = objectTo;
    links.push_back(link);
}

void LinkData::Update() {
    // Loop through all Link in links
    // Update all objectTo based upon objectFrom
    for (int i = 0; i < (int)links.size(); i++) {
        LinkFunction func = links[i].func;

        switch (func) {
        case LinkFunction::SetEqual:
            links[i].objectTo->state = links[i].objectFrom->state;
            break;
        case LinkFunction::SetInverse:
            links[i].objectTo->state = !links[i].objectFrom->state;
            break;
        }
    }
}
