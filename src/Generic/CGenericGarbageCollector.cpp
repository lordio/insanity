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

	CGenericGarbageCollector::CGenericGarbageCollector() : _pool{}
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