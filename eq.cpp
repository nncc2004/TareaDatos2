#include<iostream>

using namespace std;

/////////////////////////////////////////////////////////////////////////////

struct Lista //nodo de la lista
{
	int indice;
	Lista *sig;
		
	Lista(int x) : indice(x),sig(NULL){} //constructor
};

/////////////////////////////////////////////////////////////////////////////

struct Nodo //nodo del arbol
{
	int indice;
	Nodo *der;
	Nodo *izq;
	
	Nodo(int x): indice(x),der(NULL),izq(NULL){}	//constructor
};

/////////////////////////////////////////////////////////////////////////////

void insertar_en_lista(Lista*& elemento, int dato)
{
	Lista* nuevo = new Lista(dato); //creo un nuevo nodo con el valor de dato
	if(elemento == NULL || elemento->indice >= dato) // esto si el dato se inserta en la cabeza de la lista
	{
		nuevo->sig = elemento;
		elemento = nuevo; 
	}
	
	else // si no se inserta en la cabeza de la lista, busco donde insertarlo en la lista
	{
		Lista* posElemento = elemento;
		while(posElemento->sig != NULL && posElemento->sig->indice < dato) // con este while encuentro la posicion donde insetar el nuevo nodo
		{
			posElemento = posElemento->sig;
		}
		nuevo->sig = posElemento->sig; //si tengo [1,3,5] y quiero insertar 4, nuevo = 4, posElemento -> 1 es != NULL y menor que 4, lo mismo con el 3
		posElemento->sig = nuevo; // luego, al llegar al 5, es != NULL pero no cumple con 5<4, por lo tanto, nuevo->sig apunta a 5 y posElemento->sig(3->sig) = 4
	}
}

/////////////////////////////////////////////////////////////////////////////

//para encontrar el largo de la lista
int Longitud(Lista* element) // element es un nodo que apunta al primer elemento de la lista
{
	int longitud = 0;
	while(element != NULL)
	{
		longitud++; //aumenta en 1 la longitud de la lista
		element = element->sig; //para pasar al siguiente nodo 
	}
	return longitud;
}

/////////////////////////////////////////////////////////////////////////////

//inicio y fin es para dividir la lista en sublistas, es decir, desde donde hasta donde recorro para equilibrar (""""""recortar"""""")
Nodo* crearArbol(Lista*& elemento,int inicio, int fin) //paso elemento por referencia pq se modifica | inicio y fin son las posiciones, no elementos de la lista
{
	//con este condicional verifico si la sublista esta vacía
	if(inicio>fin) //si el inicio por ej es 0 y fin es -1, recorro desde a 0 hasta -1, como no se puede -> NULL
	{
		return NULL;
	}
	
	//aca busco el medio de la lista para establecer cual es la raiz
	int  mitad = inicio + ((fin - inicio) / 2); //si inicio en 0 y termino en 5 -> la mitad = 0+(5-0)/2 -> 2 (posicion)
	
	//para armar el subarbol izquierdo
	Nodo* sub_arbol_izq = crearArbol(elemento,inicio,mitad-1); //pido "la lista", desde donde se crea el sub-arbol y la mitad -1 (le resto 1 pq el medio es la raiz)

	Nodo* raiz = new Nodo(elemento->indice); //defino la raiz
	raiz->izq = sub_arbol_izq; //asigno el sub arbol izq a la parte izquierda del arbol(valga la redundancia)
	
	elemento = elemento->sig; //para mover el puntero a la siguiente posicion
	
	Nodo* sub_arbol_der = crearArbol(elemento,mitad+1,fin); //lo mismo pero desde la mitad +1 en adelante
	raiz->der = sub_arbol_der;
	
	return raiz;
}

/////////////////////////////////////////////////////////////////////////////

// EJEMPLO PASO A PASO
// Ejemplo: lista = [0,1,2,3,4,5]
// Para crear el arbol paso (lista, inicio = 0, fin = 5)
// el medio es 0 + ((5-0)/2) -> 0 + 2 ya que es div entera -> medio = 2                                       2
// sub arbol izq -> (lista,0,1)                                                                             /  \
// medio sub arbol izq -> 0+((1-0)/2) -> 0+0 -> 0                                                         0     4
// vuelvo a hacer el sub-arbol izq --> (lista,0,-1) -> return NULL                                         \   / \
// para armar el sub arbol derecho de la raiz 0: (lista, medio +1, fin) -> (lista, 0+1, 1)                  1 3   5
// medio = 1 + ((1-1)/2) -> 1
// ¿se puede crear un sub-arbol izquierdo? (lista, inicio = 1, fin = 0) -> NULL
// para el subarbol derecho: (lista,inicio(medio+1),fin) -> (lista,3,5)
// medio -> 3 + ((5-3)/2) -> 3 + 1 -> 4
// sub-arbol derecho (lista,5,5) 
// medio -> 5
// sub-arbol derecho(6,5) -> NULL
// sub-arbol izq -> (lista,3,3)
// medio -> 3 + ((3-3)/2) -> 3
// sub-arbol izq -> (lista,2,3) -> NULL
// tuki

/////////////////////////////////////////////////////////////////////////////

Nodo* construirArbol(Lista* lista) // construyo el arbol desde la lista ordenada
{
	int largo = Longitud(lista); //para obtener el largo de la lista y con eso, el numero total de nodos
	//ya que crearArbol devuelve la raiz del arbol ya equilibrado:
	return crearArbol(lista,0,largo-1); // retornando el arbol binario de busqueda equilibrado
}

/////////////////////////////////////////////////////////////////////////////

void recorrer_in_orden(Nodo* raiz)
{
	if(raiz == NULL)
	{
		return;
	}
	else
	{
		recorrer_in_orden(raiz->izq);
		cout<<raiz->indice<<" ";
		recorrer_in_orden(raiz->der);
	}
}

/////////////////////////////////////////////////////////////////////////////

int altura(Nodo* arbol)
{
	int Altura=1; // lo inicializo en 1 para agregar la altura de la raiz
	if(arbol == NULL) 
	{
		return 0;
	}
	else
	{
		int altura_subarbol_izq = altura(arbol->izq); //recursivamente se va aumentando la altura cada vez que de itera sobre a parte izquierda del arbol
		int altura_subarbol_der = altura(arbol->der); //lo mismo pero a la derecha
		if(altura_subarbol_izq>altura_subarbol_der)
		{
			Altura = Altura + altura_subarbol_izq;
		}
		else
		{
			Altura = Altura + altura_subarbol_der;
		}
	}
	return Altura;
}

/////////////////////////////////////////////////////////////////////////////

int main()
{
	Lista* elemento = NULL;
	insertar_en_lista(elemento,10);
	insertar_en_lista(elemento,1);
	insertar_en_lista(elemento,4);
	insertar_en_lista(elemento,3);
	insertar_en_lista(elemento,2);
	insertar_en_lista(elemento,5);
	insertar_en_lista(elemento,0);
	insertar_en_lista(elemento,11);
	
	Nodo* arbol = construirArbol(elemento);
	recorrer_in_orden(arbol);
	cout<<"\n";
	int altura_arbol = altura(arbol);
	cout<<altura_arbol;
	
	
	return 0;
}
