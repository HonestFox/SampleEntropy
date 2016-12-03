#pragma once
#include "MyMath.h"
#include "ExcelOpe.h"

/*
	计算样本熵，将结果存入数组中返回
	参数： 表格路径、 Sheet数目、 每个Sheet取样数、计算基础维度、阈值因子
*/
template<typename T>
std::vector<T> GetSampleEntropy(const char* ExcelPath, int SheetCount, int items, int Dimension, double Rate)
{
	std::vector<T> RetVec;
	RetVec.resize(SheetCount);
	std::vector<libxl::Sheet*> svec = ReadExcel(ExcelPath, SheetCount);	//读表格
	std::vector<double> average;
	average.resize(SheetCount);
	std::vector<std::vector<T>> dvec = FillArray(svec, items, average);  //每个Sheet中的元素分别填充到对应数组

																		 //开始新测试
	for (int idx = 0; idx < SheetCount; ++idx)
	{
		//计算第idx个表格的元素的阈值
		double ThresholeVal = GetThresholdVal(dvec[idx], 0.20, average[idx]);
		//获取符合要求的数目
		std::cout << GetNeededCount(dvec[idx], Dimension + 1, ThresholeVal) << std::endl;
		std::cout << GetNeededCount(dvec[idx], Dimension, ThresholeVal) << std::endl;

		std::cout << std::endl;


		RetVec[idx] = log(GetNeededCount(dvec[idx], Dimension + 1, ThresholeVal) / GetNeededCount(dvec[idx], Dimension, ThresholeVal)) * -1;
	}
	return RetVec;
}