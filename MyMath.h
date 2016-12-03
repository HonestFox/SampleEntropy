#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>

/*
	计算给定数组的【平均值】
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
	(构成重载)
	计算给定数组的【标准差】,区别在于平均值是手动传入还是在方法内部运算
*/
//	传入已有的平均值，参数： 指定数组、平均值
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

//平均值在方法内部进行运算，参数：指定数组
template <typename T = double>
double GetStandardDev(const std::vector<T>& dvec)
{
	double average = GetAverage(dvec);
	return GetStandardDev<T>(dvec, average);
}

/*
	(构成重载)
	计算【阈值】
	参数：指定数组、阈值因子（通常为 0.10 ~ 0.25），（平均值）
*/
template <typename T = double>
double GetThresholdVal(const std::vector<T>& dvec, double Rate, double average)
{
	//最好检查一下Rate的范围
	double StandardDev = GetStandardDev(dvec, average);
	return StandardDev * Rate;
}

template <typename T = double>
double GetThresholdVal(const std::vector<double>& dvec, double Rate)
{
	//最好检查一下Rate的范围
	double average = GetAverage(dvec);
	return GetThresholdVal(dvec, Rate, average);
}


/*
	获取两个数组对应列之间差的最大绝对值
	参数：数组1、数组2
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
	返回当前元素集合对应的n维数组两两行之间距离的最大值符合要求的数目
	参数：原始集合、数组维数、阈值
*/
double GetNeededCount(const std::vector<double>& dvec, int n, double ThresholdVal)
{
	double SumRet = 0;
	for (size_t PrevLine = 0; PrevLine < dvec.size() - n - 1; ++PrevLine)
	{
		//std::cout << PrevLine << std::endl;
		double Count = 0;		//PrevLine行与其下面的所有行最大距离中符合要求的数目和
		//PrevVec中存放第PrevLine行的元素
		std::vector<double> PrevVec;		
		PrevVec.resize(n);
		for (int idx = 0; idx < n; ++idx)	//填充PrevVec
		{
			PrevVec[idx] = dvec[PrevLine + idx];
		}
		for (size_t CurLine = PrevLine + 1; CurLine < dvec.size() - n; ++CurLine)
		{
			//CurVec存放第CurLine行元素
			std::vector<double> CurVec;
			CurVec.resize(n);
			for (int idx = 0; idx < n; ++idx)	//填充CurVec
			{
				CurVec[idx] = dvec[CurLine + idx];
			}
			//获取PrevLine行 和 CurLine行的最大距离，并判断是否满足条件
			if (GetMaxGap(PrevVec, CurVec) <= ThresholdVal)
			{
				++Count;
			}
		}
		//总共的行数是：dvec.size() - n + 1 行
		//总共的比较次数是： (dvec.size() - n + 1) - PrevLine 次
		//! ! ! ! !这里接下来的公式好像有问题
		Count /= ((dvec.size() - n + 1) - PrevLine);
		SumRet += Count;
	}
	//return Count / dvec.size();
	return SumRet;
}

