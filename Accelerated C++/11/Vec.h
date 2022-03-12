#ifndef VEC_H
#define VEC_H

/*
构造函数
    如果用户在给出参数同时提供了初始值,可以使用这个初始值对分配了空间的元素设置初始值
    如果仅给出一个大小参数,我们将调用T的默认构造函数设置元素初始值

explicit:声明一个构造函数是explicit的,那么编译器只在用户显示的使用构造函数时才会成功调用构造函数
    Vec<int> vi(100);   //显式的
    Vec<int> vi = 100;  //隐式的

提供用户能使用的类型名称,隐藏实现细节
    迭代器类型,Vec元素的类型,对该元素的引用,两迭代器之间的差值

索引操作:重载运算符

返回首尾迭代器:
    两种类型:const 非const

拷贝控制操作
    拷贝构造函数
    拷贝运算符
    析构函数
    
    赋值和初始化区别:
        赋值:需要删除一个旧的值,再拷贝一个新的值
        初始化:创建对象时顺便给初始值

        初始化:
            声明一个变量时
            再函数入口用函数参数时
            函数返回中使用函数返回值时
            构造初始化时
        
        赋值:
            string str = "hello world"; //初始化
            string str2(3, " ");        //初始化
            string str3;                //初始化
            str3 = str2;                //赋值

三位一体原则:
    拷贝构造函数
    拷贝赋值运算符
    析构函数

    原因:
        我们将Vec复制给另一个Vec,如果不定义拷贝构造函数就会使用默认的拷贝构造函数,产生浅拷贝,导致两个对象公用一个内存
        我们在浅拷贝的基础上,且析构函数没有定义,那么会导致产生的资源没有被释放
        我们使用了析构函数,想要释放掉new的内存,但是因为默认的拷贝构造函数是浅拷贝,我们的析构函数重复释放同一块内存,程序崩溃

        所以,拷贝构造函数,拷贝赋值运算符,析构函数是三位一体的(用于管理我们的内存资源!!!)

push_back:
    如果每插入一个新元素就分配一个新空间,那么开销巨大;所以,我们一次分配大于申请的内存,不用的不作初始化,大于该内存时扩容两倍(一次申请100,如果再调用一次push_back,则分配200个size的空间)

    所以需要更多的指针表示:
        data:初始化元素的第一个(vec.begin())
        avail:未初始化元素的第一个
        limit:最后一个可以访问元素的下一个位置(vec.end())
    
    push_back()实现靠两个函数
            grow()                  //内存满了,则扩容
            unchecked_append()      //插入新元素

灵活的内存管理:
    分配空间不能直接靠new,new会分配内存并调用构造函数构造对象;我们一次申请许多内存,但是后面数据并未用到,但是也会被new用来初始化,这就很消耗性能
    我们希望分配内存和构造对象分开来

    <memory> -> allocator<T>:它可以分配一块预备用于储存T类型对象但未初始化的内存块，并返回头指针
    template <class T>
    class allocator {
        public:
            T* allocate(size_t); //分配一块被指定了类型但却未被初始化的内存块,这个内存块内没有对象
            void deallocate(T*, size_t); //用于释放未被初始化的内存,第一个参数时allocate函数返回的指针,第二个参数时该内存大小分配的元素个数
            void construct(T*, const T&);//在未被初始化的内存区域中构造当而对象,第一个参数时allocate函数返回的指针,第二个时用于初始化的值
            void destroy(T*);//删除它的参数所指向的T类型的对象,调用该对象的析构函数,再次呈现未初始化的内存块
            //...
    }

    //用于将前两个参数所指向的内存区间中的值复制到第三个参数指针所指向的目标内存块中
    template<class In, class For>
    For uninitialized_copy(In, In, For);

    //根据构造其第三个参数尽可能多的副本,以填充其两个参数提供的内存块
    template<class For, class T>
    void uninitialized_fill(For, For, const T&); 
*/

#include <iostream>
#include <memory>

