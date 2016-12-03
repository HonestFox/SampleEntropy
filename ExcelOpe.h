/*
	对Excel的相关操作
*/
#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

#include "libxl.h"

/*
	输入Excel表格名、Sheet的数目，分别存储到一个vector中并返回
	参数：表格名称、Sheet数目
*/
std::vector<libxl::Sheet*> ReadExcel(const char* ExcelName,int SheetCount)  
{
	assert(ExcelName != NULL);
	libxl::Book* book = xlCreateBook();
	assert(book != NULL);
	assert(book->load(ExcelName));
	std::vector<libxl::Sheet*> svec;
	svec.resize(SheetCount);
	//分别读取各个Sheet
	for (int idx = 0; idx < SheetCount; ++idx)
	{
		libxl::Sheet* sheet = book->getSheet(idx);
		assert(sheet != NULL);
		svec[idx] = sheet;
	}
	return svec;
}

/*
	（构成重载）
	普通版的FillArray
	根据传入的sheet集合，将每个集合中的内容填充到数组中

	扩展版的FillArray
	根据传入的sheet集合，将每个集合中的内容填充到数组中，顺 便 求 出 每 个 sheet 的 平 均 值
*/

//普通版 参数：Sheet数组、每个Sheet读取的元素数目
template <typename T = double>
std::vector<std::vector<T> > FillArray(const std::vector<libxl::Sheet*>& svec, size_t items)
{
	std::vector<std::vector<T>> RetVec;
	RetVec.resize(svec.size());
	for (size_t idx = 0; idx < RetVec.size(); ++idx)
	{
		//把第idx个sheet存入第idx个double类型的数组中
		for (size_t items_idx = 0; items_idx < items; ++items_idx)
		{
			double Data = svec[idx]->readNum(items_idx, 0);
			RetVec[idx].push_back(Data);	//存入当前元素
		}
	}
	return RetVec;
}

//扩展版 参数：Sheet数组、每个Sheet读取的元素数目、平均值数组(输出型参数)
template <typename T = double>
std::vector<std::vector<T> > FillArray(const std::vector<libxl::Sheet*>& svec, size_t items, std::vector<double>& average )	
{
	std::vector<std::vector<T>> RetVec;
	RetVec.resize(svec.size());
	for (size_t idx = 0; idx < RetVec.size(); ++idx)
	{
		double Sum = 0;
		//把第idx个sheet存入第idx个double类型的数组中
		for (size_t items_idx = 0; items_idx < items; ++items_idx)
		{
			double Data = svec[idx]->readNum(items_idx, 0);
			Sum += Data;
			RetVec[idx].push_back(Data);	//存入当前元素
		}
		average[idx] = (Sum / items);
	}
	return RetVec;
}


