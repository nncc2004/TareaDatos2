#include<iostream>

using namespace std;

// VER LINEAS 172 Y 176 PARA VER LAS LISTAS A ELIMINAR

class super_string {
	private:
		struct nodo {
			nodo *left = NULL, *right = NULL;
			int index;
			char c;
			nodo(int index, char c): index(index),c(c) {}
			nodo(){}
		 };
		int height = 0; // Altura del árbol
		int length = 0; // Largo del super-string
		nodo* root = NULL; // Raíz del super-string
	
	public:
		super_string() {}
		
		//***********************************************************************************************************************
		struct Lista //para la lista donde voy a equilibrar
		{
			int indice;
			Lista *sig;
			char caracter;
			
			Lista(int i,char c) : indice(i), caracter(c), sig(NULL){} //constructor
		};
		//***********************************************************************************************************************
		void recorrer_agregar(nodo* raiz, Lista*& lista, Lista*& lista_fin) // aca recorro y construyo la lista enlazada :O
		{
			if(raiz == NULL){
				return;
			}
			else
			{
				recorrer_agregar(raiz->left,lista,lista_fin); // recorro el sub arbol izq
				Lista* nuevo = new Lista(raiz->index,raiz->c);
				if(lista == NULL)
				{
					lista = nuevo;
					lista_fin = lista;
				}
				else
				{
					lista_fin->sig = nuevo;
					lista_fin = nuevo;
				}
				recorrer_agregar(raiz->right,lista,lista_fin); //recorro el sub arbol der
			}
		}
		
		//***********************************************************************************************************************
		
		Lista* recorrer_in_orden(nodo* raiz) // recorro el arbol y retorno la lista enlazada
		{
			Lista* lista = NULL;
			Lista* lista_fin = NULL; //puntero que apunta al ultimo elemento de la lista, asi puedo agregar datos al final de la lista
			recorrer_agregar(raiz,lista,lista_fin);
			return lista;
		}
		
		//***********************************************************************************************************************
		
		void insertar_en_lista(Lista*& elemento,int dato, char caracter) //aca ordeno la lista para que los indices esten de menor a mayor
		{
			Lista* nuevo_nodo = new Lista(dato,caracter); //creo un nuevo nodo con el valor de dato y caracter
			if(elemento == NULL || elemento->indice >= dato) // si la lista esta vacia o el dato debe ser el primer elemento 
			{
				nuevo_nodo->sig = elemento; //el nuevo nodo va a apuntar a la cabeza de la lista
				elemento = nuevo_nodo; // el puntero de la lista ahora va a apuntar al nuevo nodo
			}
			
			else // si no se inserta en la cabeza de la lista, busco donde insertarlo en la lista
			{
				Lista* posElemento = elemento;
				while(posElemento->sig != NULL && posElemento->sig->indice < dato) // con este while encuentro la posicion donde insetar el nuevo nodo
				{
					posElemento = posElemento->sig;
				}
				nuevo_nodo->sig = posElemento->sig; //si tengo [1,3,5] y quiero insertar 4, nuevo = 4, posElemento -> 1 es != NULL y menor que 4, lo mismo con el 3
				posElemento->sig = nuevo_nodo; // luego, al llegar al 5, es != NULL pero no cumple con 5<4, por lo tanto, nuevo->sig apunta a 5 y posElemento->sig(3->sig) = 4
			}
		}
		
		//***********************************************************************************************************************
		int Longitud(Lista* elemento) //obtengo el largo de la lista
		{
			int longitud = 0;
			while(elemento != NULL)
			{
				longitud++; //aumenta en 1 la longitud de la lista
				elemento = elemento->sig; //para pasar al siguiente nodo 
			}
			return longitud;
		}
		//***********************************************************************************************************************
		nodo* crearArbol(Lista*& elemento,int inicio, int fin) //paso elemento por referencia | inicio y fin son las posiciones
		{
			//con este condicional verifico si la sublista esta vacía
			if(inicio>fin) //si el inicio por ej es 0 y fin es -1, recorro desde a 0 hasta -1, como no se puede -> NULL
			{
				return NULL;
			}
			
			//aca busco el medio de la lista para establecer cual es la raiz
			int  mitad = inicio + ((fin - inicio) / 2); //si inicio en 0 y termino en 5 -> la mitad = 0+(5-0)/2 -> 2 (posicion)
			
			//para armar el subarbol izquierdo
			nodo* sub_arbol_izq = crearArbol(elemento,inicio,mitad-1); //pido "la lista", desde donde se crea el sub-arbol y la mitad -1 (le resto 1 pq el medio es la raiz)
			
			//para verificar si el siguiente elemento es NULL
			if(elemento == NULL){
				return NULL;
			}
			
			nodo* raiz = new nodo(elemento->indice,elemento->caracter); //defino la raiz
			elemento = elemento->sig; //para mover el puntero a la siguiente posicion
			
			
			nodo* sub_arbol_der = crearArbol(elemento,mitad+1,fin); //lo mismo pero desde la mitad +1 en adelante
			
			raiz->left = sub_arbol_izq; //asigno el sub arbol izq a la parte izquierda del arbol(valga la redundancia)
			raiz->right = sub_arbol_der; //lo mismo
			
			return raiz;
		}
		//***********************************************************************************************************************
		nodo* construirArbol(Lista* lista) // construyo el arbol desde la lista ordenada
		{
			int tam_lista = Longitud(lista); //para obtener el largo de la lista y con eso, el numero total de nodos
			//ya que crearArbol devuelve la raiz del arbol ya equilibrado:
			return crearArbol(lista,0,tam_lista-1); // retornando el arbol binario de busqueda equilibrado
		}
		
		//***********************************************************************************************************************
		int altura(nodo* arbol)
		{
			int Altura = 0;
			if(arbol == NULL) 
			{
				return 0;
			}
			else
			{
				int altura_subarbol_izq = altura(arbol->left); //recursivamente se va aumentando la altura cada vez que de itera sobre a parte izquierda del arbol
				int altura_subarbol_der = altura(arbol->right); //lo mismo pero a la derecha
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
		//***********************************************************************************************************************
		int recortar() // Retorna this->height después de recortar
		{
			Lista* lista_nodos_arbol = recorrer_in_orden(root); //aca tengo la lista con el indice y el caracter de cada nodo del arbol
			Lista* lista_ordenada = NULL; //creo una lista vacia para ir guardando los datos ordenadamente
			
			while(lista_nodos_arbol != NULL) //aca inserto cada elemento de la lista que tiene los nodos, ordenadamente
			{
				insertar_en_lista(lista_ordenada,lista_nodos_arbol->indice,lista_nodos_arbol->caracter);
				lista_nodos_arbol = lista_nodos_arbol->sig;
			} //una vez terminado el while, tengo la lista ordenada 
			
			//ACA DEBERIA DE ELLIMNARSE LA LISTA "LISTA_NODOS_ARBOL", DESPUES NO SE USA
			
			nodo* arbol = construirArbol(lista_ordenada);
			
			//DESPUES DE CONSTUIR EL ARBOL YA NO NECESITO LA LISTA ORDENADA, ASI QUE SE ELIMINA
			
			height = altura(arbol);
			return height;
		}
		//***********************************************************************************************************************
	};



int main()
{
	
	return 0;
}