template <class T>
class Vec
{
public:
    typedef T*              iterator;
    typedef const T*        const_iterator;
    typedef size_t          size_type;
    typedef T               value_type;
    typedef std::ptrdiff_t  difference_type;//指针差值
    typedef T&              reference;
    typedef const T&        const_reference;

public:
    //默认构造函数
    Vec() { create(); }
    //有参构造函数
    explicit Vec(std::size_t n, const T& val = T()) { create(n, val); }
    //拷贝构造函数
    Vec(const Vec& v) { create(v.begin(), v.end()); }
    //析构函数,释放内存
    ~Vec() { uncreate(); }
    //赋值运算符
    Vec& operator=(const Vec& v);

    //大小与索引(返回元素个数,首尾指针差值),两指针相减生成ptrdiff_t类型值
    size_type size() const { return avail - data; }

    //两种返回,一种可以改变值,另一种不行
    T& operator[](size_type i) { return data[i]; }
    const T& operator[](size_type i) const { return data[i]; }

    //返回迭代器的操作
    iterator begin() { return data; }
    const iterator begin() const { return data; }

    iterator end() { return avail; }
    const iterator end() const { return avail; }

    //push_back
    void push_back(const T& val) {
        //超出额外分配的空间,扩大空间到原来的两倍
        if (avail == limit) 
            grow();
        //将新增元素放入对象末端
        unchecked_append(val);
    }
    //清除元素
    void clear();
    

private:
    iterator data;     //首元素
    iterator avail;    //未初始化元素的第一个
    iterator limit;    //最后一个可获得元素的后一个位置

    //内存分配工具
    std::allocator<T> alloc;

    //为底层数组分配空间并初始化
    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    //删除数组中的元素并释放内存
    void uncreate();

    //分配空间
    void grow();
    //添加元素
    void unchecked_append(const T&);   
};


//这里注意一下,模板一般都是在头文件实现,并且要加上template...告诉编译器,并且返回类型等需要显示定义
//如果没有防止自我拷贝的操作,那么释放掉原来的区域,也会释放掉v指向的内存,再进行赋值操作,这就是对一个被释放内存的区域的一次非法访问!
template<class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
    //防止自拷贝
    if (&rhs != this)
    {
        //先释放原对象占据空间
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    //这样可以实现连续赋值
    return *this;
}

template<class T> 
void Vec<T>::create()
{
    data = avail = limit = 0;
}

template<class T> 
void Vec<T>::create(size_type n, const T& val)
{
    data = alloc.allocate(n);
    limit = avail = data + n;
    std::uninitialized_fill(data, limit, val);
}

template<class T> 
void Vec<T>::create(const_iterator i, const_iterator j)
{
    data = alloc.allocate(j - i);
    limit = avail = std::uninitialized_copy(i, j, data);
}

template<class T> 
void Vec<T>::uncreate()
{
    if (data) {
        //相反顺序删除
        iterator it = avail;
        while (it != data) {
            alloc.destroy(--it);
        }
        alloc.deallocate(data, limit - data);
    }
    data = limit = avail = 0;
}

template<class T>
void Vec<T>::grow()
{
    //在扩展对象大小时,分配实际使用的两倍大小的空间
    size_type new_size = std::max(2 * (limit - data), ptrdiff_t(1));

    //分配新的空间并将已经存在的对象元素复制到新内存中
    iterator new_data = alloc.allocate(new_size);
    //将[data, avail) -> new_data中
    //Return value: Iterator to the element past the last element copied.(返回最后一个拷贝元素的下一个位置,即avail)
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    //析构原来空间的对象并释放原来的内存空间
    uncreate();

    //重置指针
    data = new_data;
    avail = new_avail;
    limit = data + new_size; //limit是分配最大的位置的下一个位置,不可访问
}

//假设avail指向一片新分配但尚未初始化的空间
template<class T>
void Vec<T>::unchecked_append(const T& val)
{
    alloc.construct(avail++, val);
}

template<class T>
void Vec<T>::clear()
{
    uncreate();
}

#endif