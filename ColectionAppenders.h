#ifndef SET_H_
#define SET_H_
#include <string> // para NULL

namespace UndavColectionAppenders{
	typedef bool (*Compare) (void*, void*);
	struct ColectionAppenders;
	ColectionAppenders* Crear(UndavColectionAppenders::Compare comparator = NULL);
	void Agregar(ColectionAppenders* colectionAppender, void* item);
	//pre:-
	//post: Elimina el item solo si lo encuentra, si no, no hace nada
	void EliminarItem(ColectionAppenders* colectionAppender, void* item);
	//post: Si @item esta en @colectionAppender devuelve true si no, devuelve false
	bool Contains(ColectionAppenders* colectionAppender, void* item, Compare procesar);
	bool EstaVacia(const ColectionAppenders* colectionAppender);
	void Destruir(ColectionAppenders* colectionAppender);
	namespace IteratorUndav{
		struct Iterator;
		Iterator* Create(ColectionAppenders* colectionAppender);
		bool IsEnd(Iterator* colectionAppender);
		void* Next(Iterator* colectionAppender);
		void Destroy(Iterator* iterador);
	}

}


#endif /* SET_H_ */
