//vector class interface

#ifndef VECTOR_H_
#define VECTOR_H_

typedef int Rank; //��
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����

template <typename T>
class Vector //����ģ����
{
protected:
	Rank _size; //��ģ
	int _capacity;  //����
	T* _elem; //������
	void copyFrom(T const* A, Rank lo, Rank hi); //������������A[lo, hi)
	void expand(); //�ռ䲻��ʱ����
	void shrink(); //װ�����ӹ�Сʱѹ��
	bool bubble(Rank lo, Rank hi); //ɨ�轻��
	Rank max(Rank lo, Rank hi); //ѡȡ���Ԫ��
	Rank partition(Rank lo, Rank hi); //��㹹���㷨
	void merge(Rank lo, Rank mi, Rank hi); //�鲢�㷨


public:
	// ���캯��
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //����Ϊc����ģΪs������Ԫ�س�ʼΪv
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	} //s<=c

	Vector(T const* A, Rank n) //�������帴��
	{
		copyFrom(A, 0, n);
	}

	Vector(T const* A, Rank lo, Rank hi) //�������临��
	{
		copyFrom(A, lo, hi);
	}

	Vector(Vector<T> const& V) //�������帴��
	{
		copyFrom(V._elem, 0, V._size);
	}

	Vector(Vector<T> const& V, Rank lo, Rank hi) //�������临��
	{
		copyFrom(V._elem, lo, hi);
	}


	// ��������
	~Vector()
	{
		delete[] _elem;  //�ͷ��ڲ��ռ�
	}


	// ֻ�����ʽӿ�
	Rank size() const //��ģ
	{
		return _size;
	}

	bool empty() const //�п�
	{
		return !_size;
	}

	int disordered() const; //�ж������Ƿ�������

	Rank find(T const& e) const //���������������
	{
		return find(e, 0, _size);
	}

	Rank find(T const& e, Rank lo, Rank hi) const; //���������������

	Rank search(T const& e) const //���������������
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}

	Rank search(T const& e, Rank lo, Rank hi) const; //���������������


// ��д���ʽӿ�
	T& operator[] (Rank r) const; //�����±������������������������ʽ���ø�Ԫ��

	Vector<T> & operator= (Vector<T> const&); //���ظ�ֵ���������Ա�ֱ�ӿ�¡����

	T remove(Rank r); //ɾ����Ϊr��Ԫ��

	int remove(Rank lo, Rank hi); //ɾ����������[lo, hi)֮�ڵ�Ԫ��

	Rank insert(Rank r, T const& e); //����Ԫ��

	Rank insert(T const& e)
	{
		return insert(_size, e);
	} //Ĭ����ΪĩԪ�ز���

	int deduplicate(); //����ȥ��

	int uniquify(); //����ȥ��

	void sort(Rank lo, Rank hi); //��[lo, hi)����

	void sort() //��������
	{
		sort(0, _size);
	}

	void unsort(Rank lo, Rank hi); //��[lo, hi)����

	void unsort() //��������
	{
		unsort(0, _size);
	}

	void selectionSort(Rank lo, Rank hi); //ѡ�������㷨

	void mergeSort(Rank lo, Rank hi); //�鲢�����㷨

	void bubbleSort(Rank lo, Rank hi); //���������㷨

	void quickSort(Rank lo, Rank hi); //���������㷨

	void heapSort(Rank lo, Rank hi); //�������Ժ�����ȫ�ѽ��⣩


// ����
	void traverse(void(*) (T&)); //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�

	template <typename VST> void traverse(VST&); //������ʹ�ú������󣬿�ȫ�����޸ģ�
}; //Vector


class Fib
{ //Fibonacci������
private:
	long long f, g; //f = fib(k - 1), g = fib(k)����Ϊint�ͣ�����ͻ���ֵ���

public:
	Fib(int n) //��ʼ��Ϊ��С��n����СFibonacci�O(log_phi(n))ʱ��
	{
		f = 1; //f��ʼ��Ϊfib(-1)
		g = 0; //g��ʼ��Ϊfib(0)
		while (g < n) next();
	} 

	int get() //��ȡ��ǰFibonacci�O(1)ʱ��
	{
		return g;
	} 

	int next() //ת����һFibonacci�O(1)ʱ��
	{
		g += f;
		f = g - f;
		return g;
	}

	int prev() //ת����һFibonacci�O(1)ʱ��
	{
		f = g - f;
		g -= f;
		return g;
	}
};

#endif 