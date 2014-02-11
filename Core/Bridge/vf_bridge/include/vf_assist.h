#pragma once
#pragma warning(disable:4275)

#include "vf_const.h"

namespace vapula
{
	//restrict copy
	class Uncopiable
	{
	protected:
		Uncopiable();
		~Uncopiable();
	private:
		Uncopiable(const Uncopiable&);
		Uncopiable& operator=(const Uncopiable&);
	};

	//clear target
	template<typename T>
	void Clear(T& target, bool isarr = false)
	{
		if(target == null)
			return;
		if(isarr)
			delete [] target;
		else 
			delete target;
		target = null;
	}

	//non-typed scoped pointer
	class VAPULA_API Handle : Uncopiable
	{
	protected:
		object _Ptr;
		bool _IsArr;

	public:
		explicit Handle(object ptr, bool isarr = false);
		~Handle();

	public:
		object Get();
		
		bool IsNull();

		void Ref(object ptr, bool isarr = false);

		void DeRef();

		template<typename T>
		T& Index(uint32 i) const
		{
			if(_Ptr == null)
				return null;
			return ((T*)_Ptr)[i];
		}
	};
}