#include "object.h"
#include<vector>
#include<opencv2/opencv.hpp>
using namespace std;

#define __EXPORT extern "C" __declspec(dllexport)

//__EXPORT void f(ParamPtrArray& params) {
//	vector<int>* dst = new vector<int>{ 1,2,3 };
//	params.push_back(make_param("dst", "vector<int>", dst));
//}
//
//__EXPORT void g(ParamPtrArray& params) {
//	int num = get_data<int>(params[0]);
//	int* dst = new int{ num + 1 };
//	params.push_back(make_param("increase","int",dst));
//}

__EXPORT void threshold(ParamPtrArray& params) {
	cv::Mat* dst = new cv::Mat();
	cv::threshold(get_data_ref<cv::Mat>(params[0]), *dst, get_data_ref<double>(params[1]),
		get_data_ref<double>(params[2]), get_data_ref<int>(params[3]));
	params.push_back(make_param("dst", "Mat", dst));
}