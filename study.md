# 动态规划2024/01/09

> 对于一个数组[1,2,3,4,7,56,4,8]求最长的递增序列长度

暴力求解：

对每一个子序列进行计算

```cpp
#include<iostream>
#include<vector>

using namespace std;

int longest_incr_subseq_util(const vector<int>& sequence, int prev_index, int current_index, int current_length) {
    if (current_index == sequence.size()) {
        return current_length;
    }

    int include_current = 0;
    if (sequence[current_index] > sequence[prev_index]) {//下一个数字是递增的
        include_current = longest_incr_subseq_util(sequence, current_index, current_index + 1, current_length + 1);
    }
    //下一个数字不是递增的
    int exclude_current = longest_incr_subseq_util(sequence, prev_index, current_index + 1, current_length);

    return max(include_current, exclude_current);
}

int longest_incr_subseq(const vector<int>& sequence) {
    if (sequence.empty()) {
        return 0;
    }

    int result = 0;
    for (int i = 0; i < sequence.size()-1; ++i) {
        result = max(result, longest_incr_subseq_util(sequence, i, i+1, 0));
    }

    return result;
}
```

暴力求解法在遍历的时候存在多次的重复计算

因此我们使用一个哈希表来储存我们每一个节点计算的结果，计算从i开始的每一个节点的最长子序列长度
```cpp
#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int longest_incr_subseq_util(unordered_map<int,int> &calculated,const vector<int>& sequence, int prev_index, int current_index, int current_length) {
    if (current_index == sequence.size()) {
        return current_length;
    }

    if(calculated.at(current_index) != -1){
        return calculated.at(current_index);
    }
    int include_current = 0;
    if (sequence[current_index] > sequence[prev_index]) {//下一个数字是递增的
       
        include_current = longest_incr_subseq_util(calculated,sequence, current_index, current_index + 1, current_length + 1);
      
        
    }
    //下一个数字不是递增的
    int exclude_current = longest_incr_subseq_util(calculated,sequence, prev_index, current_index + 1, current_length);
    calculated[current_index] = max(include_current, exclude_current);
    return max(include_current, exclude_current);
}

int longest_incr_subseq(const vector<int>& sequence) {
    unordered_map<int,int> calculated;
    for(int i = 0;i < sequence.size();i++){
        calculated[i] = -1;
    }
    if (sequence.empty()) {
        return 0;
    }

    int result = 0;
    for (int i = 0; i < sequence.size(); ++i) {
        result = max(result, longest_incr_subseq_util(calculated,sequence, i, i+1, 0));
    }

    return result;
}
```

上面使用了一个`unordered_map`来储存每一个`index`的所在位置的最大递增数量，如果已经计算过就不再计算

动态规划就是带备忘录的递归

# 重载操作符2024/01/11

```cpp
<返回类型说明符> operator <运算符符号>(<参数表>)
{
     <函数体>
}
```

 其中，“返回类型说明符”指出重载运算符的返回值类型，operator是定义运算符重载函数的关键字，“运算符符号”指出要重载的运算符名字，是C++中可重载的运算符，比如要重载加法运算符，这里直接写“+”即可，“参数表”指出重载运算符所需要的参数及其类型。

```CPP
#include <iostream>
using namespace std;
class addfloat
{
public:
    addfloat(float p);
    //声明运算符重载
    addfloat operator+(const addfloat &A) const;
    void show() const;
private:
    float m_p;  
};
addfloat::addfloat(float p)
{
    m_p = p;
}
//作为类的成员函数实现运算符重载
addfloat addfloat::operator+(const addfloat &A) const
{
    addfloat B;
    B.m_p = this->m_p + A.m_p;
    return B;
}

```

从上面的例子可以看出，在`addfloat`类中对“+”运算符进行了重载 ，重载后可以对该类的对象进行加法运算。当运行 t = m + n时，编译器检测到“+”左边的m（“+”具有左结合性，所以先检测左边）是一个 `addfloat`类对象，就会调用成员函数 operator+()，将表达式转换成如下格式：

        t = m.operator + (n);
  对于之前的例子：t = m + n，m和n是作为`addfloat`类的对象进行相加的，使用成员函数 `operator+()`转换为了`t = m.operator+(n)`，如果n不是类的对象，而是一个常数，例如：

但是如果m是一个常数时，即：`t = 5.2 + n`；则`t = (5.2).operator + (n)`这种转换是不允许的，编译器会报错，因为5.2不能作为类的对象调用运算符重载`operator+()`函数。

这种场景下针对“+”这种运算符作为类的成员函数进行重载是不可以的。运算符重载不仅仅可以通过类的成员函数来实现，也可以通过全局函数来实现。

我们需要<font color='red'>将运算符重载的全局函数声明为友元函数</font>，因为大多数时候重载运算符要访问类的私有数据，（当然也可以设置为非友元非类的成员函数，但是非友元又不是类的成员函数，是没有办法直接访问类的私有数据的），如果不声明为类的友元函数，而是通过在此函数中调用类的公有函数来访问私有数据会降低性能。所以一般都会设置为类的友元函数，这样我们就可以在此非成员函数中访问类中的数据了。

```cpp
#include <iostream>
using namespace std;
class addfloat
{
public:
    addfloat(float p);
    //声明为友元函数
    friend addfloat operator+(const addfloat &A, const addfloat &B);
    void show() const;
private:
    float m_p;  
};

 
//作为全局函数进行重载
addfloat operator+(const addfloat &A, const addfloat &B)
{
    addfloat C;
    C.m_p = A.m_p + B.m_p;
    return C;
}
 
int main()
{
    addfloat m(5.1);
    addfloat n(1.5);
    addfloat t;
    t = m + n; //两个addfloat类对象相加:t = m.operator+(n);
    return 0;
}

```

当运行t = m + n时，编译器检测到“+”两边都是`addfloat`类的对象，就会转换为类似下面的函数调用：

<font color='orange'>t = operator + (m, n);</font>

因此，m和n都可以看作是函数的实参：
t = m + 5.2转换为 t = operator + (m, 5.2);
t = 5.2 + n转换为 t = operator + (5.2, n);
以全局函数的形式重载“+”，是为了保证“+”运算符的操作数能够被对称的处理；换句话说，常数在“+”左边和右边都是正确的；
因此，运算符左右两边都有操作对象时，且这两个操作对象可以互换，最好可以使用全局函数的形式重载，例如：+、-、*、/、==、!= ，这些符合运算符两边有操作对象的运算符。
