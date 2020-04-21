#include "natural.h"
#include "rational.h"
#include "integer.h"
#include "polinomial.h"
//P.k=-1 при ошибке
polinom read_PP()
{
	polinom P;
	printf("Введите степень полинома\n");
	if (scanf("%d", &(P.k)) == EOF) { printf("ошибка в read_PP\n"); P.k = -1; return P; }
	P.mas = new rational_number[P.k + 3];
	if (P.mas == NULL) { printf(""); P.k = -1; return P; }
	printf("Введите коэффициенты полинома. Не забывайте, что ноль - тоже коэффициент.\n");
	for (int i = P.k; i >= 0; i--)
		P.mas[i] = read_QQ();
	return P;
}
//-1 при ошибке(!)
int free_P(polinom P)
{
	rational_number* Q, q;
	for (int i = P.k; i >= 0; i--)
	{
		q = P.mas[i];
		if (free_Q(q) == -1) { printf("ошибка в free_P\n"); return -1; }
	}
	Q = P.mas;
	//check
	if (Q == NULL) { printf("пустой указатель в free_P\n"); return -1; }
	//
	delete[] Q;
	Q = NULL;
	return 0;
}
int print_PP(polinom P)
{
	for (int i = P.k; i >= 0; i--)
	{
		//P.mas[i]=RED_Q_Q(P.mas[i]);
		if (P.mas[i].sign) printf("-");
		else printf("+");
		if (!(INT_Q_B(P.mas[i]) && P.mas[i].ch[0] == 1 && P.mas[i].n == 1 && i != 0))
			for (int j = P.mas[i].n - 1; j >= 0; j--) printf("%d", P.mas[i].ch[j]);
		if (!INT_Q_B(P.mas[i])) {
			printf("/");
			for (int j = P.mas[i].m - 1; j >= 0; j--) printf("%d", P.mas[i].zn[j]);
		}
		if (i == 1) printf("x");
		else if (i) printf("x^%d", i);
	}
	printf("\n");
	return 0;
}
polinom Pcpy(polinom P)
{
	polinom P1; int i;
	P1.k = P.k;
	P1.mas = new rational_number[P.k + 3];
	for (i = P.k; i >= 0; i--)
		P1.mas[i] = Qcpy(P.mas[i]);
	return P1;
}
polinom ADD_PP_P(polinom P1, polinom P2)//1
{
	polinom P; int max = P1.k;
	if (P2.k > max) max = P2.k;
	P.k = max;
	P.mas = new rational_number[max + 3];
	for (int i = max; i >= 0; i--)
		if ((i <= P1.k) && (i <= P2.k)) P.mas[i] = ADD_QQ_Q(P1.mas[i], P2.mas[i]);
		else if (i > P1.k) P.mas[i] = Qcpy(P2.mas[i]);
		else P.mas[i] = Qcpy(P1.mas[i]);
	return P;
}
polinom SUB_PP_P(polinom P1, polinom P2)//2
{
	polinom P; int max = P1.k;
	if (P2.k > max) max = P2.k;
	P.k = max;
	P.mas = new rational_number[max + 3];
	for (int i = max; i >= 0; i--)
		if ((i <= P1.k) && (i <= P2.k)) P.mas[i] = SUB_QQ_Q(P1.mas[i], P2.mas[i]);
		else if (i > P1.k) P.mas[i] = Qcpy(P2.mas[i]);
		else P.mas[i] = Qcpy(P1.mas[i]);
	return P;
}
polinom MUL_PQ_P(polinom P1, rational_number Q)//3
{
	polinom P;
	P.k = P1.k;
	P.mas = new rational_number[P.k + 3];
	for (int i = P.k; i >= 0; i--)
		P.mas[i] = MUL_QQ_Q(P1.mas[i], Q);
	return P;
}
polinom MUL_Pxk_P(polinom P1, int k)//4
{
	polinom P;
	rational_number Q;
	P.k = P1.k + k;
	P.mas = new rational_number[P.k + 3];
	for (int i = 0; i <= k; i++)
	{
		Q.zn = new uint8_t[2]; Q.zn[0] = 1;
		Q.ch = new uint8_t[2]; Q.ch[0] = 0;
		Q.n = 1;
		Q.m = 1;
		Q.sign = 0;
		P.mas[i] = Q;
	}
	for (int i = 0; i <= P1.k; i++)
		(P.mas[i + k]) = Qcpy(P1.mas[i]);
	return P;
}
rational_number LED_P_Q(polinom P)//5
{
	return P.mas[P.k];
}
int DEG_P_N(polinom P)//6
{
	return P.k;
}
//P.k==-1 в случае ошибки
polinom FAC_P_Q(polinom P)//7
{
	polinom P1;
	P1.k = P.k;
	int NokM, NodN, x, i, MAXSIZE_P = P.k + 3;
	uint8_t* Ch, * Zn, * Nok, * Nod, * temp, * ultratemp;
	P1.mas = new rational_number[MAXSIZE_P];
	if (P.mas == NULL) { printf("пустой указатель в FAC_P_Q\n"); P.k = -1; return P; }//check
	Nok = new uint8_t[P.mas[0].m];
	Nod = new uint8_t[P.mas[0].n];
	if (Nod == NULL || Nok == NULL) { printf("пустой указатель в FAC_P_Q\n"); P.k = -1; return P; }//check
	NokM = P.mas[0].m;
	NodN = P.mas[0].n;
	if (numbcpy(Nok, P.mas[0].zn, P.mas[0].m)) { printf("numbcpy in FAC_P_Q\n"); P.k = -1; return P; }
	if (numbcpy(Nod, P.mas[0].ch, P.mas[0].n)) { printf("numbcpy in FAC_P_Q\n"); P.k = -1; return P; }
	for (i = P.k; i > 0; i--)
	{
		Zn = new uint8_t[P.mas[i].m + 1];
		Ch = new uint8_t[P.mas[i].n + 1];
		if (Zn == NULL || Ch == NULL) { printf("пустой указатель в FAC_P_Q\n"); P.k = -1; return P; }//check
		if (numbcpy(Zn, P.mas[i].zn, P.mas[i].m)) { printf("numbcpy in FAC_P_Q\n"); P.k = -1; return P; }//check
		if (numbcpy(Ch, P.mas[i].ch, P.mas[i].n)) { printf("numbcpy in FAC_P_Q\n"); P.k = -1; return P; }//check
		x = P.mas[i].n;
		temp = LCM_NN_N(&Nok, &Zn, NokM, P.mas[i].m, &NokM);
		int MAXSIZE_Nok = int(_msize(Nok));
		delete[] Nok; Nok = NULL;
		Nok = temp;
		Nod = GCF_NN_N(&Nod, &Ch, &NodN, &x, &NodN);
		delete[] Zn; Zn = NULL;
		delete[] Ch; Ch = NULL;
	}
	for (i = P.k; i >= 0; i--)
	{
		ultratemp = MUL_NN_N(P.mas[i].ch, Nok, P.mas[i].n, NokM, &x);
		if (ultratemp != NULL && i < MAXSIZE_P) P1.mas[i].ch = ultratemp;
		else { printf("пустой указатель в FAC_P_Q\n"); P.k = -1; return P; }
		P1.mas[i].n = x;
		ultratemp = MUL_NN_N(P.mas[i].zn, Nod, P.mas[i].m, NodN, &x);
		if (ultratemp != NULL) P1.mas[i].zn = ultratemp;
		else { printf("пустой указатель в FAC_P_Q\n"); P.k = -1; return P; }
		P1.mas[i].m = x;
		P1.mas[i].sign = P.mas[i].sign;
		P1.mas[i] = RED_Q_Q(P1.mas[i]);
	}
	delete[] Nok;
	delete[] Nod;
	return P1;
}
polinom MUL_PP_P(polinom P1, polinom P2)//8
{
	polinom P; rational_number Q, Qt; int i, j;
	P.k = P1.k + P2.k;
	P.mas = new rational_number[P.k + 3];
	//check
	if (P.mas == NULL) { printf("пустой указатель в MUL_P_P"); P.k = -1; return P; }
	//
	for (i = P.k; i >= 0; i--) 
	{ 
		P.mas[i].m = 1;
		P.mas[i].n = 1;
		P.mas[i].ch = new uint8_t[3];
		P.mas[i].zn = new uint8_t[3];
		if (P.mas[i].ch == NULL || P.mas[i].zn == NULL) { printf("пустой указатель в MUL_P_P"); P.k = -1; return P; }//check
		P.mas[i].ch[0] = 0;
		P.mas[i].zn[0] = 1;
		P.mas[i].sign = 0;
	}
	for (i = P1.k; i >= 0; i--)
		for (j = P2.k; j >= 0; j--)
		{
			Q = MUL_QQ_Q(P1.mas[i], P2.mas[j]);
			Qt = ADD_QQ_Q(P.mas[i + j], Q);
			free_Q(Q);
			free_Q(P.mas[i + j]);
			P.mas[i + j] = Qt;
		}
	return P;
}
//P.k=-1 в случае ошибки
polinom DIV_PP_P(polinom P_input1, polinom P_input2)//9
{//портит исходные данные
	polinom P, P1 = P_input1, P2 = P_input2; int i, j, x; rational_number Q, Q1;
	if (P_input2.k > P_input1.k) { P1 = P_input2; P2 = P_input2; }
	if (P1.k == -1 || P2.k == -1) { printf("error from other function in DIV_P_P\n"); P.k = -1; return P; }//check
	if (P1.mas == NULL || P2.mas == NULL) { printf("error NULL pointer in DIV_P_P\n"); P.k = -1; return P; }//check
	P.k = P1.k - P2.k;
	P.mas = new rational_number[P.k+3];
	if (P.mas == NULL) { printf("error new in DIV_P_P\n"); P.k = -1; return P; }//check
	if (P.k < 0) { printf("error P.k<0 in DIV_P_P\n"); P.k = -1; return P; }//check
	for (i = P1.k; i >= P2.k; i--)
	{
		x = i - P2.k; 
		P.mas[x] = DIV_QQ_Q(P1.mas[i], P2.mas[P2.k]);
		if (P.mas[x].sign == -1) { printf("error from DIV_QQ_Q in DIV_P_P\n"); P.k = -1; return P; }//check
		P.mas[x] = RED_Q_Q(P.mas[x]);
		if (P.mas[x].sign == -1) { printf("error from RED_Q_Q in DIV_P_P\n"); P.k = -1; return P; }//check
		for (j = i - 1; j >= i - P2.k; j--)
		{
			Q = MUL_QQ_Q(P.mas[x], P2.mas[P2.k + j - i]);
			if (Q.sign == -1) { printf("error from MUL_QQ_Q in DIV_P_P\n"); P.k = -1; return P; }//check
			Q1 = SUB_QQ_Q(P1.mas[j], Q);
			if (Q1.sign == -1) { printf("error from SUB_QQ_Q in DIV_P_P\n"); P.k = -1; return P; }//check
			free_Q(Q); free_Q(P1.mas[j]);
			P1.mas[j] = Q1;
		}
	}
	return P;
}
polinom MOD_PP_P(polinom P1, polinom P2)//10
{
	polinom P; int i;
	P = DIV_PP_P(P1, P2);
	free_P(P);
	P.k = P2.k - 1;
	P.mas = new rational_number[P.k + 3];
	if (P.mas == NULL) { printf("error in MOD_P_P\n"); P.k = -1; return P; }//check
	for (i = P2.k - 1; i >= 0; i--)
		if (P.k == i && P1.mas[i].ch[0] == 0 && P1.mas[i].n == 1) P.k--;
		else P.mas[i] = RED_Q_Q(Qcpy(P1.mas[i]));
	if (P.k < 0) { P.k = 0; P.mas[0].ch = new uint8_t[2]; P.mas[0].ch[0] = 0; P.mas[0].n = 1; P.mas[0].sign = 0; P.mas[0].zn = new uint8_t[2]; P.mas[0].zn[0] = 1; P.mas[0].m = 1; }
	return P;
}

