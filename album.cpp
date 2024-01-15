#include "album.h"

Album::Album(std::string albumName): name{albumName}
{

}

bool Album::putInAlbum(Image &&im)
{
  auto [it, success] = images.insert({im.getName(), std::move(im)});
  return success;
}

std::optional<Image> Album::removeFromAlbum(const std::string name)
{
    auto result = images.extract(name);
    if (result.empty())
      return std::nullopt;
    else
      return std::move(result.mapped());
}

const std::string &Album::getName() const
{
  return name;
}

void Album::playAll(int rectSize) const
{
  for (auto it = images.begin(); it != images.end(); ++it)
    (*it).second.showG(rectSize);
    /**
     *  the incorrected code was:
     *      it->showG(rectSize);
     *  In the playAll method, it->second.showG(rectSize); should be used instead of it->showG(rectSize);,
     *  as it is an iterator to a std::map pair, and the Image object is the second element of the pair.
     *  */
}

