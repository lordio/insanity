#define INSANITY_BUILDING_LIBRARY

#include "CGenericGarbageCollector.hpp"
#include <IObject.hpp>
#include <algorithm>

namespace Insanity
{
	IGarbageCollector * IGarbageCollector::Create()
	{
		return new CGenericGarbageCollector{};
	}

	CGenericGarbageCollector::CGenericGarbageCollector()
	{
	}
	CGenericGarbageCollector::~CGenericGarbageCollector()
	{
		Clean();
	}

	//=====================================================
	//Interface: IGarbageCollector
	//=====================================================
	void CGenericGarbageCollector::Track(IObject * obj)
	{
		//if we're not supposed to track it, don't.
		if (!obj->ShouldBeTracked()) return;

		//if it's already being tracked, don't.
		if (obj->IsBeingTracked()) return;

		_pool.push_back(obj);

		obj->SetIsTracked(true);
	}
	void CGenericGarbageCollector::Untrack(IObject * obj)
	{
		//if it's not supposed to be tracked, it shouldn't be in here.
		if (!obj->ShouldBeTracked()) return;

		//if it's not being tracked, it definitely won't be in here.
		if (!obj->IsBeingTracked()) return;

		auto iter = std::find(_pool.begin(),_pool.end(),obj);
		if(iter == _pool.end()) return;

		_pool.erase(iter);

		obj->SetIsTracked(false);
	}
	void CGenericGarbageCollector::Collect()
	{
        for(auto iter = _pool.begin(); iter != _pool.end();)
        {
            if((*iter)->GetReferenceCount() == 0)
            {
                (*iter)->Delete();
                iter = _pool.erase(iter);
                
                //object deletion shouldn't Delete tracked objects, and Untrack/Track calls in object deletions seems at least a little unlikely.
            }
            else iter++;
        }
	}
	void CGenericGarbageCollector::Clean()
	{
		while(_pool.size() != 0)
		{
			auto iter = _pool.begin();
			_pool.erase(iter);
		}
	}
}