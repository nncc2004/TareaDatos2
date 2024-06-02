#ifndef recortarH
#define recortarH
#include "TDA.h"

super_string::nodo* super_string::balanceo(nodo** arreglo, int inicio, int final){
	if(inicio > final) return nullptr;
	
	int mitad = (inicio + final)/2;
	nodo* raiz = arreglo[mitad];
	raiz->left = balanceo(arreglo, inicio, mitad-1);
	raiz->right = balanceo(arreglo, mitad+1, final);
	return raiz;
}

void super_string::InOrdenRecortar(nodo*CurrNodo, nodo**arreglo, int &k){
	if(CurrNodo == nullptr) return;
	InOrdenRecortar(CurrNodo->left, arreglo, k);
	arreglo[k] = CurrNodo;
	k++;
	InOrdenRecortar(CurrNodo->right, arreglo, k);
}

int super_string::recortar(){
	nodo** arreglo = new nodo*[length];
	int k = 0;
	InOrdenRecortar(root, arreglo, k);
	PostOrdenHelp(root);// limpiar el arbol antiguo
	root = balanceo(arreglo, 0 , length-1);
	return 0;
}

#endif
