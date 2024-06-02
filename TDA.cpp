#include<iostream>
#include<string.h>
#include "TDA.h"
#include<fstream>
using namespace std;
//Se crea un sst en el main y se lee el texto. sobre el sst cerado se maneja el resto. 

void REVERSO(int l, int r, super_string & s){
	super_string s1, s2, s3, s4;
	s.separar(l, s1, s2);
	s2.separar(r-l+1, s3, s4);
	s3.reverso();
	s1.juntar(s3);
	s1.juntar(s4);
	s.limpiar();
	s.juntar(s1);
	s1.limpiar();
	s2.limpiar();
	s3.limpiar();
	s4.limpiar();
}

void ELIMINAR(int l, int r, super_string & s){
	super_string s1, s2, s3, s4;
	s.separar(l, s1, s2);
	s2.separar(r-l+1, s3, s4);
	s1.juntar(s4);
	s.limpiar();
	s.juntar(s1);
	s1.limpiar();
	s2.limpiar();
	s3.limpiar();
	s4.limpiar();
}
 void INSERTAR(int i, super_string & s, string S){
	super_string nuevo,s1, s2;
	for (int k =0; k<S.length(); k++){
		nuevo.agregar(S[k]);
	}
	s.separar(i, s1, s2);
	s1.juntar(nuevo);
	s1.juntar(s2);
	s.limpiar();
	s.juntar(s1);
	nuevo.limpiar();
	s1.limpiar();
	s2.limpiar();
 }
void MOSTRAR(super_string &s){
	string actual = s.stringizar();
	cout<<actual<<"\n";
}
int main(){
	super_string s;
	ifstream archivo;
	string lineaActual = "FIN";
	char caracterActual;
	archivo.open("prueba.txt", ios::in);
	archivo>>lineaActual;
	while(lineaActual!="FIN"){
		if (lineaActual == "REVERSO") {
			int l, r;
			archivo>>l;
			archivo>>r;
			REVERSO(l, r, s);
        } else if (lineaActual == "ELIMINAR") {
            int l, r;
			archivo>>l;
			archivo>>r;
			ELIMINAR(l, r, s);
        } else if (lineaActual == "INSERTAR") {
            int i;
            archivo>>i;
            string S;
            archivo>>S;
            INSERTAR(i, s, S);
        } else if (lineaActual == "RECORTAR") {
            // Código para la acción RECORTAR
            cout<<"Funcion en progreso...";
        } else if (lineaActual == "MOSTRAR") {
            MOSTRAR(s);
        };
		archivo>>lineaActual;
	}
	
	
	return 0;
}
