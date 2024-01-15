#ifndef ALBUM_H
#define ALBUM_H
#include <string>
#include <map>
#include <memory>
#include "Image.h"

/** original album.h was missing optional and map header */
#include <optional>
#include <map>

  /** added for question five*/

class Album
{
public:
  Album(std::string albumName);
  bool putInAlbum(Image &&im);
  std::optional<Image> removeFromAlbum(const std::string name); /** added const keyword */
  const std::string &getName() const;
  void playAll(int rectSize = 10) const;

  /** added for question five*/
private:
  const std::string name;
  std::map<std::string, Image> images;
  /** added for question five*/
};

#endif // ALBUM_H
