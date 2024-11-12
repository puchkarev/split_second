//
// Created by Victor Puchkarev on 11/12/24.
//

#ifndef SPLIT_SECOND_TEXT_H
#define SPLIT_SECOND_TEXT_H

#include <string>

#include "model.h"

class text {
public:
    static Model from_string(const std::string& text);
    static Model from_character(char c);
};


#endif //SPLIT_SECOND_TEXT_H
