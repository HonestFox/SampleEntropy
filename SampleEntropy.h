#pragma once
#include "MyMath.h"
#include "ExcelOpe.h"

/*
	���������أ���������������з���
	������ ���·���� Sheet��Ŀ�� ÿ��Sheetȡ�������������ά�ȡ���ֵ����
*/
template<typename T>
std::vector<T> GetSampleEntropy(const char* ExcelPath, int SheetCount, int items, int Dimension, double Rate)
{
	std::vector<T> RetVec;
	RetVec.resize(SheetCount);
	std::vector<libxl::Sheet*> svec = ReadExcel(ExcelPath, SheetCount);	//�����
	std::vector<double> average;
	average.resize(SheetCount);
	std::vector<std::vector<T>> dvec = FillArray(svec, items, average);  //ÿ��Sheet�е�Ԫ�طֱ���䵽��Ӧ����

																		 //��ʼ�²���
	for (int idx = 0; idx < SheetCount; ++idx)
	{
		//�����idx������Ԫ�ص���ֵ
		double ThresholeVal = GetThresholdVal(dvec[idx], 0.20, average[idx]);
		//��ȡ����Ҫ�����Ŀ
		std::cout << GetNeededCount(dvec[idx], Dimension + 1, ThresholeVal) << std::endl;
		std::cout << GetNeededCount(dvec[idx], Dimension, ThresholeVal) << std::endl;

		std::cout << std::endl;


		RetVec[idx] = log(GetNeededCount(dvec[idx], Dimension + 1, ThresholeVal) / GetNeededCount(dvec[idx], Dimension, ThresholeVal)) * -1;
	}
	return RetVec;
}