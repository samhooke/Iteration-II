#ifndef LINKDATA_HPP_INCLUDED
#define LINKDATA_HPP_INCLUDED

#include "ObjectsBase.hpp"
#include <vector>

enum class LinkFunction {Set, SetInv};

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
    void Add(LinkFunction func, GameObject::StaticLinkable* objectFrom, GameObject::StaticLinkable* objectTo);

    std::vector<Link> links;
};

#endif // LINKDATA_HPP_INCLUDED
