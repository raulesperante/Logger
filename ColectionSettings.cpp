#include "ColectionSettings.h"
#include <cstring> // Se usa para NULL

using UndavColectionSettings::ColectionSettings;
using UndavColectionSettings::IteratorUndav::Iterator;

struct Node{
	void* item;
	Node* next;
};

struct UndavColectionSettings::ColectionSettings{
	Node* first;
};

ColectionSettings* UndavColectionSettings::Create(){
	ColectionSettings* colectionSetting = new ColectionSettings;
	colectionSetting->first = NULL;

	return colectionSetting;
}

Node* CreateNode(void* item, Node* next){
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = next;
	return newNode;
}

bool UndavColectionSettings::IsEmpty(const ColectionSettings* colectionSetting){
	return colectionSetting->first==NULL;
}

void UndavColectionSettings::Add(ColectionSettings* colectionSetting, void* item){
	if(IsEmpty(colectionSetting)){
		colectionSetting->first = CreateNode(item, NULL);
	}else{
		Node* aux = colectionSetting->first;
		colectionSetting->first = CreateNode(item, aux);
	}
}

void UndavColectionSettings::Destroy(ColectionSettings* colectionSetting){
	Node* iterator = colectionSetting->first;
	Node* auxiliar;
	while(iterator!=NULL){
		auxiliar = iterator;
		iterator = iterator->next;
		delete auxiliar;
	}

	delete colectionSetting;
}

struct UndavColectionSettings::IteratorUndav::Iterator{
	Node* currentNode;
};

UndavColectionSettings::IteratorUndav::Iterator* UndavColectionSettings::IteratorUndav::Create(ColectionSettings* colectionSetting){
	Iterator* nuevo = new Iterator;
	nuevo->currentNode = colectionSetting->first;

	return nuevo;
}

bool UndavColectionSettings::IteratorUndav::IsEnd(Iterator* iterator){
	return iterator->currentNode == NULL;
}


void* UndavColectionSettings::IteratorUndav::Next(Iterator* iterator){
	void* auxiliar = NULL;
	if(iterator->currentNode != NULL){
		auxiliar = iterator->currentNode->item;
		iterator->currentNode = iterator->currentNode->next;
	}
	return auxiliar;
}

void UndavColectionSettings::IteratorUndav::Destroy(Iterator* iterator){
	delete iterator;
}
