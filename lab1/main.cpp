#include <stdio.h>
#include <cmath>
#include <cstring>
#include <ctime>

const unsigned int MOD = 65536;

struct Titem {
	unsigned long long key;
	char value[65];
};


template<class T>
class TVector {
	private:
		unsigned int size; // кол-во занятых ячеек 
		unsigned int capacity; // емкость 
		T* data;
	public:
		void Assert(const unsigned int n, T elem);
		T& operator[](const unsigned int &index);
		void PushBack(T elem);
		unsigned int Size();
		TVector();
		TVector(const unsigned int n);
		TVector(const unsigned int n, T elem);
		~TVector();
};

template<class T>
void TVector<T>::Assert(const unsigned int n, T elem) {
	for (int i = 0; i < n; i++) {
		data[i] = elem;
	}
}

template<class T>
T& TVector<T>::operator[](const unsigned int &index) {
	return data[index];
}

template<class T>
void TVector<T>::PushBack(T elem) {
	if (data == 0) {
		capacity = 1;
		data = new T[capacity];
	}
	if (size == capacity) {
		capacity = capacity * 2;
		T* new_data = new T[capacity];
		for (int i = 0; i < size; i++) {
			new_data[i] = data[i];
		}
		delete[] data;
		data = new_data;
	}
	data[size] = elem;
	size++;
}

template<class T>
unsigned int TVector<T>::Size() {
	return size;
}

template<class T>
TVector<T>::TVector() {
	size = 0;
	capacity = 0;
	data = 0;
}

template<class T>
TVector<T>::TVector(const unsigned int n) {
	size = n;
	capacity = n;
	data = new T[size];
	Assert(n, T());
}

template<class T>
TVector<T>::~TVector() {
	delete[] data;
}

void RadixSort(TVector<Titem> &data, int n) { // макс число 18 446 744 073 709 551 615(8 байт)
	unsigned long long div = 1;
	for (int k = 0; k < 4; k++) {
		TVector<int> count(MOD); // создаем массив счетчиков в диапазоне от 1 до 65536(2 байта)
		for (int i = 0; i < n; i++) { // проходим по массиву
			count[(data[i].key / div) % MOD]++; // по остатку от деления на 65536 берем в счетчике ячейку и делпем ++
		}// (сначала отсекаем уже пройденую часть числа делением на div)

		for (int i = 1; i < MOD; i++) {// в count собираем сложением индекс массива data последнего числа, соответствующего индексу count
			count[i] = count[i] + count[i - 1];
		}
		TVector<Titem> res(n);
		for (int i = n - 1; i >= 0; i--) { // идем с конца массива
			res[count[(data[i].key / div) % MOD] - 1] =  data[i];// копируем в res из data на позицию полученную в count
			count[(data[i].key / div) % MOD]--; // уменьшаем позицию полученную в count
		}
		for (int i = 0; i < n; i++) {
			data[i] = res[i]; // копируем в data
		}
		div = div * MOD;
	}
}

int main() {
	TVector<Titem> a;
	Titem data;
	while (scanf("%llu%s", &data.key, data.value) > 0) {
        a.PushBack(data);
    }
	int n = a.Size();
	RadixSort(a, n);
	for (int i = 0; i < n; i++) {
		printf("%llu %s\n", a[i].key, a[i].value);
	}
	return 0;
}
