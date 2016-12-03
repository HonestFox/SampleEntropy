#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>

/*
	�����������ġ�ƽ��ֵ��
*/
template <typename T = double>
double GetAverage(const std::vector<T>& dvec)
{
	double sum = 0;
	for (auto& i : dvec)
	{
		sum += i;
	}
	return (sum / dvec.size());
}
/*
	(��������)
	�����������ġ���׼�,��������ƽ��ֵ���ֶ����뻹���ڷ����ڲ�����
*/
//	�������е�ƽ��ֵ�������� ָ�����顢ƽ��ֵ
template <typename T = double>
double GetStandardDev(const std::vector<T> dvec, double average)
{
	double ret = 0;
	for (auto& it : dvec)
	{
		ret += pow((it - average), 2);
	}
	ret /= dvec.size();
	ret = sqrt(ret);
	return ret;
}

//ƽ��ֵ�ڷ����ڲ��������㣬������ָ������
template <typename T = double>
double GetStandardDev(const std::vector<T>& dvec)
{
	double average = GetAverage(dvec);
	return GetStandardDev<T>(dvec, average);
}

/*
	(��������)
	���㡾��ֵ��
	������ָ�����顢��ֵ���ӣ�ͨ��Ϊ 0.10 ~ 0.25������ƽ��ֵ��
*/
template <typename T = double>
double GetThresholdVal(const std::vector<T>& dvec, double Rate, double average)
{
	//��ü��һ��Rate�ķ�Χ
	double StandardDev = GetStandardDev(dvec, average);
	return StandardDev * Rate;
}

template <typename T = double>
double GetThresholdVal(const std::vector<double>& dvec, double Rate)
{
	//��ü��һ��Rate�ķ�Χ
	double average = GetAverage(dvec);
	return GetThresholdVal(dvec, Rate, average);
}


/*
	��ȡ���������Ӧ��֮����������ֵ
	����������1������2
*/
double GetMaxGap(const std::vector<double>& dvec1, const std::vector<double>& dvec2)
{
	assert(dvec1.size() == dvec2.size());
	double MaxGap = 0;
	for (size_t idx = 0; idx < dvec1.size(); ++idx)
	{
		double Gap = abs(dvec1[idx] - dvec2[idx] );
		if (Gap > MaxGap)
		{
			MaxGap = Gap;
		}
	}
	return MaxGap;
}

/*
	���ص�ǰԪ�ؼ��϶�Ӧ��nά����������֮���������ֵ����Ҫ�����Ŀ
	������ԭʼ���ϡ�����ά������ֵ
*/
double GetNeededCount(const std::vector<double>& dvec, int n, double ThresholdVal)
{
	double SumRet = 0;
	for (size_t PrevLine = 0; PrevLine < dvec.size() - n - 1; ++PrevLine)
	{
		//std::cout << PrevLine << std::endl;
		double Count = 0;		//PrevLine������������������������з���Ҫ�����Ŀ��
		//PrevVec�д�ŵ�PrevLine�е�Ԫ��
		std::vector<double> PrevVec;		
		PrevVec.resize(n);
		for (int idx = 0; idx < n; ++idx)	//���PrevVec
		{
			PrevVec[idx] = dvec[PrevLine + idx];
		}
		for (size_t CurLine = PrevLine + 1; CurLine < dvec.size() - n; ++CurLine)
		{
			//CurVec��ŵ�CurLine��Ԫ��
			std::vector<double> CurVec;
			CurVec.resize(n);
			for (int idx = 0; idx < n; ++idx)	//���CurVec
			{
				CurVec[idx] = dvec[CurLine + idx];
			}
			//��ȡPrevLine�� �� CurLine�е������룬���ж��Ƿ���������
			if (GetMaxGap(PrevVec, CurVec) <= ThresholdVal)
			{
				++Count;
			}
		}
		//�ܹ��������ǣ�dvec.size() - n + 1 ��
		//�ܹ��ıȽϴ����ǣ� (dvec.size() - n + 1) - PrevLine ��
		//! ! ! ! !����������Ĺ�ʽ����������
		Count /= ((dvec.size() - n + 1) - PrevLine);
		SumRet += Count;
	}
	//return Count / dvec.size();
	return SumRet;
}

