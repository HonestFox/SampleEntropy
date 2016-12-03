#include <iostream>
#include <vector>
#include "test.h"
#include "SampleEntropy.h"

#define DEFAULT_EXCEL_PATH  "./table.xls"
#define DEFAULT_SHEET_COUNT  4
#define DEFAULT_ITEMS 1400
#define DEFAULT_DEMENSION 2
#define DEFAULT_RATE 0.20


int main()
{
	const char* ExcelPath = DEFAULT_EXCEL_PATH;			//表格路径
	const int SheetCount = DEFAULT_SHEET_COUNT;			//Sheet数目
	const int items = DEFAULT_ITEMS;									//每个Sheet中采样数
	const int Dimension = DEFAULT_DEMENSION;				//计算时采用的数组维度
	const double rate = DEFAULT_RATE;								//阈值因子

	std::vector<double> Ret = GetSampleEntropy<double>(ExcelPath, SheetCount, items ,Dimension, rate);
	for (auto& i : Ret)
	{
		std::cout << i << std::endl;
	}

	system("pause");
	return 0;
}


/*
需要改进的地方：
	效率，复杂度 
	vector传参，用const &
	MyMath中方法的模板化
	用异常，换掉一大堆的assert()
*/