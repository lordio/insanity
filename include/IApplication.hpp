#ifndef INSANITY_INTERFACE_APPLICATION
#define INSANITY_INTERFACE_APPLICATION

#include "Constants.hpp"
#include "IThread.hpp"

namespace Insanity
{
	//=====================================================
	//Represents the program as a whole
	//	and contains the main thread's library context.
	//	(Garbage collector and the like.)
	//=====================================================
	class INSANITY_API IApplication : public virtual IThread
	{
	protected:
		//=================================================
		//The global application instance.
		//=================================================
		static IApplication * s_app;
	public:
		//=================================================
		//Gets the active Application instance,
		//	or creates one if it does not already exist.
		//=================================================
		static IApplication * GetInstance();
		
		//=================================================
		//Delete nulls the global application.
		//=================================================

		//=================================================
		//End requests the thread loop end.
		//=================================================
	};
}

#endif
