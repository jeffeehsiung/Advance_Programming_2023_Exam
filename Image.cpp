#include "Image.h"
#include <stdexcept>
#include <utility>
#include <numeric>
#include <QMessageBox>

bool Image::getBinary() const
{
  return binary;
}

void Image::setBinary(bool newBinary)
{
  binary = newBinary;
}

Image::Image(unsigned int r, unsigned int c, std::string_view n, bool bin) : rows{r}, cols{c}, elements(r*c, 0), name{n}, binary{bin}
{
  /** in the incorrect files, the elements vector was not initialized,
   *  which can lead to undefined and undesired behavior
   *  Constructor Image(unsigned int r, unsigned int c, std::string_view n = "", bool bin=false);
   *  should initialize elements vector with the correct size: elements(r * c, 0).
   *  */
}

Image::Image(const Image & other):
  rows{other.rows}, cols{other.cols}, elements{other.elements}, name{"copy of "+other.name}, binary{other.binary}
{

}

const ubyte& Image::operator[](unsigned int index) const
{
  if (index >= cols * rows)
    throw std::out_of_range {"Index too large: " + std::to_string(index)};

  return elements[index];
}

ubyte& Image::operator[](unsigned int index)
{
  return const_cast<ubyte&>(std::as_const(*this)[index]);
}

ubyte &Image::getPixel(unsigned int row, unsigned int col)
{
  return elements[row*cols+col];
}

const ubyte &Image::getPixel(unsigned int row, unsigned int col) const
{
  return elements[row*cols+col];

}

void Image::showT(std::ostream &os, std::string delim) const
{
  os << "----" << name << "------" << std::endl;
  for (unsigned int row = 0; row < rows; ++row)
    {
      for (unsigned int col = 0; col < cols; ++col)
        os << (int)getPixel(row, col) << delim;
      os << std::endl;
    }
}

void Image::showG(int rectSize) const
{
    /** TODO:
     *  Validate rows and cols are non-zero before creating QImage.
     *  */
  QImage qim(cols, rows, QImage::Format_Grayscale8);
  for (unsigned int row = 0; row < rows; ++row)
    {
      for (unsigned int col = 0; col < cols; ++col)
        {
        auto pix = getPixel(row, col);
        if (binary)
          {
          if (pix == 0) pix = 255;
          if (pix == 1) pix = 0;
          }
        qim.setPixelColor(col, row, QColor(pix, pix, pix));
        }
    }
  qim = qim.scaled(cols*rectSize, rows*rectSize);
  QMessageBox msgBox = QMessageBox();
  msgBox.setText(QString::fromStdString(name));
  msgBox.setIconPixmap(QPixmap::fromImage(qim));
  msgBox.exec();
}

void Image::shiftHor(int columns)
{
  unsigned int rot = columns % cols;
  for (unsigned int row = 0; row < rows; ++row)
    {
      auto start = begin() + row*cols;
      auto stop = start + cols;
      std::rotate(start, start+rot, stop);
    }

}

void Image::shiftVert(int rowsDelta)
{
  auto start = begin() + rowsDelta*cols;
  std::rotate(begin(), start, end());
}

unsigned int Image::sumRegion(const typename std::vector<ubyte>::const_iterator &pos, int regSize) const
{
  unsigned int sum{0};
  auto distance = pos - cbegin();
  unsigned int colPos = distance % cols;
  auto top = pos - regSize * cols;
  auto bottom = pos + regSize* static_cast<int>(cols);
  auto startRow = -regSize;
  auto endRow = regSize;
  while (top < cbegin())
    {
    top += cols;
    ++startRow;
    }
  while (bottom > cend())
    {
    bottom -= cols;
    --endRow;
    }
  for (int row = startRow; row <= endRow; ++row)
    {
      auto start = pos + row * static_cast<int>(cols);
      unsigned int columns{0};
      auto left = regSize + 1;
      do
        {
          --left;
          auto distance = (start-left) - cbegin();
          columns = distance % cols;
        }
      while (columns > colPos);
      auto right = regSize + 1;
      do
        {
          --right;
          auto distance = (start+right) - cbegin();
          columns = distance % cols;
        }
      while (columns < colPos);

      sum = std::accumulate(start-left, start+right+1, sum);
    }
  return sum;
}


