#ifndef LINKDATA_HPP_INCLUDED
#define LINKDATA_HPP_INCLUDED

#include "ObjectsBase.hpp"
#include <vector>

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
};

#endif // LINKDATA_HPP_INCLUDED
