#pragma once

class Block
{
public:
	Block(unsigned int id);
protected:
	unsigned int ID_;
};

Block::Block(unsigned int id)
{
	ID_ = id;
}