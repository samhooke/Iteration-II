#ifndef LINKDATA_HPP_INCLUDED
#define LINKDATA_HPP_INCLUDED

#include "ObjectsBase.hpp"
#include <vector>
#include <string>

enum class LinkFunction {SetEqual, SetInverse};

struct Link {
    LinkFunction func;
    GameObject::StaticLinkable* objectFrom;
    GameObject::StaticLinkable* objectTo;
};

class LinkData {
public:
    LinkData();
    ~LinkData();

    void Update();
    void Add(GameObject::StaticLinkable* objectFrom, LinkFunction func, GameObject::StaticLinkable* objectTo);
    std::vector<Link> links;

    void GiveReferenceToStaticLinkableObject(GameObject::StaticLinkable* obj);
    std::vector<GameObject::StaticLinkable*> staticLinkableObjects; // List of all GameObject::StaticLinkable

    void SnapshotTake();
    std::vector<GameObject::StaticLinkable*> SnapshotDiff(std::string matchTag, bool matchState);

private:
    std::vector<bool> snapshotData;
};

#endif // LINKDATA_HPP_INCLUDED