polinom GCF_PP_P(polinom P1, polinom P2)
{
	polinom P, PP, PP1=Pcpy(P1), PP2=Pcpy(P2);
	P = Pcpy(P2);
	PP = MOD_PP_P(P1, P2);
	while (!(PP.k == 0 && PP.mas[0].ch[0] == 0 && PP.mas[0].n == 1))
	{
		free_P(PP1);
		PP1 = Pcpy(PP);
		free_P(PP2);
		PP2 = MOD_PP_P(P,PP);
		free_P(P);
		free_P(PP);
		P = Pcpy(PP1);
		PP = Pcpy(PP2);
	}
	return P;
}
polinom DER_P_P(polinom P_input)//12
{
	polinom P; int i; rational_number Q;
	P.k = P_input.k - 1;
	P.mas = new rational_number[P_input.k+1];
	for (i = P_input.k; i > 0; i--)
	{
		Q = TRANS_int_Q(i);
		P.mas[i - 1] = MUL_QQ_Q(Q, P_input.mas[i]);
		free_Q(Q);
	}
	return P;
}

polinom NMR_P_P(polinom P_input)//13
{
	polinom P_output, P_temp,P_temp1;
	P_temp1 = Pcpy(P_input);
	P_temp = DER_P_P(P_input);
	P_output = GCF_PP_P(P_temp, P_temp1);
	free_P(P_temp);
	free_P(P_temp1);
	P_temp = DIV_PP_P(P_input,P_output);
	free_P(P_output);
	P_output = P_temp;
	return P_output;
}

