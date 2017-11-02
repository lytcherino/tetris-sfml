
#include <string>
#include <map>
#include <memory>
#include <assert>

template<typename Resource, typename Identifier>
class ResourceHolder
{
public:
  void load(Identifier id, const std::string& filename);
  Resource& get(Identifier id);
  Resource get(Identifier id);

private:
  std::map<Identifier, std::unique_ptr<Resource>> m_ResourceMap;
};

#include "ResourceHolder.inl"
