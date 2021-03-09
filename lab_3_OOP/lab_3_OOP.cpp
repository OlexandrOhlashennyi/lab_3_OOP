#include <iostream>
#include <Windows.h>

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
		n = 2;
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
			this->counter[i] = this->min_value[i] = dc.min_value[i];
			this->max_value[i] = dc.max_value[i];
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
};

void menu(DigitalCounter);

int main() {
	int arr[10] = { 0, 0, 0 };
	int arr1[10] = { 23, 59, 59 };
	int arr2[10] = { 1, 0, 1 };
	int arr3[10] = { 1, 1, 0 };
	
	DigitalCounter dc1(3, arr, arr1, 10);
	DigitalCounter dc2(3, arr, arr1, 10);
	dc2.setCounter(arr2);
	dc1.setCounter(arr3);
	cout << "dc1:   " << dc1;
	cout << "dc2:   " << dc2;
	cout << (dc1 > dc2);
	
	return 0;
}



void DigitalCounter::Increase()
{
	counterIncrease(counter + n - 1);
}

void DigitalCounter::counterIncrease(int* counter)
{
	(*counter)++;
	if (*counter > max_value[counter - this->counter]) {
		*counter = min_value[counter - this->counter];
		counterIncrease(--counter);
	}
}

void DigitalCounter::print()
{
	for (int i = 0; i < n - 1; i++) {
		cout << counter[i] << " : ";
	}
	cout << counter[n - 1] << endl;
}

void menu(DigitalCounter obj) {
	while (true)
	{
		int n = obj.getN();
		int* arr1 = new int[n];
		int* arr2 = new int[n];
		system("cls");
		int choise;
		bool exit;
		cout << "\n\n\t1.Start counter\n\t2.Set range\n\t3.Get range\n\t4.Set counter\n\t5.Get counter\n\t6.Set timer delay\n\t7.Get timer delay\n\t0.Exit\n\n";
		cin >> choise;
		switch (choise) {
		case 1:
			cout << "Counter starting...(Esc to stop)\n";
			exit = false;
			while (!exit) {
				obj.print();						//виведення значення лічильника
				obj.Increase();						//збільшення лічильника на 1
				Sleep(obj.getTimerDelay());			//чекаємо задану кількість мілісекунд
				if (GetAsyncKeyState(VK_ESCAPE)) {	//вловлюємо натискання esc
					exit = true;
				}
			}
			break;
		case 2:
			for (int i = 0; i < n; i++) {
				cout << "Enter counter range[a b](a<b): ";
				cin >> arr1[i] >> arr2[i];
			}
			obj.setMinimum(arr1);								//встановлюємо мінімум
			obj.setMaximum(arr2);								//встановлюємо максимум
			break;
		case 3:
			obj.getMinimum(arr1);
			obj.getMaximum(arr2);
			printf("Range:\n");
			for (int i = 0; i < n; i++) printf("%d - %d\n", arr1[i], arr2[i]);
			break;
		case 4:
			for (int i = 0; i < n; i++) {
				cout << "Enter counter number: ";
				cin >> arr1[i];
			}
			obj.setCounter(arr1);
			break;
		case 5:
			obj.print();
			break;
		case 6:
			int t;
			cout << "Enter delay in milliseconds: ";
			cin >> t;
			obj.setTimerDelay(t);							//встановлюємо затримку
			break;
		case 7:
			cout << "Timer delay: " << obj.getTimerDelay() << "ms";
			break;
		case 0:
		default:
			return;
		}
		cout << "\n\n";
		system("pause");
	}
}