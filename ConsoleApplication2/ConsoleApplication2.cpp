// ConsoleApplication2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <fstream>
#include <algorithm>
#include <random>

template <class T>
class Victor {
private:
	size_t len;
	T *arr;
	size_t capacity = 16;
public:
	//Констурктор по умолчанию, ничего не передаем.
	Victor() : len(capacity), arr(new T[capacity]) {
	}
	//конструктор копирования
	Victor(T *arr, size_t len) : len(len) {
		this->arr = new T[(this->len / capacity + 1) * capacity];
		for (auto i = 0; i < len; i++)
			this->arr[i] = arr[i];
	}

	Victor(const Victor &obj) : len(obj.len) {
		this->arr = new T[len];
		for (auto i = 0; i < len; i++)
			this->arr[i] = obj.arr[i];
	}

	Victor(Victor &&obj) {
		len = obj.len;
		arr = obj.arr;
		obj.arr = nullptr;
	}

	~Victor() {
		delete[] arr;
	}

	// Оператор присвоения
	Victor& operator= (const Victor &obj) {
		if (this == &obj)
			return *this;

		delete[] arr;
		Victor tmp(obj);
		swap(tmp);
		return *this;
	}

	Victor& operator= (Victor &&obj) {
		delete[] arr;
		swap(std::move(obj));
		return *this;
	}

	// ----------------------------
	// метод begin
	T* begin() {
		return arr;
	}
	// метод end
	T* end() {
		return (arr + len);
	}
	// метод size
	size_t size() {
		return len;
	}

	void printVector() {
		for (auto i = 0; i != len; i++)
			std::cout << arr[i] << " ";
		std::cout << std::endl;
	}

	void increaseLen() {
		T* temp = new T[(len / capacity + 2) * capacity];
		for (auto i = 0; i < len; i++)
			temp[i] = std::move(arr[i]);
		delete[] arr;
		arr = temp;
	}

	// -----------------------------
	// метод push_back
	void push_back(const T& el)
	{
		if (len % capacity == 0)
		{
			increaseLen();
			arr[len] = el;
		}
		else
			arr[len] = el;
		len++;
	}

	void push_back(T&& el)
	{
		if (len % capacity == 0)
		{
			increaseLen();
			arr[len] = std::move(el);
		}
		else
			arr[len] = std::move(el);
		len++;
	}
	// метод pop_back
	void pop_back()
	{
		erase(end() - 1);
	}
	// метод erase
	void erase(const T* inx) {
		T *narr = new T[len - 1];
		for (auto i = arr; i != inx; i++)
			*(narr + (i - arr)) = *i;
		for (auto i = inx + 1; i != arr + len; i++)
			*(narr + (i - arr - 1)) = *i;
		delete[] arr;
		arr = narr;
		len--;
	}
	void erase(const T* b, const T* e) {
		if (e > b) {
			auto declen = e - b + 1;
			T *narr = new T[len - declen];
			for (auto i = arr; i != b; i++)
				*(narr + (i - arr)) = *i;
			for (auto i = e + 1; i != arr + len; i++)
				*(narr + (i - arr - declen)) = *i;
			delete[] arr;
			arr = narr;
			len -= declen;
		}
	}
	void swap(Victor &obj) {
		std::swap(arr, obj.arr);
		std::swap(len, obj.len);
	}
};

template <class T>
void swap(T &a, T &b) {
	a.swap(b);
}


int main() {
	//int a[9] = { 1,2,3,4,5,6,7,8,9 };
	//char b[2] = { '2', '1' };
	//Victor<int> v(a, 9);
	//Victor<char> v1(b, 2);
	//v1.push_back('1');
	//v.pop_back();
	//v.swap(v1);
	//v1.printVector();
	//v.printVector();

	Victor<std::ofstream> vStreams;
	for (int i = 0; i < 10; i++) {
		std::string name = std::to_string(i) + ".txt";
		vStreams.push_back(std::ofstream(name));
	}
	std::shuffle(vStreams.begin(), vStreams.end(), std::random_device());
	int num = 0;
	for (auto &stream : vStreams) {
		stream << num;
		stream.close();
		++num;
	}
	return 0;
}