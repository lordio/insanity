#ifndef INSANITY
#define INSANITY

#if defined(INSANITY_BUILDING_LIBRARY)
#	error Attempted to include Insanity.hpp from a library implementation file.
#endif

#include "Constants.hpp"

//does this need to be here?
#include "IGarbageCollector.hpp"

//non-instantiables
//	(do not have a Create static method)
#include "IClonable.hpp"
#include "IObject.hpp"
#include "ITask.hpp"
#include "IThread.hpp"

//instantiables
//	(have a Create static method)
#include "IByteArray.hpp"
#include "IMutex.hpp"
#include "IRenderer.hpp"
#include "IServerSocket.hpp"
#include "IShaderProgram.hpp"
#include "IStreamSocket.hpp"
#include "ISubThread.hpp"
#include "IWindow.hpp"

//configuration objects
//	(instantiable, but not through Create methods)
#include "IConfigFile.hpp"
#include "IConfigObject.hpp"

//Singleton Application
#include "IApplication.hpp"

//Module
//	(instantiable, but each is unique)
#include "IMod.hpp"

//Helper classes
#include "EKeyMap.hpp"
#include "Ptr.hpp"
#include "TMatrix.hpp"
#include "TRectangle.hpp"
#include "TVector.hpp"

//Default classes
//	(provide most common necessary implementation, but are generally overridable)
#include "Default.hpp"

#if defined(PLATFORM_MSWINDOWS)
//link against insanity library
#	pragma comment(lib, "Insanity.lib")

//link against Common Controls v6 managed DLL
#	pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' \
version='6.0.0.0' \
processorArchitecture='*' \
publicKeyToken='6595b64144ccf1df' \
language='*'\"")

#	if defined(INSANITY_MSWINDOWS_SUPPRESS_CONSOLE)
//tell the program loader not to spawn a console window for this process.
#		pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#	endif
#endif

#endif
