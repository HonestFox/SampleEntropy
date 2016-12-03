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
	std::vector<std::vector<double>> dvec = FillArray(svec, SheetCount, average);  //��չ��
	//std::vector<std::vector<double>> dvec = FillArray(svec, SheetCount);              //��ͨ��
}

void TestMyMathFunc()	//��MyMath.h�з����Ĳ���
{
	int SheetCount = 4;
	int items = 1400;
	std::vector<libxl::Sheet*> svec = ReadExcel("table.xls", SheetCount);
	std::vector<double> average;
	average.resize(SheetCount);
	std::vector<std::vector<double>> dvec = FillArray(svec, items, average);  //��չ��	��dvec�� ���������Sheet���е�Ԫ��

	//��ʼ�²���
	for (int idx = 0; idx < SheetCount; ++idx)
	{
		//�����idx������Ԫ�ص���ֵ
		//std::cout << GetThresholdVal(dvec[idx], 0.20, average[idx]) << std::endl;
		double ThresholeVal = GetThresholdVal(dvec[idx], 0.20, average[idx]);
		//��ȡ����Ҫ�����Ŀ
		std::cout << GetNeededCount(dvec[idx], 2, ThresholeVal) << std::endl;
	}
}


void TestFinally()	//���ղ���1
{
	int SheetCount = 4;
	int items = 1400;
	int Dimension = 2;
	std::vector<libxl::Sheet*> svec = ReadExcel("table.xls", SheetCount);
	std::vector<double> average;
	average.resize(SheetCount);
	std::vector<std::vector<double>> dvec = FillArray(svec, items, average);  //��չ��	��dvec�� ���������Sheet���е�Ԫ��

																			  //��ʼ�²���
	for (int idx = 0; idx < SheetCount; ++idx)
	{
		//�����idx������Ԫ�ص���ֵ
		//std::cout << GetThresholdVal(dvec[idx], 0.20, average[idx]) << std::endl;
		double ThresholeVal = GetThresholdVal(dvec[idx], 0.20, average[idx]);
		//��ȡ����Ҫ�����Ŀ
		std::cout << log(GetNeededCount(dvec[idx], Dimension + 1, ThresholeVal) / GetNeededCount(dvec[idx], Dimension, ThresholeVal)) * -1 << std::endl;
	}
}
