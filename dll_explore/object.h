#pragma once
#pragma once
#include<string>
#include<opencv2/opencv.hpp>

struct OperatorInterfaceBase {
public:
	virtual ~OperatorInterfaceBase() {}
};

template <typename T>
struct OperatorInterface : public OperatorInterfaceBase {
public:
	OperatorInterface(const std::string& name, const std::string& type, T* ptr);
	~OperatorInterface();

	T data();
	T& data_ref();
	const T& data_const_ref();

private:
	const std::string name_;
	const std::string type_;
	T* ptr;
};

using MatObject = OperatorInterface<cv::Mat>;
using SizeObject = OperatorInterface<cv::Size>;
using IntObject = OperatorInterface<int>;
using DoubleObject = OperatorInterface<double>;
using StringObject = OperatorInterface<std::string>;

using ParamPtr = std::shared_ptr<OperatorInterfaceBase>;
using ParamPtrArray = std::vector<ParamPtr>;

template <typename T>
OperatorInterface<T>::OperatorInterface(const std::string& name, const std::string& type, T* ptr) : name_(name), type_(type), ptr(ptr) {}

template<typename T>
OperatorInterface<T>::~OperatorInterface() {
	delete ptr;
}

template<typename T>
T OperatorInterface<T>::data() {
	return *ptr;
}

template<typename T>
const T& OperatorInterface<T>::data_const_ref() {
	return *ptr;
}

template<typename T>
T& OperatorInterface<T>::data_ref() {
	return *ptr;
}
template<typename T>
T get_data(ParamPtr param_ptr) {
	return dynamic_cast<OperatorInterface<T>*>(param_ptr.get())->data();
}

template<typename T>
T& get_data_ref(ParamPtr param_ptr) {
	return dynamic_cast<OperatorInterface<T>*>(param_ptr.get())->data_ref();
}

template<typename T>
const T& get_data_const_ref(ParamPtr param_ptr) {
	return dynamic_cast<OperatorInterface<T>*>(param_ptr.get())->data_const_ref();
}

template<typename T>
ParamPtr make_param(std::string name, std::string type, T* value_ptr) {
	return ParamPtr(new OperatorInterface<T>(name, type, value_ptr));
}
