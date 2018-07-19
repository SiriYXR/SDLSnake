#include "SIRI_Functions.h"

#include <stdexcept>
#include <time.h>

namespace siri {

	int SIRI_Rand(int max, int min)
	{
		if (max < min)
			throw std::runtime_error("Myrand max<min");
		if (max == 0)
			throw std::runtime_error("Myrand max==0");

		int num;
		srand((unsigned)time(NULL) + rand());//选取种子文件
		do
		{
			num = (int)rand() % max;
		} while (num < min || num > max);

		return num;
	}

}