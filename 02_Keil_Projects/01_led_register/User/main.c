#include<stm32f10x.h>
// 查手册 找基地址和偏移地址等
// 宏定义 寄存器地址与名称 优化代码 各个模块结构体 按照内存顺序宏定义了指针,简化代码
// 置零位与，置一位或 
// 位运算 精确化对单个位赋值 不影响其他端口 不粗糙 更精准
// 宏定义 每个位的名称 增强代码可读性 代码编写更方便 减少手册中寄存器位的查看 提高编码效率
// 位的宏定义将位上的值变成1，供作位运算，恰好可以只对一个位的数据进行处理
int main(void)
{
	// 1. 开启时钟
//	RCC->APB2ENR = 4; // ...0100
	
	// 第二位置1
//	RCC->APB2ENR |= (1<<2);
	
	// 最终优化
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	// 2. 配置GPIO工作模式
//	GPIOA->CRL = 3; // ...0011
	
	//前四位置1 1 0 0
//	GPIOA->CRL |= ((1<<0)|(1<<1));
//	GPIOA->CRL |= (1<<1);
//	GPIOA->CRL &= ~((1<<3)|(1<<2));
//	GPIOA->CRL &= ~(1<<2);
	
	// 最终进化
	GPIOA->CRL &= ~GPIO_CRL_CNF0;
	GPIOA->CRL |= GPIO_CRL_MODE0;
	
	GPIOA->CRL &= ~GPIO_CRL_CNF1;
	GPIOA->CRL |= GPIO_CRL_MODE1;
	
	GPIOA->CRH &= ~GPIO_CRH_CNF8;
	GPIOA->CRH |= GPIO_CRH_MODE8;
	
	// 3. 设置PA0为低电平
//	GPIOA->ODR = 0xfffe; // 0位置0
	
	// 第零位置0
//	GPIOA->ODR &= ~(1<<0);

	// 最终进化
	GPIOA->ODR &= ~GPIO_ODR_ODR0;     // 置0
	GPIOA->ODR &= ~GPIO_ODR_ODR1;
	GPIOA->ODR &= ~GPIO_ODR_ODR8;
	
	// 4. 死循环保持状态
	while(1){}
}
