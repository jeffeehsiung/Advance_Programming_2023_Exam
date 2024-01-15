#include "Video.h"

Video::Video(std::string n) : name(std::move(n)) {}

void Video::addImage(const Image& image) {
    collection.push_back(image);
}

void Video::showT(std::ostream& os, const std::string& delim) const {
    for (const auto& img : collection) {
        img.showT(os, delim);
        os << std::endl;
    }
}

void Video::showG(int rectSize) const {
    for (const auto& img : collection) {
        img.showG(rectSize);
    }
}

void Video::processAll(unsigned int regSize) {
    for (auto& img : collection) {
        img.processAll(regSize);
    }
}

const std::string& Video::getName() const {
    return name;
}


///** Assuming Image objects are uniquely owned by Video. */
///** added constructor overload for question five */
//Video::Video(std::string n) : name(std::move(n)) {}
//void Video::addImage(std::unique_ptr<Image> image) {
//    collection.push_back(std::move(image));  // Use move semantics
//}

//void Video::showT(std::ostream& os, const std::string& delim) const {
//    for (const auto& img : collection) {
//        img->showT(os, delim);  // Access members via ->
//        os << std::endl;
//    }
//}

//void Video::showG(int rectSize) const {
//    for (const auto& img : collection) {
//        img->showG(rectSize);
//    }
//}

///** STL Algorithms: For operations like processAll, you can leverage STL algorithms like std::for_each for concise and expressive code.*/
//void Video::processAll(unsigned int regSize) {
//    std::for_each(collection.begin(), collection.end(), [regSize](const auto& img) {
//        img->processAll(regSize);
//    });
//}

//const std::string& Video::getName() const {
//    return name;
//}


/** Assuming Image objects are shared among Video objects. */
//void Video::addImage(const std::shared_ptr<Image>& image) {
//    collection.push_back(image);  // Shared ownership
//}

//void Video::showT(std::ostream& os, const std::string& delim) const {
//    for (const auto& img : collection) {
//        img->showT(os, delim);  // Access members via ->
//        os << std::endl;
//    }
//}

//void Video::showG(int rectSize) const {
//    for (const auto& img : collection) {
//        img->showG(rectSize);
//    }
//}

///** STL Algorithms: For operations like processAll, you can leverage STL algorithms like std::for_each for concise and expressive code.*/
//void Video::processAll(unsigned int regSize) {
//    std::for_each(collection.begin(), collection.end(), [regSize](const auto& img) {
//        img->processAll(regSize);
//    });
//}
