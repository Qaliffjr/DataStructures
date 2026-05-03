#include "recordArray.hpp"

RecordArray copyArray(const RecordArray& source) {
	RecordArray copy{};
	copy.size = source.size;
	copy.capacity = source.size;
	if (source.size <= 0 || source.arr == nullptr) {
		copy.arr = nullptr;
		return copy;
	}
	copy.arr = new Record[source.size];
	for (int i = 0; i < source.size; ++i) {
		copy.arr[i] = source.arr[i];
	}
	return copy;
}

void freeArray(RecordArray& arr) {
	delete[] arr.arr;
	arr.arr = nullptr;
	arr.size = 0;
	arr.capacity = 0;
}
