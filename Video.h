#ifndef VIDEO_H
#define VIDEO_H

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include "Image.h"

class Video {
public:
    explicit Video(std::string name);
    void addImage(const Image& image);
    void showT(std::ostream& os, const std::string& delim = "") const;
    void showG(int rectSize = 10) const;
    void processAll(unsigned int regSize);
    const std::string& getName() const;

private:
    std::vector<Image> collection;  // Store Images by value
    std::string name;
};

#endif // VIDEO_H


//#ifndef VIDEO_H
//#define VIDEO_H

//#include <vector>
//#include <iostream>
//#include <algorithm>
//#include <memory>  // Include for smart pointers
//#include "Image.h"

///** In this implementation, Video takes ownership of Image objects using std::unique_ptr.
//     *  This ensures that Image objects are automatically destroyed when the Video object is destroyed
//     *  or when the collection changes, preventing memory leaks.
//     *  */
//class Video{
//public:
//    /** added constructor overload for question five */
//    explicit Video(std::string name);
//    Video() = default;
//    void addImage(std::unique_ptr<Image> image);
//    void showT(std::ostream& os, const std::string& delim = "") const;
//    void showG(int rectSize = 10) const;
//    void processAll(unsigned int regSize) ;
//    /** added for question five */
//    const std::string& getName() const;


//private:
//    std::vector<std::unique_ptr<Image>> collection;
//    std::string name;

//};

//#endif // VIDEO_H

/** Video Class Structure: The Video class contains a private member collection, which is a vector of Image objects.
 *   This collection represents the frames of the video.
 *   addImage: Adds an Image object to the collection.
 *   showT: Displays the textual representation of each image in the collection. It separates the images with a newline for clarity.
 *   showG: Displays the graphical representation of each image. Depending on your GUI setup, you might want to add functionality to pause or navigate between the images.
 *   processAll: Applies a processing function (defined in the Image class) to all images in the collection.
 *
 *   Pass by Reference: When passing objects to functions, using references prevents unnecessary copying. This is particularly important for potentially large objects like Image.
 *   Const Correctness: Use const where the data is not supposed to change. This helps in optimizing the code and also in preventing accidental modifications.
 *   Move Semantics in addImage: If you have cases where you are passing r-value Image objects to addImage, providing a version of addImage that uses move semantics can significantly improve performance.
 *   STL Algorithms: The use of std::for_each in processAll is more idiomatic and can be optimized by compilers.
 *   Effcient String Handling: Passing std::string as a const reference in showT avoids unnecessary copying of string literals.
 *   */


/** If you choose to use std::shared_ptr for managing Image objects within the Video class,
 *  it means you are allowing shared ownership of these objects.
 *  This is useful when an Image object may be used by multiple Video objects or other parts of your application,
 *  and you need automatic memory management to ensure proper deletion of these objects when no longer needed.
 *  */
//#ifndef VIDEO_H
//#define VIDEO_H

//#include <vector>
//#include <iostream>
//#include <algorithm>
//#include <memory>  // Include for smart pointers
//#include "Image.h"

//class Video {
//public:
//    Video() = default;

//    void addImage(const std::shared_ptr<Image>& image);
//    void showT(std::ostream& os, const std::string& delim = "") const;
//    void showG(int rectSize = 10) const;
//    void processAll(unsigned int regSize);

//private:
//    std::vector<std::shared_ptr<Image>> collection;
//};

//#endif // VIDEO_H


