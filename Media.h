#ifndef MEDIA_H
#define MEDIA_H

#include <iostream>

class Media {
public:
    Media(std::string name): name{name}{}
    virtual ~Media() = default;
    virtual void showT(std::ostream& os, const std::string& delim = "") const = 0;
    virtual void showG(int rectSize = 10) const = 0;
    virtual void processAll(unsigned int regSize) = 0;
    virtual const std::string& getName() const {
        return name;
    }

protected:
    std::string name;
};


#endif // MEDIA_H
