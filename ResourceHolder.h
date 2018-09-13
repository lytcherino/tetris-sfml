#ifndef RESOURCE_HOLDER_H
#define RESOURCE_HOLDER_H

#include <map>
#include <memory>
#include <cassert>
#include <string>

template<typename Resource, typename Identifier>
class ResourceHolder
{
public:
  void load(Identifier id, const std::string& filename);
  void insert(Identifier id, Resource res);

  Resource& get(Identifier id);
  const Resource& get(Identifier id) const;

private:
  std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insert(Identifier id, Resource res)
{
  std::unique_ptr<Resource> resource = std::make_unique<Resource>();
  auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
  assert(inserted.second);
}

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
  std::unique_ptr<Resource> resource(new Resource());
  if (!resource->loadFromFile(filename)) {
    throw std::runtime_error("ResourceHolder::load - Failed to load file" + filename);
  }
  auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
  assert(inserted.second);
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
  return mResourceMap[id];
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
  return mResourceMap[id];
}

#endif
