#include "LinkData.hpp"

LinkData::LinkData() {}
LinkData::~LinkData() {}

void LinkData::Add(LinkFunction func, GameObject::StaticLinkable* objectFrom, GameObject::StaticLinkable* objectTo) {
    Link link;
    link.func = func;
    link.objectFrom = objectFrom;
    link.objectTo = objectTo;
    links.push_back(link);
}
