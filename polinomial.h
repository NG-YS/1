struct polinom { 
	int k;//старшая степень полинома, иначе говоря, длина массива коэффициэнтов 
	struct rational_number* mas; //массив рациональнах коэффициентов
};
int polinomial();//main in file
struct polinom read_PP();//serv
int free_P(polinom P);//serv
int print_PP(polinom P);//serv
polinom ADD_PP_P(polinom P1, polinom P2);//1
polinom SUB_PP_P(polinom P1, polinom P2);//2
polinom MUL_PQ_P(polinom P1, rational_number Q);//3
polinom MUL_Pxk_P(polinom P1, int k);//4
rational_number LED_P_Q(polinom P);//5
int DEG_P_N(polinom P);//6

polinom DER_P_P(polinom P_input);//12