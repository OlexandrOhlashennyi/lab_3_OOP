#include <iostream>
#include <Windows.h>
#define N 5

using namespace std;

class DigitalCounter {
private:
	int* counter;
	int* min_value;
	int* max_value;
	int n;
	int timer_delay;
	void counterIncrease(int*);
public:
	DigitalCounter() {
		n = 3;
		counter = new int[n];
		min_value = new int[n];
		max_value = new int[n];
		for (int i = 0; i < n; i++) {
			counter[i] = min_value[i] = 0;
			max_value[i] = 9;
		}
		timer_delay = 100;

	}
	DigitalCounter(int n, int* min_value, int* max_value, int t) {
		this->n = n;
		counter = new int[this->n];
		this->min_value = new int[this->n];
		this->max_value = new int[this->n];
		for (int i = 0; i < n; i++) {
			counter[i] = this->min_value[i] = min_value[i];
			this->max_value[i] = max_value[i];
		}
		timer_delay = t;
	}

	DigitalCounter(const DigitalCounter& dc) {
		this->n = dc.n;
		counter = new int[this->n];
		min_value = new int[this->n];
		max_value = new int[this->n];
		for (int i = 0; i < n; i++) {
			counter[i] = dc.counter[i];
			min_value[i] = dc.min_value[i];
			max_value[i] = dc.max_value[i];
		}
		this->timer_delay = dc.timer_delay;
	}

	~DigitalCounter() { delete[] this->min_value;  delete[] this->max_value; delete[] this->counter; }

	int getN() { return n; }
	int getCounter(int* arr) {
		for (int i = 0; i < n; i++) arr[i] = counter[i];
	}
	void getMinimum(int* arr) {
		for (int i = 0; i < n; i++) arr[i] = min_value[i];
	}
	void getMaximum(int* arr) {
		for (int i = 0; i < n; i++) arr[i] = max_value[i];
	}
	int getTimerDelay() { return timer_delay; }

	void setMinimum(int* arr) {
		for (int i = 0; i < n; i++) min_value[i] = arr[i];
	}
	void setMaximum(int* arr) {
		for (int i = 0; i < n; i++) arr[i] = min_value[i];
	}
	void setCounter(int* arr) {
		for (int i = 0; i < n; i++) counter[i] = arr[i];
	}
	void setTimerDelay(int a) { timer_delay = a; }
	void Increase();
	void print();

	friend ostream& operator<<(ostream& output, const DigitalCounter& DC) {
		for (int i = 0; i < DC.n - 1; i++) {
			output << DC.counter[i] << " : ";
		}
		output << DC.counter[DC.n - 1] << endl;
		return output;
	}
	friend istream& operator>>(istream& input, DigitalCounter& DC) {
		for (int i = 0; i < DC.n; i++) {
			input >> DC.max_value[i];
		}
		for (int i = 0; i < DC.n; i++) {
			input >> DC.min_value[i];
		}
		for (int i = 0; i < DC.n; i++) {
			input >> DC.counter[i];
		}
		input >> DC.timer_delay;
		return input;
	}
	
	bool operator>(const DigitalCounter& dc) {
		for (int i = 0; i < n; i++) {
			if (this->counter[i] > dc.counter[i]) return true;
			else if (this->counter[i] < dc.counter[i]) return false;
		}
		return false;
	}
	bool operator<(const DigitalCounter& dc) {
		for (int i = 0; i < n; i++) {
			if (this->counter[i] < dc.counter[i]) return true;
			else if (this->counter[i] > dc.counter[i]) return false;
		}
		return false;
	}
	DigitalCounter operator++() {
		this->Increase();
		return *this;
	}
	DigitalCounter operator++(int) {
		this->Increase();
		return *this;
	}
	DigitalCounter operator=(DigitalCounter& dc) {
		n = dc.n;
		delete[] min_value;
		delete[] max_value;
		delete[] counter;
		counter = new int[n];
		min_value = new int[n];
		max_value = new int[n];
		for (int i = 0; i < n; i++) {
			counter[i] = dc.counter[i];
			min_value[i] = dc.min_value[i];
			max_value[i] = dc.max_value[i];
		}
		timer_delay = dc.timer_delay;
		return *this;
	}
};

void sort(DigitalCounter*, DigitalCounter*);
void swap(DigitalCounter&, DigitalCounter&);
void print(DigitalCounter*);

int main() {
	DigitalCounter dc[N];
	cout << "instructions:\n{max max max}\n{min min min}\n{counter counter counter}\ntimer\nEnter " << N << " counters: " << endl;
	for (int i = 0; i < N; i++)
		cin >> dc[i];
	
	cout << endl << "Counters:\n";
	print(dc);
	sort(dc, dc + N-1);

	cout  << endl << "Sorted:" << endl;
	print(dc);

	for (int i = 0; i < N; i++)
		dc[i]++;
	sort(dc, dc + N - 1);

	cout << endl << "Sorted after ++:" << endl;
	print(dc);
	return 0;
}

void print(DigitalCounter* dc) {
	for (int i = 0; i < N; i++)
		cout << dc[i];
}

void swap(DigitalCounter& e1, DigitalCounter& e2) {
	DigitalCounter temp(e1);
	e1 = e2;
	e2 = temp;
}

void sort(DigitalCounter* ptrl, DigitalCounter* ptrr) {
	if (ptrr < ptrl + 1) return;
	if (ptrr == ptrl + 1) {
		if (*ptrr < *ptrl)
			swap(*ptrr, *ptrl);
		return;
	}
	DigitalCounter* ptrc = ptrr, *ptr, *ptrs = ptrl;
	while (*ptrs < *ptrc)
		ptrs++;
	ptr = ptrs++;
	while (ptrs < ptrr) {
		if (*ptrs < *ptrc) {
			swap(*ptrs, *ptr);
			ptr++;
		}
		ptrs++;
	}
	swap(*ptrc, *ptr);
	sort(ptrl, ptr - 1);
	sort(ptr + 1, ptrr);
}

void DigitalCounter::Increase() {
	counterIncrease(counter + n - 1);
}

void DigitalCounter::counterIncrease(int* counter) {
	(*counter)++;
	if (*counter > max_value[counter - this->counter]) {
		*counter = min_value[counter - this->counter];
		counterIncrease(--counter);
	}
}

void DigitalCounter::print() {
	for (int i = 0; i < n - 1; i++) {
		cout << counter[i] << " : ";
	}
	cout << counter[n - 1] << endl;
}


/*
23 59 59
0 0 0
1 1 2
10
23 59 59
0 0 0
0 0 0
10
23 59 1
0 0 0
1 1 1
10
23 59 59
0 0 0
11 1 1
10
23 59 59
0 0 0
1 11 1
10
*/