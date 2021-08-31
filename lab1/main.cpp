#include <stdio.h>
#include <cmath>
#include <cstring>
#include <ctime>

struct Titem {
	unsigned long long key;
	char value[65];
};

namespace NMystd {
	template<class T>
	class TVector {
		private:
			unsigned int capacity;
			unsigned int maxsize;
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
			maxsize = 1;
			data = new T[maxsize];
		}
		if (capacity == maxsize) {
			maxsize = maxsize * 2;
			T* new_data = new T[maxsize];
			for (int i = 0; i < capacity; i++) {
				new_data[i] = data[i];
			}
			delete[] data;
			data = new_data;
		}
		data[capacity] = elem;
		capacity++;
	}

	template<class T>
	unsigned int TVector<T>::Size() {
		return capacity;
	}

	template<class T>
	TVector<T>::TVector() {
		capacity = 0;
		maxsize = 0;
		data = 0;
	}

	template<class T>
	TVector<T>::TVector(const unsigned int n) {
		capacity = n;
		maxsize = n;
		data = new T[capacity];
		Assert(n, T());
	}

	template<class T>
	TVector<T>::TVector(const unsigned int n, T elem) {
		capacity = n;
		maxsize = n;
		data = new T[capacity];
		Assert(n, elem);
	}

	template<class T>
	TVector<T>::~TVector() {
		delete[] data;
	}
}

const unsigned int MOD = 65536;

void RadixSort(NMystd::TVector<Titem> &data, int n) {
	unsigned long long div = 1;
	for (int k = 0; k < 4; k++) {
		NMystd::TVector<int> count(MOD);
		for (int i = 0; i < n; i++) {
			count[(data[i].key / div) % MOD]++;
		}

		for (int i = 1; i < MOD; i++) {
			count[i] = count[i] + count[i - 1];
		}
		NMystd::TVector<Titem> res(n);
		for (int i = n - 1; i >= 0; i--) {
			res[count[(data[i].key / div) % MOD] - 1] =  data[i];
			count[(data[i].key / div) % MOD]--;
		}
		for (int i = 0; i < n; i++) {
			data[i] = res[i];
		}
		div = div * MOD;
	}
}

int main() {
	double start, end;
	start = clock();
	NMystd::TVector<Titem> a;
	Titem cur;
	while (scanf("%llu%s", &cur.key, cur.value) > 0) {
        a.PushBack(cur);
    }
	int n = a.Size();
	RadixSort(a, n);
	for (int i = 0; i < n; i++) {
		printf("%llu %s\n", a[i].key, a[i].value);
	}
	end = clock();
    printf("TIME %Lf\n", (end - start) /1000);
	return 0;
}
