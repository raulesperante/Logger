#ifndef BAG_H_
#define BAG_H_

namespace UndavColectionSettings{
	struct ColectionSettings;
	ColectionSettings* Create();
	void Add(ColectionSettings* colectionSettings, void* item);
	bool IsEmpty(const ColectionSettings* colectionSettings);
	void Destroy(ColectionSettings* colectionSettings);
	namespace IteratorUndav{
		struct Iterator;
		Iterator* Create(ColectionSettings* colectionSettings);
		bool IsEnd(Iterator* colectionSettings);
		void* Next(Iterator* colectionSettings);
		void Destroy(Iterator* iterador);
	}
}


#endif
