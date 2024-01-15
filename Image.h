#ifndef Image_H
#define Image_H

#include <iostream>
#include <string>
#include <vector>
#include <stdint.h>
#include <functional>
/** in the incorrected header file the functional header was missing
 *  Include necessary headers for used features.
 *  E.g., #include <iostream>  // Include this at the beginning of your Image.cpp file
 *  If you have using namespace std; in your code, remove it to avoid potential conflicts and explicitly use std::.
 *  E.g., <functional> for std::function, <string_view> for std::string_view.
 *  */

/** the following headers are added includes for q2-4 */
#include <algorithm>
#include <iterator>
#include <QDebug>


class Image;
using ubyte = uint8_t;
using filter = std::function<Image(const Image &, unsigned int)>;

class Image
{
private:
  unsigned int rows, cols;
  std::vector<ubyte> elements;
  std::string name;
  bool binary;
  std::vector<filter> filters;

public:
  explicit Image(unsigned int r, unsigned int c, std::string_view n = "", bool bin=false);
  Image(const Image& other);
  Image(Image&& Image) noexcept = default;
  ~Image() =default;
  Image& operator=(const Image& rhs) = default;
  Image& operator=(Image&& rhs) noexcept = default;
  unsigned int getSize() const { return cols * rows; };
  unsigned int getcols() const { return cols; };
  unsigned int getrows() const { return rows; };
  bool getBinary() const;
  void setBinary(bool newBinary);
  auto begin() {return elements.begin();};
  auto end() {return elements.end();};
  auto cbegin() const {return elements.cbegin();};
  auto cend() const {return elements.cend();};
  ubyte& operator[](unsigned int index);
  const ubyte& operator[](unsigned int index) const;
  ubyte & getPixel(unsigned int row, unsigned int col);
  const ubyte & getPixel(unsigned int row, unsigned int col) const;
  const std::string &getName() const {return name;};

  void showT(std::ostream & os, std::string delim= "") const;
  void showG(int rectSize = 10) const;
  /** the incorrected file was missing headers reqruied for showG method
   *  Include necessary Qt headers for QImage, QColor, QPixmap, and QMessageBox.
   *  */
  void addFilter(filter & f) {filters.push_back(f);};
  void shiftHor(int columns);
  void shiftVert(int rowsDelta);
  void shiftToOrigin(const ubyte& value);
  /** in the incorrected files
   *  The method shiftToOrigin(const ubyte &value); is declared twice. Remove one declaration.
   *  */
  unsigned int sumRegion(const std::vector<ubyte>::const_iterator &pos, int regSize) const;
  /** the incorrected sumRegion was missing const keyword. const keyword can avoid undesired copies */
  Image processAll(unsigned int regSize);

  /** Added functions */
  void setElements(const std::vector<ubyte>& newElements);
};

/** Added standalone function ( alternatively, static member function) to match the filter type requriement */
Image nextState(const Image &currentImage, unsigned int regSize);

#endif
