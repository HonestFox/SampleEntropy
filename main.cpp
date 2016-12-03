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
	const char* ExcelPath = DEFAULT_EXCEL_PATH;			//���·��
	const int SheetCount = DEFAULT_SHEET_COUNT;			//Sheet��Ŀ
	const int items = DEFAULT_ITEMS;									//ÿ��Sheet�в�����
	const int Dimension = DEFAULT_DEMENSION;				//����ʱ���õ�����ά��
	const double rate = DEFAULT_RATE;								//��ֵ����

	std::vector<double> Ret = GetSampleEntropy<double>(ExcelPath, SheetCount, items ,Dimension, rate);
	for (auto& i : Ret)
	{
		std::cout << i << std::endl;
	}

	system("pause");
	return 0;
}


/*
��Ҫ�Ľ��ĵط���
	Ч�ʣ����Ӷ� 
	vector���Σ���const &
	MyMath�з�����ģ�廯
	���쳣������һ��ѵ�assert()
*/