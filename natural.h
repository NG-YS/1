#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include <locale.h>
#include <stdint.h>
#include <stdlib.h>
//serv - сервисные функции, необходимые для облегчения работы
//все функции типа int вернут -1 при ошибке, а все функции типа uint8_t* вернут NULL
int natural();//main in file
uint8_t* read_NN(int n);//serv
int print_NN(uint8_t* A, int n);//serv
int numbcpy(uint8_t* A, uint8_t* B, int n);//serv
int COM_NN_D(uint8_t* A, uint8_t* D, int n, int m);//1
int NZER_N_B(uint8_t* A, int n);//2
uint8_t* ADD_1N_N(uint8_t* A, int* n);//3
uint8_t* ADD_NN_N(uint8_t* A, uint8_t* B, int n, int m, int* p);//4
uint8_t* SUB_NN_N(uint8_t* A, uint8_t* B, int n, int m, int* p);//5
uint8_t* MUL_ND_N(uint8_t* A, int n, int a, int* p);//6
uint8_t* MUL_Nk_N(uint8_t* A, int n, int k, int* p);//7
uint8_t* MUL_NN_N(uint8_t* A, uint8_t* B, int n, int m, int* p);//8
uint8_t* SUB_NDN_N(uint8_t* A, uint8_t* B, int n, int m, int k, int* p);//9
int DIV_NN_Dk(uint8_t* A, uint8_t* B, int n, int m, int* k);//10
uint8_t* DIV_NN_N(uint8_t* A, uint8_t* B, int n, int m, int* p);//11
uint8_t* MOD_NN_N(uint8_t** AA, uint8_t** BB, int n, int m, int* p);//12
uint8_t* GCF_NN_N(uint8_t** AA, uint8_t** BB, int* n, int* m, int* p);//13
uint8_t* LCM_NN_N(uint8_t** AA, uint8_t** BB, int n, int m, int* p);//14
