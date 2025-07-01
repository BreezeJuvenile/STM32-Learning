#include<stm32f10x.h>

void Delay_us(uint16_t us);
void Delay_ms(uint16_t ms);
void Delay_s(uint16_t s);

int main(void)
{
	// 1. 开启时钟
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	
	// 2. 配置GPIO工作模式	
	GPIOA->CRL &= ~GPIO_CRL_CNF0;
	GPIOA->CRL |= GPIO_CRL_MODE0;
	
	GPIOA->CRL &= ~GPIO_CRL_CNF1;
	GPIOA->CRL |= GPIO_CRL_MODE1;
	
	GPIOA->CRH &= ~GPIO_CRH_CNF8;
	GPIOA->CRH |= GPIO_CRH_MODE8;
	
	// 3. 设置PA0、PA1、PA8默认高电平
	GPIOA->ODR |= GPIO_ODR_ODR0;     
	GPIOA->ODR |= GPIO_ODR_ODR1;
	GPIOA->ODR |= GPIO_ODR_ODR8;
	
	// 4. 死循环保持状态
	while(1)
	{
		GPIOA->ODR &= ~GPIO_ODR_ODR0;  // 亮灯
		Delay_ms(500);
		GPIOA->ODR |= GPIO_ODR_ODR0; // 灭灯

		GPIOA->ODR &= ~GPIO_ODR_ODR1; // 亮灯
		Delay_ms(500);
		GPIOA->ODR |= GPIO_ODR_ODR1; // 灭灯

		GPIOA->ODR &= ~GPIO_ODR_ODR8; // 亮灯
		Delay_ms(500);			// 延时500ms
		GPIOA->ODR |= GPIO_ODR_ODR8; // 灭灯
	}
}

// 延时函数 微秒为单位 利用系统的嘀嗒定时器 系统CPU频率 72MHz 一次嘀嗒 1/72 us
void Delay_us(uint16_t us)
{
	// 1. 装载一个计数值 1us 嘀嗒72次
	SysTick->LOAD = 72 * us;

	// 2. 配置嘀嗒定时器 使用系统时钟（1）、不开启中断（0）、打开使能寄存器（1）
	SysTick->CTRL |= 0x05;

	// 3. 等待计数值变为0，即判断配置标志位COUNTFLAG是否变为1 （我的理解：每一次计数完毕后会置0）
	while((SysTick->CTRL & SysTick_CTRL_COUNTFLAG) == 0)
	{}

	// 4. 关闭定时器
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE;   //（ 我的理解：使能寄存器置0）
}

void Delay_ms(uint16_t ms)
{
	while(ms--)
	{
		Delay_us(1000);
	}
}

void Delay_s(uint16_t s)
{
	while(s--)
	{
		Delay_ms(1000);
	}
}

