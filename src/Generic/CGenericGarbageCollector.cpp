#define INSANITY_BUILDING_LIBRARY

#include "CGenericGarbageCollector.hpp"
#include <IObject.hpp>
#include <algorithm>

#include <functional>

namespace Insanity
{
	IGarbageCollector * IGarbageCollector::Create()
	{
		return new CGenericGarbageCollector();
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
		_pool.push_back(obj);
	}
	void CGenericGarbageCollector::Untrack(IObject * obj)
	{
		auto iter = std::find(_pool.begin(),_pool.end(),obj);
		if(iter == _pool.end()) return;

		_pool.erase(iter);
	}
	void CGenericGarbageCollector::Collect()
	{
        for(auto iter = _pool.begin(); iter < _pool.end();)
        {
            if((*iter)->GetReferenceCount() == 0)
            {
                (*iter)->Delete();
                iter = _pool.erase(iter);
                
                //object deletion shouldn't Delete tracked objects, and Untrack/Track calls in object deletions seems at least a little unlikely.
            }
            else iter++;
        }
		/*IObject * last = nullptr;

		for(auto iter = _pool.begin(); iter < _pool.end();)
		{
			if((*iter)->GetReferenceCount() != 0)
			{
				last = *iter;
				iter++;
			}
			else
			{
				(*iter)->Delete();
				_pool.erase(iter);

				//iterator invalidated. find last checked object (or vector start if last is nullptr)
				if(last == nullptr) iter = _pool.begin();
				else
				{
					iter = std::find(_pool.begin(),_pool.end(),last);
					iter++;
				}
				//is it possible for the destruction of an object created second to destroy an object earlier in the vector? I don't think so.
				//	since GarbageCollector handles destruction. Elsewhere things should just retain and release.
			}
		}*/
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