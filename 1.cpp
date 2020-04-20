#include "natural.h"
#include "rational.h"
#include "integer.h"
#include "polinomial.h"
int main()
{
	setlocale(LC_ALL, "Russian");
	while(1)
	{
		printf("Введите номер, соответствующий множеству, с которым будет проводиться работа\n1) Натуральные числа\n2) Целые числа\n3) Рациональные числа\n4) Полиномы\n");
		int x, res;	char c;
		if (scanf("%d", &x) == EOF) return 1;
		switch (x)
		{
		case 0: if (scanf("%c", &c) == EOF) return 1; return 0;
			break;
		case 1:
			res = natural();
			if (res == -1) printf("Error Natural %d", res);
			break;
		case 2:
			res = integer();
			if (res == -1) printf("Error Integer %d", res);
			break;
		case 3:
			res = rational();
			if (res == -1) printf("Error Rational %d", res);
			break;
		case 4:
			res = polinomial();
			if (res == -1) printf("Error polynomial %d", res);
			break;
		default: printf("Неверный номер");
		}
	}
}