int polinomial()
{
	printf("введите номер действия согласно инструкции в документации\n1) Сложение многочленов\n2) Вычитание многочленов\n3) Умножение многочлена на рациональное число\n4) Умножение многочлена на x^k\n5) Старший коэффициент многочлена\n6) Степень многочлена\n7) Вынесение из многочлена НОК знаменателей коэффициентов и НОД числителей\n8) Умножение многочленов\n9) Частное от деления многочлена на многочлен при делении с остатком\n10) Остаток от деления многочлена на многочлен при делении с остатком\n11) НОД многочленов\n12) Производная многочлена\n13) Преобразование многочлена — кратные корни в простые\n");
	int x, k; char c;
	polinom A, B, res, P_temp;
	rational_number Q;
	if (scanf("%d", &x) == EOF) return -1;
	if (x == 0) return 0;
	A = read_PP();
	switch (x) 
	{
		case 1:
			B = read_PP();
			res = ADD_PP_P(A, B);
			print_PP(res);
			free_P(A);
			free_P(B);
			free_P(res);
			break;
		case 2:
			B = read_PP();
			res = SUB_PP_P(A, B);
			print_PP(res);
			free_P(A);
			free_P(B);
			free_P(res);
			break;
		case 3:
			Q = read_QQ();
			res = MUL_PQ_P(A, Q);
			print_PP(res);
			free_P(A);
			free_Q(Q);
			free_P(res);
			break;
		case 4:
			printf("введите k\n");
			if (scanf("%d%c", &k, &c) == EOF) return -1;
			res = MUL_Pxk_P(A, k);
			print_PP(res);
			free_P(A);
			free_P(res);
			k = 0;
			break;
		case 5:
			Q = LED_P_Q(A);
			print_QQ(Q);
			free_P(A);
			break;
		case 6:
			k = DEG_P_N(A);
			printf("%d\n", k);
			free_P(A);
			k = 0;
			break;
		case 7:
			res = FAC_P_Q(A);
			print_PP(res);
			free_P(A);
			free_P(res);
			break;
		case 8:
			B = read_PP();
			res = MUL_PP_P(A, B);
			print_PP(res);
			free_P(A);
			free_P(B);
			free_P(res);
			break;
		case 9:
			B = read_PP();
			res = DIV_PP_P(A, B);
			print_PP(res);
			free_P(A);
			free_P(B);
			free_P(res);
			break;
		case 10:
			B = read_PP();
			res = MOD_PP_P(A, B);
			print_PP(res);
			free_P(A);
			free_P(B);
			free_P(res);
			break;
		case 11:
			B = read_PP();
			res = GCF_PP_P(A, B);
			print_PP(res);
			free_P(A);
			free_P(B);
			free_P(res);
			break;
		case 12:
			res = DER_P_P(A);
			print_PP(res);
			free_P(A);
			free_P(res);
			break;
		case 13:
			P_temp = NMR_P_P(A);
			res = FAC_P_Q(P_temp);
			print_PP(res);
			free_P(P_temp);
			free_P(A);
			free_P(res);
			break;
		default: return 0;
			break;
	}
	return 0;
}