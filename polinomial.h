
struct polinom {
	int k;//старшая степень полинома, иначе говоря, длина массива коэффициэнтов 
	struct rational_number* mas; //массив рациональнах коэффициентов
};
int polinomial();//main in file
struct polinom read_PP();//serv
int free_P(struct polinom P);//serv
int print_PP(struct polinom P);//serv
struct polinom ADD_PP_P(struct polinom P1, struct polinom P2);//1
struct polinom SUB_PP_P(struct polinom P1, struct polinom P2);//2
struct polinom MUL_PQ_P(struct polinom P1, struct rational_number Q);//3
struct polinom MUL_Pxk_P(struct polinom P1, int k);//4
struct rational_number LED_P_Q(struct polinom P);//5
int DEG_P_N(struct polinom P);//6
