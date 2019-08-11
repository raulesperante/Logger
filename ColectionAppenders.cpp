#include <iostream>
#include "ColectionAppenders.h"

using UndavColectionAppenders::ColectionAppenders;

struct NodoSet{
	void* item;
	NodoSet* next;
};

struct UndavColectionAppenders::ColectionAppenders{
	NodoSet* first;
	UndavColectionAppenders::Compare comparator;
};

NodoSet* getNodoIterador(UndavColectionAppenders::IteratorUndav::Iterator* iterador);

ColectionAppenders* UndavColectionAppenders::Crear(UndavColectionAppenders::Compare comparator){
	ColectionAppenders* colectionAppender = new ColectionAppenders;
	colectionAppender->first = NULL;
	colectionAppender->comparator = comparator;
	return colectionAppender;
}

NodoSet* CrearNodo(void* item, NodoSet* next){
	NodoSet* nuevoNodo = new NodoSet;
	nuevoNodo->item = item;
	nuevoNodo->next = next;
	return nuevoNodo;
}

bool UndavColectionAppenders::EstaVacia(const ColectionAppenders* colectionAppender){
	return colectionAppender->first==NULL;
}


bool UndavColectionAppenders::Contains(ColectionAppenders* colectionAppender, void* item, UndavColectionAppenders::Compare compare){
	bool isItem = false;
	void* auxItem = NULL;
	UndavColectionAppenders::IteratorUndav::Iterator* iterador = UndavColectionAppenders::IteratorUndav::Create(colectionAppender);
	while(!UndavColectionAppenders::IteratorUndav::IsEnd(iterador) && !isItem){
		auxItem = UndavColectionAppenders::IteratorUndav::Next(iterador);
		isItem = compare(auxItem, item);
	}
	UndavColectionAppenders::IteratorUndav::Destroy(iterador);
	return isItem;
}



void UndavColectionAppenders::Agregar(ColectionAppenders* colectionAppender, void* item){
	if(EstaVacia(colectionAppender)){
		colectionAppender->first = CrearNodo(item, NULL);
		//Si el item no esta lo agrego
	}else if(!UndavColectionAppenders::Contains(colectionAppender, item, colectionAppender->comparator)){

			NodoSet* aux = colectionAppender->first;
			colectionAppender->first = CrearNodo(item, aux);
		}
	}

void Del(ColectionAppenders* colectionAppender, void* item, UndavColectionAppenders::Compare compare){
	NodoSet* iterador = colectionAppender->first;
	NodoSet* previous = NULL;
	while(iterador != NULL && !compare(iterador->item, item)){
		previous = iterador;
		iterador = iterador->next;
	}
	if(iterador == NULL){
		std::cout<<"Elemento no encontrado"<<std::endl;
	}
	else if(previous == NULL){
		colectionAppender->first = iterador->next;
		delete iterador;
	}else{
		previous->next = iterador->next;
		delete iterador;
	}
}

void UndavColectionAppenders::EliminarItem(ColectionAppenders* colectionAppender, void* item){
	Del(colectionAppender, item, colectionAppender->comparator);

}

void UndavColectionAppenders::Destruir(ColectionAppenders* colectionAppender){
	NodoSet* iterador = colectionAppender->first;
	NodoSet* auxiliar;
	while(iterador != NULL){
		auxiliar = iterador;
		iterador = iterador->next;
		delete auxiliar;
	}
	delete iterador;
}

struct UndavColectionAppenders::IteratorUndav::Iterator{
	NodoSet* currentNode;
};

NodoSet* getNodoIterador(UndavColectionAppenders::IteratorUndav::Iterator* iterador){
	return iterador->currentNode;
}

UndavColectionAppenders::IteratorUndav::Iterator* UndavColectionAppenders::IteratorUndav::Create(ColectionAppenders* colectionAppender){
	Iterator* nuevo = new Iterator;
	nuevo->currentNode = colectionAppender->first;

	return nuevo;
}

bool UndavColectionAppenders::IteratorUndav::IsEnd(Iterator* iterator){
	return iterator->currentNode == NULL;
}

void* UndavColectionAppenders::IteratorUndav::Next(Iterator* iterator){
	void* auxiliar = NULL;
	if(iterator->currentNode != NULL){
		auxiliar = iterator->currentNode->item;
		iterator->currentNode = iterator->currentNode->next;
	}
	return auxiliar;
}

void UndavColectionAppenders::IteratorUndav::Destroy(Iterator* iterator){
	delete iterator;
}
