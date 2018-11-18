#include <stdio.h>

int * sum(int x); //声明一个 指针函数 返回类型位一个指针变量 可以通过*p来获取值
int (*pfun)(int,int);//声明一个 函数指针
int max(int x,int y);//声明全局函数
int getname(int x,int y, int(*p)(int,int));//声明函数指针
int add(int x,int y);
int main(void)
{
    //int name = 400;
    int *re = sum(100);
    //sleep(1);
    printf("%d %p\n",*re,re);
    //sleep(2);
    printf("%d %p\n",*re,re);//严重有问题 居然值不一样了

    //max = 0x12345;//错误 函数名和数组名的地址不允许修改
    pfun = max;//初始化函数指针 指向max函数的函数指针变量
    printf("sum的入口地址：%p\n",sum);
    printf("max的入口地址：%p pfun的地址：%p max的大小:%d\n",max, pfun, pfun(10,20));//函数名就是函数的入口也是地址

    int x = getname(44,55,max);//函数名称 就是地址就是指针
    printf("x的值：%d\n",x);
    printf("x+y的值：%d\n",getname(10,20,add));


    return 0;
}

//定义函数指针变量
int getname(int x, int y,int(*p)(int,int)){

    return p(x,y);
}
int add(int x, int y)
{
    return x+y;
}
int max(int xx, int yy){
    return xx>yy?xx:yy;
}
int * sum(int x){
    int static sum =0;//static 修身的变量在数据段；不会被函数栈回收
    int *p = add;
    int i;
    for(i=1;i<=x;i++){
        sum +=i;
    }
    return p;
    //return ∑//会警告 返回的是局部变量的地址
}