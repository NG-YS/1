struct rational_number {
	int n,m, sign;//n - числителя, m - знаменателя
	uint8_t* ch,*zn;//ch - числитель, zn, знаменатель
};
int rational();//main in file
int print_QQ(struct rational_number Q);//serv
struct rational_number Qcpy(struct rational_number Q);//srev
struct rational_number read_QQ();//serv
int free_Q(struct rational_number Q);//serv
struct rational_number RED_Q_Q(struct rational_number Q);//1
int INT_Q_B(struct rational_number Q);//2
struct rational_number TRANS_Z_Q(struct integer_number Z);//3
struct integer_number TRANS_Q_Z(struct rational_number Q);//4
struct rational_number ADD_QQ_Q(struct rational_number Q1, struct rational_number Q2);//5
struct rational_number SUB_QQ_Q(struct rational_number Q1, struct rational_number Q2);//6
struct rational_number MUL_QQ_Q(struct rational_number Q1, struct rational_number Q2);//7
struct rational_number DIV_QQ_Q(struct rational_number Q1, struct rational_number Q2);//8