Image Image::processAll(unsigned int regSize)
{
  Image result(*this);
  for (auto &f : filters)
    result = f(result, regSize);
  return result;
}

 /** Added functions */
void Image::shiftToOrigin(const ubyte &value) {
  qDebug() << "value is: " << value;
  // Use STL to find the position of the element
  auto it = std::find(elements.begin(), elements.end(), value);

  if (it == elements.end()) {
    return; // Element not found, no shift required
  }

  // Calculate the position in terms of rows and columns
  auto index = std::distance(elements.begin(), it);
  qDebug() << "index is: " << index;
  int elementRow = index / cols;
  int elementCol = index % cols;

  // Calculate the horizontal and vertical shifts required
  int horizontalShift = elementCol; // Shift left by elementCol columns
  int verticalShift = elementRow;   // Shift up by elementRow rows

  // Perform the shifts
  shiftHor(horizontalShift); // Negative value for leftward shift
  shiftVert(verticalShift);  // Negative value for upward shift
}


void Image::setElements(const std::vector<ubyte>& newElements) {
    elements = newElements;
}

/** Standalone functions */
Image nextState(const Image &currentImage, unsigned int regSize) {
    /** `nextState` is a standalone function (not a member of `Image`) that takes an `Image` object and an `unsigned int`
   *  (for region size, though it seems it's not being used as per the Game of Life logic).
   *  It computes the next state based on the Game of Life rules and returns a new `Image` object.
   *
   *  In this implementation, for each cell in the current image,
   *  we calculate the number of live neighbors and apply the rules of the Game of Life:
   *  A live cell with fewer than two or more than three live neighbors dies.
   *  A live cell with two or three live neighbors lives on.
   *  A dead cell with exactly three live neighbors becomes alive.
   *  The resulting state of each cell is stored in newElements,
   *  which is then used to create a new Image object that represents the next state of the Game of Life simulation.
   *
   *  The sumRegion method is used to count live neighbors.
   *  It's important that this function is implemented correctly for the Game of Life logic to work as expected.
   *  This function should calculate the sum of the values of all cells in a region around the given cell, including the cell itself,
   *  which is why we subtract the value of the current cell (currentImage.getPixel(row, col)) from the sum.
   *
   *  'std::vector<ubyte> called newElements'
   *  is necessary because we cannot modify the elements vector in-place while we are still reading its current state to determine the next state.
   *  After computing newElements, we assign it back to elements, which involves moving the data from newElements to elements.
   *  This move operation is efficient in C++ and does not involve deep copying the entire vector.
   *  */
    unsigned int rows = currentImage.getrows();
    unsigned int cols = currentImage.getcols();
    std::vector<ubyte> newElements(rows * cols, 0);

    for (unsigned int row = 0; row < rows; ++row) {
        for (unsigned int col = 0; col < cols; ++col) {
              int liveNeighbors = currentImage.sumRegion(currentImage.cbegin() + row * cols + col, regSize) - currentImage.getPixel(row, col);
              bool isAlive = currentImage.getPixel(row, col) == 1;

              // Applying the Game of Life rules
              if (isAlive && (liveNeighbors == 2 || liveNeighbors == 3)) {
              // Any live cell with two or three live neighbors lives on to the next generation
              newElements[row * cols + col] = 1;
              } else if (!isAlive && liveNeighbors == 3) {
              // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction
              newElements[row * cols + col] = 1;
              }
              // All other live cells die in the next generation. Similarly, all other dead cells stay dead
              // The default state of elements in newElements is already 0 (dead), so no need to explicitly set it
        }
    }

    Image result(rows, cols, "NextState", currentImage.getBinary());
    result.setElements(newElements);
    return result;
}


