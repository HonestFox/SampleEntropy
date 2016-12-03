#include <iostream>
#include "ExcelOpe.h"
#include "MyMath.h"

void TestReadExcel()
{
	std::vector<libxl::Sheet*> svec = ReadExcel("table.xls", 4);
}

void TestFillArray()
{
	int SheetCount = 4;
	int items = 1400;
	std::vector<libxl::Sheet*> svec = ReadExcel("table.xls", SheetCount);
	std::vector<double> average;
	average.resize(SheetCount);
	std::vector<std::vector<double>> dvec = FillArray(svec, SheetCount, average);  //扩展版
	//std::vector<std::vector<double>> dvec = FillArray(svec, SheetCount);              //普通版
}

void TestMyMathFunc()	//对MyMath.h中方法的测试
{
	int SheetCount = 4;
	int items = 1400;
	std::vector<libxl::Sheet*> svec = ReadExcel("table.xls", SheetCount);
	std::vector<double> average;
	average.resize(SheetCount);
	std::vector<std::vector<double>> dvec = FillArray(svec, items, average);  //扩展版	，dvec是 表格中所有Sheet当中的元素

	//开始新测试
	for (int idx = 0; idx < SheetCount; ++idx)
	{
		//计算第idx个表格的元素的阈值
		//std::cout << GetThresholdVal(dvec[idx], 0.20, average[idx]) << std::endl;
		double ThresholeVal = GetThresholdVal(dvec[idx], 0.20, average[idx]);
		//获取符合要求的数目
		std::cout << GetNeededCount(dvec[idx], 2, ThresholeVal) << std::endl;
	}
}


void TestFinally()	//最终测试1
{
	int SheetCount = 4;
	int items = 1400;
	int Dimension = 2;
	std::vector<libxl::Sheet*> svec = ReadExcel("table.xls", SheetCount);
	std::vector<double> average;
	average.resize(SheetCount);
	std::vector<std::vector<double>> dvec = FillArray(svec, items, average);  //扩展版	，dvec是 表格中所有Sheet当中的元素

																			  //开始新测试
	for (int idx = 0; idx < SheetCount; ++idx)
	{
		//计算第idx个表格的元素的阈值
		//std::cout << GetThresholdVal(dvec[idx], 0.20, average[idx]) << std::endl;
		double ThresholeVal = GetThresholdVal(dvec[idx], 0.20, average[idx]);
		//获取符合要求的数目
		std::cout << log(GetNeededCount(dvec[idx], Dimension + 1, ThresholeVal) / GetNeededCount(dvec[idx], Dimension, ThresholeVal)) * -1 << std::endl;
	}
}
