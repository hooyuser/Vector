//vector class interface

#ifndef VECTOR_H_
#define VECTOR_H_

typedef int Rank; //秩
#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）

template <typename T>
class Vector //向量模板类
{
protected:
	Rank _size; //规模
	int _capacity;  //容量
	T* _elem; //数据区
	void copyFrom(T const* A, Rank lo, Rank hi); //复制数组区间A[lo, hi)
	void expand(); //空间不足时扩容
	void shrink(); //装填因子过小时压缩
	bool bubble(Rank lo, Rank hi); //扫描交换
	Rank max(Rank lo, Rank hi); //选取最大元素
	Rank partition(Rank lo, Rank hi); //轴点构造算法
	void merge(Rank lo, Rank mi, Rank hi); //归并算法


public:
	// 构造函数
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) //容量为c、规模为s、所有元素初始为v
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	} //s<=c

	Vector(T const* A, Rank n) //数组整体复制
	{
		copyFrom(A, 0, n);
	}

	Vector(T const* A, Rank lo, Rank hi) //数组区间复制
	{
		copyFrom(A, lo, hi);
	}

	Vector(Vector<T> const& V) //向量整体复制
	{
		copyFrom(V._elem, 0, V._size);
	}

	Vector(Vector<T> const& V, Rank lo, Rank hi) //向量区间复制
	{
		copyFrom(V._elem, lo, hi);
	}


	// 析构函数
	~Vector()
	{
		delete[] _elem;  //释放内部空间
	}


	// 只读访问接口
	Rank size() const //规模
	{
		return _size;
	}

	bool empty() const //判空
	{
		return !_size;
	}

	int disordered() const; //判断向量是否已排序

	Rank find(T const& e) const //无序向量整体查找
	{
		return find(e, 0, _size);
	}

	Rank find(T const& e, Rank lo, Rank hi) const; //无序向量区间查找

	Rank search(T const& e) const //有序向量整体查找
	{
		return (0 >= _size) ? -1 : search(e, 0, _size);
	}

	Rank search(T const& e, Rank lo, Rank hi) const; //有序向量区间查找


// 可写访问接口
	T& operator[] (Rank r) const; //重载下标操作符，可以类似于数组形式引用各元素

	Vector<T> & operator= (Vector<T> const&); //重载赋值操作符，以便直接克隆向量

	T remove(Rank r); //删除秩为r的元素

	int remove(Rank lo, Rank hi); //删除秩在区间[lo, hi)之内的元素

	Rank insert(Rank r, T const& e); //插入元素

	Rank insert(T const& e)
	{
		return insert(_size, e);
	} //默认作为末元素插入

	int deduplicate(); //无序去重

	int uniquify(); //有序去重

	void sort(Rank lo, Rank hi); //对[lo, hi)排序

	void sort() //整体排序
	{
		sort(0, _size);
	}

	void unsort(Rank lo, Rank hi); //对[lo, hi)置乱

	void unsort() //整体置乱
	{
		unsort(0, _size);
	}

	void selectionSort(Rank lo, Rank hi); //选择排序算法

	void mergeSort(Rank lo, Rank hi); //归并排序算法

	void bubbleSort(Rank lo, Rank hi); //起泡排序算法

	void quickSort(Rank lo, Rank hi); //快速排序算法

	void heapSort(Rank lo, Rank hi); //堆排序（稍后结合完全堆讲解）


// 遍历
	void traverse(void(*) (T&)); //遍历（使用函数指针，只读或局部性修改）

	template <typename VST> void traverse(VST&); //遍历（使用函数对象，可全局性修改）
}; //Vector


class Fib
{ //Fibonacci数列类
private:
	long long f, g; //f = fib(k - 1), g = fib(k)。均为int型，徆快就会数值溢出

public:
	Fib(int n) //初始化为不小于n的最小Fibonacci项，O(log_phi(n))时间
	{
		f = 1; //f初始化为fib(-1)
		g = 0; //g初始化为fib(0)
		while (g < n) next();
	} 

	int get() //获取当前Fibonacci项，O(1)时间
	{
		return g;
	} 

	int next() //转至下一Fibonacci项，O(1)时间
	{
		g += f;
		f = g - f;
		return g;
	}

	int prev() //转至上一Fibonacci项，O(1)时间
	{
		f = g - f;
		g -= f;
		return g;
	}
};

#endif 