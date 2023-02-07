#pragma once
#include <stdlib.h>
#include <MyLinkedList.hpp>

namespace Alloc {
	class Allocator;

	class refTemp {
	public:
		virtual void UpdatePointer(void*) = 0;
		virtual void* getLocation() = 0;
		virtual size_t getSize() = 0;
		virtual std::pair<void*, size_t> getLocationAndSize() = 0;
		virtual void Free(Allocator&) = 0;
		virtual void Nullify() = 0;
	protected:
	};
	

	class Allocator {
	public:

		Allocator(size_t Size) {
			Allocated = (char*)malloc(Size);
		}

		~Allocator() {
			free(Allocated);
		}

		void Free(refTemp* Address) {
			FreeQueue.push_back(Address->getLocationAndSize());
		}


		void Cleanup() {
			size_t freed = 0;
			size_t freeCounter = 0;

			auto it = FreeQueue.begin();

			for (refTemp* CurReference : References) {
				auto temp = CurReference->getLocation();
				if (it != FreeQueue.end()) {
					if ((temp >= it->first) && (temp < ((char*)it->first + it->second))) CurReference->Nullify();
					else if (CurReference->getLocation() > it->first) {
						freeCounter += it->second;
						it++;

					}
				}

				CurReference->UpdatePointer((void*)((char*)CurReference->getLocation() - freeCounter));
			}

			FreeQueue.clear();
		}

		template<typename U>
		friend class ref;
		friend class refTemp;
	protected:
		char* Allocated = 0;
		size_t mutable LastElement = 0;
		extstd::List<refTemp*> References;
		extstd::List<std::pair<void*, size_t>> FreeQueue;
#ifdef _HAS_CXX17
		[[nodiscard]]
#endif
		std::pair<void*, size_t> Alloc(size_t size) const {
			LastElement += size;
			return std::make_pair((void*)(Allocated + LastElement - size), size);
		}
	};

	template<typename T>
	class ref : public refTemp{
	public:
		ref(){
			loc = 0;
		}

		ref(Allocator& allocator, size_t sizeToAlloc = 1) : loc((T*)allocator.Alloc(sizeToAlloc * sizeof(T)).first), AllocatedSize(sizeToAlloc * sizeof(T)) {
			allocator.References.push_back(this);
		}
		
		ref(ref& reference) {
			loc = reference.loc;
			AllocatedSize = reference.AllocatedSize;
		}
		ref(const std::pair<void*, size_t>& addr) {
			AllocatedSize = addr.second;
			loc = (T*)addr.first;
		}

		void UpdatePointer(void* NewPointer) override{
			std::copy(loc, loc + AllocatedSize, (char*)NewPointer);

			loc = (T*)NewPointer;
		}

		void* getLocation() override {
			return (void*)loc;
		}

		size_t getSize() override { 
			return AllocatedSize;
		}

		std::pair<void*, size_t> getLocationAndSize() {
			return std::make_pair((void*)loc, AllocatedSize);
		}

		void Free(Allocator& allocator) override {
			allocator.References.remove(this);
			allocator.FreeQueue.push_back(getLocationAndSize());
			AllocatedSize = 0;
			loc = 0;
		}

		void Nullify() {
			AllocatedSize = 0;
			loc = 0;
		}

		void operator=(const std::pair<void*, size_t>& addr)  {
			AllocatedSize = addr.second;
			loc = (T*)addr.first;
		}

		void operator=(ref& reference) {
			loc = reference.loc;
			AllocatedSize = reference.AllocatedSize;
		}
		T& operator*() {
			return *loc;
		}

		template<typename M>
		operator M* () {
			return (M*)loc;
		}

	protected:
		size_t AllocatedSize = 0;
		T* loc;
	};
}