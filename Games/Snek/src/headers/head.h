#ifndef __HEAD_H__
#define __HEAD_H__

#include "block.h"


class Head : public Block{
public:
    using Block::Block;
    
    int move2(std::vector<Block*> body, std::vector<Block*> fruits, int& score); 
};

#endif