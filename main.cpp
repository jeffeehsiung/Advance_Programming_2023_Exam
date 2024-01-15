#include <fstream>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QRegularExpression>
#include "album.h"

Image loadFromFile(unsigned int rows, unsigned int cols, const QString& resourcePath) {
    static const QRegularExpression re("\\s+");  // Static regular expression object

    QFile file(resourcePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        throw std::logic_error("Resource file " + resourcePath.toStdString() + " not found");

    QTextStream in(&file);
    Image result(rows, cols, "from " + resourcePath.toStdString());
    unsigned int position = 0;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList numbers = line.split(re, Qt::SkipEmptyParts);
        for (const QString& number : numbers) {
            bool ok;
            int pix = number.toInt(&ok);
            if (ok && position < rows * cols) {
                result[position++] = static_cast<ubyte>(pix);
            } else if (!ok) {
                throw std::logic_error("Resource file contains invalid data.");
            } else {
                break; // Exit loop if maximum size reached
            }
        }
    }
    return result;
}


int main(int argc, char *argv[])
{
  std::ofstream result{"result.txt"};
  QApplication app(argc, argv);
  /** TODO:
   *  The QApplication app(argc, argv); object is created but not used in a typical Qt application manner.
   *  Ensure that the Qt application loop is correctly implemented if needed.
   *  Proper Use of QApplication: The QApplication object is typically used in Qt applications that have a GUI.
   *  If your application does not need a GUI event loop, you may remove this object.
   *  If you intend to use Qt's GUI features,
   *  you should start the application loop by calling app.exec() at the end of the main function.
   *  However, based on your code, it seems the QApplication is only used for QMessageBox, which is a part of the GUI.
   *  If the GUI is not required, consider removing the QApplication object and related GUI elements.
   *  // QApplication app(argc, argv); // Remove this if GUI is not required
   *  // ... rest of main function ...
   *  // return app.exec(); // Add this if GUI event loop is needed
   *  */
  Album pictures("My first album");
  Image test(12, 12, "test");
  int value = 0;
  std::iota(test.begin(), test.end(), value);
  test.showT(result, "\t");
  test.showG(20);
  Image copy_test(test);
  pictures.putInAlbum(std::move(test));
  pictures.putInAlbum(std::move(copy_test));
  auto alb1 = pictures.removeFromAlbum("test");
  if (alb1)
        /** in the incorrected files,
         *  the albumn returned by removeFromAlbum is an optoinal<Image>
         *  but its value was attempted to be accessed using operator ".".
         *  The shiftHor and shiftVert functions
         *  are applied to std::optional<Image> (returned by removeFromAlbum).
         *  You should use the -> operator or value() to access the `Image object inside the std::optional`.
         *  For example: alb1->shiftHor(3); instead of alb1.shiftHor(3); if alb1 is a valid Image object.
         *  The same applies to alb1->showT(result, "\t"); and other similar uses of alb1 and alb2.
         *  */
    {
      alb1->shiftHor(3);
      alb1->showT(result, "\t");
      alb1->shiftVert(4);
      alb1->showT(result, "\t");

      /** given code for post-correction question two -- not answer */
      alb1->shiftToOrigin(57);
      alb1->showT(result, "\t");
    }
  auto alb2 = pictures.removeFromAlbum("test");
  if (alb2)
    {
      result << "Image with name test should no longer be part of your album" <<std::endl;
    }
  try
  {
    qDebug() << "Current directory:" << QDir::currentPath();
    Image fromFile = loadFromFile(8, 8, ":/glider.txt");
    fromFile.showT(result);
    fromFile.setBinary(true);
    fromFile.showG(25);

    /** given code for post-correction question three -- not answer */
    filter f1 = nextState;
        /** the nextState filter will show error if not defined.
         *  It should be defined when reaching 2023 question three.
         *  */
    fromFile.addFilter(f1);
    for (int repeat = 0; repeat < 4; ++repeat)
      {
        fromFile = fromFile.processAll(1);
        fromFile.showG(25);
        fromFile.showT(result);
        fromFile.addFilter(f1);
      }
  }
  catch (std::logic_error & e)
  {
    result << e.what() << std::endl;
  }
  pictures.playAll();
  result.close();
  //will only work if more is a valid command...
  system("more result.txt");
  /** The system("more result1.txt"); command at the end of main is platform-dependent and might not work on all systems.
   *  Consider removing or modifying it for broader compatibility.
   *  */

  return 0;
}
