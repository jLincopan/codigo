#include <stdio.h>
#include <string.h>
#include "arbolBin.h"

datoArbol NODO_NULO = {0};

ArbolBin arbolToBin(Arbol n){
	ArbolBin bin;
	bin.primero = n.primero;
	return bin;
}

ArbolBin creaNodo(datoArbol u){
	//crea el nodo raiz
	Arbol raiz = creaRaiz(u);
	//se crean e inserta el nodo terminal izquierdo
	Arbol Ti = creaRaiz(NODO_NULO);
	insertaHijoMasIzq(raiz, Ti);
	Ti = hijoMasIzq(raiz);
	//se crean e inserta el nodo terminal derecho
	Arbol Td = creaRaiz(NODO_NULO);
	insertaHermanoDer(Ti,Td);
	return arbolToBin(raiz);
}

ArbolBin hijoIzq(ArbolBin n){
	Arbol Ti = hijoMasIzq(n);
	return arbolToBin(Ti);
}

bool existeHijoIzq(ArbolBin n) {
	Arbol Ti = hijoIzq(n);
	if(esNulo(Ti))
		return false;
	return true;
}

bool existeHijoDer(ArbolBin n) {
	Arbol Ti = hijoDer(n);
	if(esNulo(Ti))
		return false;
	return true;
}

ArbolBin hijoDer(ArbolBin n){
	ArbolBin Ti = hijoIzq(n);
	Arbol Td = hermanoDer(Ti);
	return arbolToBin(Td);
}

void insertaHijoIzq(ArbolBin & n, ArbolBin & Ti){
	ArbolBin hi = podarHijoIzq(n);
	anula((Arbol&)hi);
	insertaHijoMasIzq(n, Ti);
}

void insertaHijoDer(ArbolBin & n, ArbolBin & Td){
	ArbolBin hd = podarHijoDer(n);
	anula((Arbol&)hd);
	ArbolBin Ti = hijoIzq(n);
	insertaHermanoDer(Ti, Td);	
}

datoArbol etiqueta(ArbolBin n){
	return etiqueta((Arbol)n);	
}

void reEtiqueta(datoArbol e, ArbolBin & n, ArbolBin raiz){
	reEtiqueta(e, (Arbol&) n, (Arbol) raiz);
}

ArbolBin padre(ArbolBin n, ArbolBin raiz){
	Arbol p;
	if(esNodoTerminal(n)){
		return arbolToBin(p); //Arbol nulo
	}
	p = padre((Arbol)n, (Arbol) raiz);
	return arbolToBin(p);
}

ArbolBin raiz(ArbolBin n){
	return arbolToBin(raiz((Arbol)n));	
}

void anula(ArbolBin & raiz){
	anula((Arbol&)raiz);
}

ArbolBin podarHijoIzq(ArbolBin  & n){
	Arbol Ti = podarHijoMasIzq(n);
	return arbolToBin(Ti);
}
ArbolBin podarHijoDer(ArbolBin  & n){
	ArbolBin Ti = hijoIzq(n);
	Arbol Td = podarHermanoDer(Ti);
	return arbolToBin(Td);
}

// Adicionales al TDA
bool esHoja(ArbolBin n){
	ArbolBin Ti = hijoIzq(n);
	ArbolBin Td = hijoDer(n);
	return esNodoTerminal(Ti) && esNodoTerminal(Td);
}

bool esNulo(ArbolBin raiz){
	return esNulo((Arbol)raiz);
}

bool esNodoTerminal(ArbolBin n){
	datoArbol temp = etiqueta(n);
	if(strncmp(temp.fecha_fallecimiento, NODO_NULO.fecha_fallecimiento, sizeof(NODO_NULO.fecha_fallecimiento)) == 0) {
		return true;
	} else {
		return false;
	}
}

void ordenSimetrico(ArbolBin n){
	if(esNulo(n) || esNodoTerminal(n))
		return;
	ordenSimetrico(hijoIzq(n));
	mostrarDatos(n);
	ordenSimetrico(hijoDer(n));
}

void ordenPrevio(ArbolBin n){
	if(esNulo(n) || esNodoTerminal(n))
		return;
	datoArbol dato = etiqueta(n);
	mostrarDatos(n);
	ordenPrevio(hijoIzq(n));
	ordenPrevio(hijoDer(n));
}
void ordenPosterior(ArbolBin n){
	if(esNulo(n) || esNodoTerminal(n))
		return;
	ordenPosterior(hijoIzq(n));
	ordenPosterior(hijoDer(n));
	datoArbol dato = etiqueta(n);
	mostrarDatos(n);
}

datoArbol registrarDatos(unsigned int generacion, const char nombre[], const char nacimiento[], const char fallecimiento[]) {
	datoArbol tmp;
	tmp.generacion = generacion;
	strncpy(tmp.nombre, nombre, sizeof(tmp.nombre));
	strncpy(tmp.fecha_nacimiento, nacimiento, sizeof(tmp.fecha_nacimiento));
	strncpy(tmp.fecha_fallecimiento, fallecimiento, sizeof(tmp.fecha_fallecimiento));
	
	return tmp;
}

void mostrarDatos(ArbolBin dato) {
	datoArbol d = etiqueta(dato);

	printf("Generación: %i Nombre: %s Nacimiento: %s Fallecimiento: %s\n",d.generacion, d.nombre, d.fecha_nacimiento, d.fecha_fallecimiento);
}