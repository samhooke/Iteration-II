#include "LinkData.hpp"

LinkData::LinkData() {}
LinkData::~LinkData() {}

void LinkData::GiveReferenceToStaticLinkableObject(GameObject::StaticLinkable* obj) {
    staticLinkableObjects.push_back(obj);
}

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

void LinkData::SnapshotTake() {
    snapshotData.clear();

    // Take a snapshot, store it in snapshotData
    for (int i = 0; i < (int)staticLinkableObjects.size(); i++) {
        GameObject::StaticLinkable* obj = staticLinkableObjects[i];
        snapshotData.push_back(obj->state);
    }
}

// After calling SnapshotTake(), the following function can be called to determine
// which objects have changed states. The argument `matchTag` filters only objects
// that match that tag. The argument `matchState` fitlers only objects that match
// that state. As an example:
//
// SnapshotTake();
// // Do stuff that changes states...
// std::vector<GameObject::StaticLinkable*> statesChanged = SnapshotDiff(TAG_DOOR, STATE_DOOR_SHUT);
//
// The above function example would populate `statesChanged` with all the objects whose
// tag is TAG_DOOR whose state changed to STATE_DOOR_SHUT after SnapshotTake() was called!
std::vector<GameObject::StaticLinkable*> LinkData::SnapshotDiff(std::string matchTag, bool matchState) {

    std::vector<GameObject::StaticLinkable*> stateChanged;

    // Compare current situation to previous snapshot
    for (int i = 0; i < (int)staticLinkableObjects.size(); i++) {
        GameObject::StaticLinkable* obj = staticLinkableObjects[i];
        if (snapshotData[i] != obj->state) {
            // The state changed!

            // Check it matches the required tag and state
            if (obj->tag == matchTag && obj->state == matchState)
                stateChanged.push_back(obj);
        }
    }

    return stateChanged;
}
