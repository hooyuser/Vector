#include "vector.h"
#include <stdlib.h>      
#include <time.h> 
#include <algorithm>

using namespace std;

const double MIN_OCCUPANCY = 0.2;

template <typename T>
Rank Vector<T>::max(Rank lo, Rank hi)
{
	return (_elem[lo] > _elem[hi] ? _elem[lo] : _elem[hi]);
}


template <typename T> //Ԫ������ΪT
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)  //����������A[lo, hi)Ϊ�������c����
{
	_elem = new T[_capacity = 2 * (hi - lo)]; //����ռ�
	_size = 0;  //��ģ����
	while (lo < hi)
		_elem[_size++] = A[lo++]; //A[lo, hi)�ڵ�Ԫ����һ������_elem[0, hi - lo)
}


template <typename T>
T& Vector<T>::operator[] (Rank r) const //�����±������[]
{
	if (r < _size)
		return _elem[r];
	else
		return _elem[_size - 1];
}


template <typename T>
Vector<T>& Vector<T>::operator= (Vector<T> const& V) //���ظ�ֵ�����=
{
	if (_elem)
		delete[] _elem; //�ͷ�ԭ������
	copyFrom(V._elem, 0, V.size()); //���帴��
	return *this; //���ص�ǰ��������ã��Ա���ʽ��ֵ
}


template <typename T>
void Vector<T>::expand()  //�����ռ䲻��ʱ����
{
	if (_size < _capacity)
		return; //��δ��Աʱ����������
	if (_capacity < DEFAULT_CAPACITY)
		_capacity = DEFAULT_CAPACITY; //��������С����
	T* oldElem = _elem;  //����ԭ������ַ
	_elem = new T[_capacity <<= 1]; // �����ӱ�
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i]; //����ԭ��������
	delete[] oldElem; //�ͷ�ԭ�ռ�
}


template <typename T>
void Vector<T>::shrink() //װ�����ӹ�Сʱѹ��������ռ�ռ� 
{
	if (_capacity < DEFAULT_CAPACITY << 1)
		return; //���������� DEFAULT_CAPACITY ����
	if (_size * MIN_OCCUPANCY > _capacity)
		return; //��MIN_OCCUPANCYΪ�½�
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1]; //��������
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i]; //����ԭ��������
	delete[] oldElem; //�ͷ�ԭ�ռ�
}


template <typename T>
int Vector<T>::disordered() const  //������������������Ԫ�ضԵ�����
{
	int n = 0; //������
	for (int i = 1; i < _size; i++) //��һ���_size - 1������Ԫ��
		if (_elem[i - 1] > _elem[i]) ++n; //���������
	return n; //���������ҽ���n = 0
}


template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)  //�ȸ��������������[lo, hi)
{
	T* V = _elem + lo; //��������_elem[lo, hi)������һ����V[0, hi - lo)
	for (Rank i = hi - lo; i > 0; i--) //�Ժ���ǰ
	{
		srand((unsigned)time(0));
		swap(V[i - 1], V[rand() % i]); //��V[i - 1]��V[0, i)��ĳһԪ���������
	}

}


template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const //����������˳����ң��������һ��Ԫ��e��λ�ã�ʧ��ʱ������lo - 1
{
	while ((lo < hi--) && (e != _elem[hi])); //�Ӻ���ǰ��˳����ң�ֱ�������±�hiԽ�����ҳɹ�
	return hi; //��hi < lo������ζ��ʧ�ܣ�����hi������Ԫ�ص���
}


template <typename T> //��e��Ϊ��ΪrԪ�ؓI��
Rank Vector<T>::insert(Rank r, T const& e) { //assert: 0 <= r <= size
	expand(); //���б�Ҫ������
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1]; //�Ժ���ǰ�����Ԫ��˳�κ�һ����Ԫ
	_elem[r] = e;
	_size++; //������Ԫ�؎Ը�������
	return r; //ކ����
}


template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) //�����׼�[lo, hi)
{
	if (lo == hi) return 0; //����Ч�ʿ��ǣ����������˻����������remove(0, 0)
	while (hi < _size)
		_elem[lo++] = _elem[hi++]; //[hi, _size)˳��ǰ��hi - lo����Ԫ
	_size = lo; //���¹�ģ��ֱ�Ӷ���β��[lo, _size = hi)����
	shrink(); //���б�Ҫ��������
	return hi - lo; //���ر�����Ԫ�ذm��Ŀ
}


template <typename T>
T Vector<T>::remove(Rank r) //ɾ����������Ϊr��Ԫ�أ�0 <= r < size
{
	T e = _elem[r]; //���ݱ�ɾ��Ԫ��
	remove(r, r + 1); //��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
	return e; //���ر�ɾ��Ԫ��
}


template <typename T>
int Vector<T>::deduplicate() //ɾ�������������ظ�Ԫ��
{
	int oldSize = _size; //��¼ԭ��ģ
	Rank i = 1; //��_elem[1]��ʼ
	while (i < _size) //��ǰ�����һ�����Ԫ��_elem[i]
		(find(_elem[i], 0, i) < 0) ? //����ǰ׺��Ѱ�Ҳ��T��ͬ�ߣ�����һ����
		i++ : remove(i); //������ͬ������������̣����������ͬ��
	return oldSize - _size; //�����_ģ����������������Ԫ������
}


template <typename T>
int Vector<T>::uniquify() //���������ظ�Ԫ���޳��㷨
{
	Rank i = 0, j = 0; //���Ի��조���ڡ�Ԫ�ص���
	while (++j < _size) //��һɨ�裬ֱ��ĩԪ��
		if (_elem[i] != _elem[j]) //������ͬ��
			_elem[++i] = _elem[j]; //���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
	_size = ++i;
	shrink(); //ֱ�ӽس�β������Ԫ��
	return j - i; //������ģ�仯��������ɾ��Ԫ������
}


