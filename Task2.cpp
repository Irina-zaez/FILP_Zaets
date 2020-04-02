#include "stdafx.h"
#include "map"

class Block
{
public:
	size_t mem_size;
	bool is_free = true;
	void* mem_point;
	Block* twin;
	Block* parent;

	Block(size_t size, void* point)
	{
		mem_size = size;
		mem_point = point;
		twin = this;
		parent = this;
	}
};

class Allocator
{
public:
	size_t mem_size;
	std::map<void*, Block*> blocks;

	Allocator(size_t size)
	{
		size_t mem_size = size;
		void* point = malloc(size);
		Block* block = new Block(size, point);
		blocks[point] = block;
	};

	void* alloc(size_t size)
	{
		if (size > mem_size)
		{
			throw 2;
		}
		std::map<void*, Block*>::iterator it;
		size_t min_size = mem_size;
		Block* block;
		for (it = blocks.begin(); it != blocks.end(); it++)
		{
			if (!it->second->is_free)
				continue;
			if (size == it->second->mem_size)
			{
				block = it->second;
				break;
			}
			if (size < it->second->mem_size && min_size > it->second->mem_size)
			{
				block = it->second;
				min_size = it->second->mem_size;
			}
		}

		if (min_size / 2 >= size)
		{
			Block* twin = new Block(min_size / 2, (void*)((size_t)(block->mem_point) + min_size / 2));
			Block* new_block = new Block(min_size / 2, block->mem_point);
			new_block->is_free = false;
			new_block->parent = block;
			twin->parent = block;
			twin->twin = new_block;
			new_block->twin = twin;
			blocks[new_block->mem_point] = new_block;
			blocks[twin->mem_point] = twin;
		}
		return block->mem_point;
	}

	void dealloc(void* mem_point)
	{
		Block* block = blocks[mem_point];
		block->is_free = true;
		size_t size = block->mem_size;
		while (true)
		{
			if (!block->twin->is_free || block->twin == block)
				break;
			Block* twin = block->twin;
			std::map<void*, Block*>::iterator it;
			void* mem_point;
			if (block->mem_point < twin->mem_point)
				mem_point = block->mem_point;
			else
			{
				mem_point = twin->mem_point;
				Block* other = twin;
				twin = block;
				block = other;
			}
			for (it = blocks.begin(); it != blocks.end(); it++)
			{
				if (it->second == twin)
					blocks.erase(it);
			}
			blocks[block->mem_point] = block->parent;
			block = block->parent;
		}
	}
};