#ifndef INSANITY_DEFAULT_IMPLEMENTATIONS
#define INSANITY_DEFAULT_IMPLEMENTATIONS

//Classes that client code may desire to inherit can define a default implementation.
//This is not intended for internal use.

//all default-implementation classes should be pulled in here.
//Note, this should not be included in Insanity.hpp
//If you want this, include it manually.
#include "Default/Mod.hpp"
#include "Default/Object.hpp"
#include "Default/Renderer.hpp"
#include "Default/Task.hpp"
#include "Default/Thread.hpp"
#include "Default/Window.hpp"

#endif