template <typename T>
void Vector<T>::sort(Rank lo, Rank hi) //��������[lo, hi)����
{
	switch (rand() % 5) //���ѡȡ�����㷨���ɸ��ݾ���������ص����ѡȡ������
	{
	case 1:  bubbleSort(lo, hi); break; //��������
	case 2:  selectionSort(lo, hi); break; //ѡ������ϰ�⣩
	case 3:  mergeSort(lo, hi); break; //�鲢����
	case 4:  heapSort(lo, hi); break; //�������Ժ���ܣ�
	default: quickSort(lo, hi); break; //���������Ժ���ܣ�
	}
}


template <typename T> //��������������
void Vector<T>::bubbleSort(Rank lo, Rank hi) //assert: 0 <= lo < hi <= size
{
	while (lo < (hi = bubble(lo, hi)));
} //������ɨ�轻����ֱ��ȫ��


template <typename T>
Rank Vector<T>::bubble(Rank lo, Rank hi) //һ��ɨ�轻��
{
	Rank last = lo; //���Ҳ������Գ�ʼ��Ϊ[lo - 1, lo]
	while (++lo < hi) //�������ң���һ����������Ԫ��
		if (_elem[lo - 1] > _elem[lo])
		{ //��������
			last = lo; //�������Ҳ������λ�ü�¼����ͨ������ʹ�ֲ�����
			swap(_elem[lo - 1], _elem[lo]);
		}
	return last; //�������Ҳ�������λ��
}


template <typename T> //�����鲢����
void Vector<T>::mergeSort(Rank lo, Rank hi)
{ //0 <= lo < hi <= size
	if (hi - lo < 2) return; //��Ԫ��������Ȼ���򣬷���...
	int mi = (lo + hi) / 2; //���е�Ϊ��
	mergeSort(lo, mi);
	mergeSort(mi, hi); //�ֱ�����
	merge(lo, mi, hi); //�鲢

}


template <typename T> //���������Ĺ鲢
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)//���������������[lo, mi)��[mi, hi)
{
	T* A = _elem + lo; //�ϲ��������A[0, hi - lo) = _elem[lo, hi)

	int lb = mi - lo;
	T* B = new T[lb]; //ǰ������B[0, lb) = _elem[lo, mi)
	for (Rank i = 0; i < lb; i++)
		B[i] = A[i]; //����ǰ������

	int lc = hi - mi;
	T* C = _elem + mi; //��������C[0, lc) = _elem[mi, hi)

	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc); )
	{ //B[j]��C[k]�е�С������Aĩβ
		if ((j < lb) && (!(k < lc) || (B[j] <= C[k]))) A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || (C[k] < B[j]))) A[i++] = C[k++];
	}
	delete[] B; //�ͷ���ʱ�ռ�B
} //�鲢��õ���������������[lo, hi)


template <typename T> //����������������[lo, hi)�ڣ�ȷ��������e�����һ���ڵ����
Rank Vector<T>::search(T const& e, Rank lo, Rank hi) const
{ //assert: 0 <= lo < hi <= _size
	return (rand() % 2) ? //����50%�ĸ������ʹ�ö��ֲ��һ�Fibonacci����
		binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}


// ���ֲ����㷨���汾C��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size
template <typename T>
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)
{
	while (lo < hi)
	{ //ÿ������������һ�αȽ��жϣ���������֧
		Rank mi = (lo + hi) >> 1; //���е�Ϊ��㣨�����ȵ��۰룬��Ч�ڿ��֮��ֵ��ʾ�����ƣ�
		(e < A[mi]) ? hi = mi : lo = mi + 1; //���ȽϺ�ȷ������[lo, mi)��(mi, hi)
	} //�ɹ����Ҳ�����ǰ��ֹ
	return --lo; //ѭ������ʱ��loΪ����e��Ԫ�ص���С�ȣ���lo - 1��������e��Ԫ�ص������
} //�ж������Ԫ��ʱ�����ܱ�֤����������ߣ�����ʧ��ʱ���ܹ�����ʧ�ܵ�λ��


// Fibonacci�����㷨���汾A��������������������[lo, hi)�ڲ���Ԫ��e��0 <= lo <= hi <= _size
template <typename T>
static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi)
{
	Fib fib(hi - lo); //��O(log_phi(n = hi - lo)ʱ�䴴��Fib����
	while (lo < hi) //ÿ����������Ҫ�����αȽ��жϣ���������֧
	{
		while (hi - lo < fib.get())
			fib.prev(); //ͨ����ǰ˳����ң���̯O(1)����������������Σ�
		Rank mi = lo + fib.get() - 1; //ȷ������Fib(k) - 1�����
		if (e < A[mi])
			hi = mi; //����ǰ���[lo, mi)��������
		else if (A[mi] < e)
			lo = mi + 1; //�������(mi, hi)��������
		else
			return mi; //��mi������	
	} //�ɹ����ҿ�����ǰ��ֹ
	return -1; //����ʧ��
} //�ж������Ԫ��ʱ�����ܱ�֤����������ߣ�ʧ��ʱ���򵥵ط���-1��������ָʾʧ�ܵ�λ��


template <typename T>
void Vector<T>::traverse(void(*visit) (T&)) //���Ӻ���ָ����c
{
	for (int i = 0; i < _size; i++) visit(_elem[i]); //��������
}

template <typename T> //Ԫ������
template <typename VST> //������
void Vector<T>::traverse(VST& visit) //���Ӻ���������c
{
	for (int i = 0; i < _size; i++) visit(_elem[i]); //��������
}