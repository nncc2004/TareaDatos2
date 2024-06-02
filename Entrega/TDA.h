#ifndef TDA
#define TDA
#include<iostream>
#include<string.h>

using namespace std;


//TDA
class super_string {
	private:
		struct nodo {
			nodo *left = nullptr, *right = nullptr;
			int index;
			char c;
			nodo(int index, char c) {} //CONTRSUCTOR!!!!
			nodo(){}
		};
		int height = 0; // Altura del árbol
		int length = 0; // Largo del super-string
		nodo* root = nullptr; // Raíz del super-string
	public:
		super_string() {}
		void juntar(super_string &s);
		void agregar(char c);
		void separar(int i, super_string &a, super_string &b);
		void reverso(); 
		int recortar();
		string stringizar(); 
		void limpiar();
		
		//recotar
		nodo* balanceo(nodo** arreglo, int inicio, int final);
		void InOrdenRecortar(nodo*CurrNodo, nodo** arreglo, int &k);
		int altura(nodo* nodo);

		//Funciones auxiliares extra:
		void InOrdenHelp(nodo* nodo, string & texto); //Para stringizar
		void InOrdenHelp2(nodo* nodo, string reversed); //Para reverse
		void InOrdenHelp3(nodo* nodo, int i, super_string &a, super_string &b); //Para separar
		void PostOrdenHelp(nodo* nodo);//Para limpiar


		
};
//Agregar (terminada)
void super_string::agregar(char c){
	//Crear el nodo
	nodo* NuevoNodo = new nodo;
	NuevoNodo->index = length;
	NuevoNodo->c = c;
	NuevoNodo->left = nullptr;
	NuevoNodo->right = nullptr;
	//Primero ver si el arbol esta vacio por medio de la raiz
	if(root == nullptr){
		root = NuevoNodo;
		length++;
		height = 1;
		return;
	}else{//Aca si el arbol no esta vacio
		nodo* Curr = root; //Como visto en clases para listas, nodo actual para poder recorrer
		int nivel = 1; //Una variable de nivel para poder ir viendo la profundidad y con eso el height del arbol
		//Se recorre el arbolhasta encntrar un espacio vacio como hijo derecho de un nodo y se inserta el nodo.
		while (true) {
            if (Curr->right != nullptr) {
                Curr = Curr->right;
            } else {
                Curr->right = NuevoNodo;
                length++;
                break;
            }
            nivel++;
        }
        //Revisar la profundidad del arbol con nivel
        if(nivel +1 > height){
        	height = nivel+1;
		}
	}
}
//Stringizar (terminada) + funcion auxiliar InordenHelp
void super_string::InOrdenHelp(nodo* nodo, string & texto){
	if(nodo == nullptr) return;
	InOrdenHelp(nodo->left, texto);
	texto += nodo->c;
	InOrdenHelp(nodo->right, texto);
}
string super_string::stringizar(){
	string texto;
	InOrdenHelp(root, texto);
	return texto;
}
//Juntar (terminada)
void super_string::juntar(super_string &s){
	//Verificar que s no este vacio
	if(s.root==nullptr) return;
	string s2 = s.stringizar();
	for(int k = 0; k<s2.length(); k++){
    	agregar(s2[k]);
	}
}
//Reverse (terminada) + funcion auxiliar InordenHelp2
void super_string::InOrdenHelp2(nodo* nodo, string reversed){
	if(nodo == nullptr) return;
	InOrdenHelp2(nodo->left, reversed);
	nodo->c = reversed[nodo->index];
	InOrdenHelp2(nodo->right, reversed);
}
void super_string::reverso(){
	string texto, reversed;
	texto = stringizar();
	for(int k = texto.length()-1; k>=0; k--){
		reversed += texto[k];
	}
	InOrdenHelp2(root, reversed);
}
//Separar (terminada) + funcion auxiliar InordenHelp3
void super_string::InOrdenHelp3(nodo* nodo, int i, super_string &a, super_string &b){
	if(nodo == nullptr) return;
	InOrdenHelp3(nodo->left, i, a, b);
	if(nodo->index<i){
		a.agregar(nodo->c);
	}else{
		b.agregar(nodo->c);
	}
	InOrdenHelp3(nodo->right,  i, a, b);
}
void super_string::separar(int i, super_string &a, super_string &b){
	InOrdenHelp3(root, i, a, b);
}
//Limpiar (terminada) + funcion auxiliar PostOrdenHelp
void super_string::PostOrdenHelp(nodo* nodo) {
    if (nodo == nullptr) return;
    PostOrdenHelp(nodo->left);
    PostOrdenHelp(nodo->right);
    delete nodo;
}
void super_string::limpiar(){
	PostOrdenHelp(root);
	root = nullptr;
	length = 0;
	height = 0;
}
#endif
