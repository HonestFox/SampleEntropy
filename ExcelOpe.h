/*
	��Excel����ز���
*/
#pragma once

#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>

#include "libxl.h"

/*
	����Excel�������Sheet����Ŀ���ֱ�洢��һ��vector�в�����
	������������ơ�Sheet��Ŀ
*/
std::vector<libxl::Sheet*> ReadExcel(const char* ExcelName,int SheetCount)  
{
	assert(ExcelName != NULL);
	libxl::Book* book = xlCreateBook();
	assert(book != NULL);
	assert(book->load(ExcelName));
	std::vector<libxl::Sheet*> svec;
	svec.resize(SheetCount);
	//�ֱ��ȡ����Sheet
	for (int idx = 0; idx < SheetCount; ++idx)
	{
		libxl::Sheet* sheet = book->getSheet(idx);
		assert(sheet != NULL);
		svec[idx] = sheet;
	}
	return svec;
}

/*
	���������أ�
	��ͨ���FillArray
	���ݴ����sheet���ϣ���ÿ�������е�������䵽������

	��չ���FillArray
	���ݴ����sheet���ϣ���ÿ�������е�������䵽�����У�˳ �� �� �� ÿ �� sheet �� ƽ �� ֵ
*/

//��ͨ�� ������Sheet���顢ÿ��Sheet��ȡ��Ԫ����Ŀ
template <typename T = double>
std::vector<std::vector<T> > FillArray(const std::vector<libxl::Sheet*>& svec, size_t items)
{
	std::vector<std::vector<T>> RetVec;
	RetVec.resize(svec.size());
	for (size_t idx = 0; idx < RetVec.size(); ++idx)
	{
		//�ѵ�idx��sheet�����idx��double���͵�������
		for (size_t items_idx = 0; items_idx < items; ++items_idx)
		{
			double Data = svec[idx]->readNum(items_idx, 0);
			RetVec[idx].push_back(Data);	//���뵱ǰԪ��
		}
	}
	return RetVec;
}

//��չ�� ������Sheet���顢ÿ��Sheet��ȡ��Ԫ����Ŀ��ƽ��ֵ����(����Ͳ���)
template <typename T = double>
std::vector<std::vector<T> > FillArray(const std::vector<libxl::Sheet*>& svec, size_t items, std::vector<double>& average )	
{
	std::vector<std::vector<T>> RetVec;
	RetVec.resize(svec.size());
	for (size_t idx = 0; idx < RetVec.size(); ++idx)
	{
		double Sum = 0;
		//�ѵ�idx��sheet�����idx��double���͵�������
		for (size_t items_idx = 0; items_idx < items; ++items_idx)
		{
			double Data = svec[idx]->readNum(items_idx, 0);
			Sum += Data;
			RetVec[idx].push_back(Data);	//���뵱ǰԪ��
		}
		average[idx] = (Sum / items);
	}
	return RetVec;
}


