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

int super_string::altura(nodo*nodo){
	int Altura = 0;
	if(nodo == NULL) 
	{
		return 0;
	}
	else
	{
		int altura_subarbol_izq = altura(nodo->left); //recursivamente se va aumentando la altura cada vez que de itera sobre a parte izquierda del arbol
		int altura_subarbol_der = altura(nodo->right); //lo mismo pero a la derecha
		if(altura_subarbol_izq>altura_subarbol_der)
		{
			Altura = 1 + altura_subarbol_izq;
		}
		else
		{
			Altura = 1 + altura_subarbol_der;
		}
	}
	return Altura;
}
int super_string::recortar(){
	nodo** arreglo = new nodo*[length];
	int k = 0;
	InOrdenRecortar(root, arreglo, k);
	PostOrdenHelp(root);// limpiar el arbol antiguo
	root = balanceo(arreglo, 0 , length-1);
	height = altura(root);
	return height;
}

#endif
