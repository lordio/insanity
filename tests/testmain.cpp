#include <Insanity.hpp>
using namespace Insanity;

#include <iostream>

#include <TString.hpp>
#include <Default/Thread.hpp>

#define PREFIX "../../../tests/"
#define MODPREFIX "../../../bin/Win32/"

class ConformanceTest
{
	bool _failed;
	char const * _testName;
	char const * _reason;
protected:
	bool Success()
	{
		return true;
	}
	bool Fail(char const * reason)
	{
		_failed = true;
		_reason = reason;
		
		return false;
	}
	
	virtual bool DoTests() = 0;
	
	void RunTests()
	{
		std::cout << _testName << ": ";
		
		if(DoTests()) std::cout << "Successful." << std::endl;
		else std::cout << "Failed. (Reason: " << _reason << ")" << std::endl;
	}
	
	bool HasFailed() const
	{
		return _failed;
	}
	char const * Reason() const
	{
		return _reason;
	}
	char const * TestName() const
	{
		return _testName;
	}
	
	void Warn(char const * reason)
	{
		std::cout << "Warning: " << reason << " -- " << std::flush;
	}
public:
	ConformanceTest(char const * testName) : _failed(false), _testName(testName), _reason(nullptr)
	{
	}
	virtual ~ConformanceTest()
	{
	}
};

class WindowedEnvironmentConformanceTest : public ConformanceTest
{
/*
Abstract:
	Tests objects commonly used in client-side graphical applications.
	
Todo:
	Add Renderer, ShaderProgram, Task tests.
	May be better able to test Task in the Communications Conformance Test.
	ConfigObject used but not thoroughly tested. Can do a more rigorous test in the Module Interaction Conformance Test.

Tests the following objects:
	Application
	Window
	ConfigFile
*/
private:
	class WECTWindow final : public Default::Window
	{
	private:
		u64 _handlers;
		WindowedEnvironmentConformanceTest * _test;
	public:
		WECTWindow(IConfigObject const * cfg, WindowedEnvironmentConformanceTest * test) : 
			Default::Window(cfg), 
			_handlers(0), 
			_test(test)
		{
		}
		~WECTWindow()
		{
		}
		
		void MouseHandler(EMouseButton button, EMouseButtonState state, u16 x, u16 y) override
		{
			u8 shift = 0;
			
			if(button == EMouseButton::Null && state != EMouseButtonState::Null)
			{
				state = EMouseButtonState::Null;
				_test->Warning("button Null, but State non-Null. Corrected.");
			}
			else if(state == EMouseButtonState::Null && button != EMouseButton::Null)
			{
				button = EMouseButton::Null;
				_test->Warning("state Null, but button non-Null. Corrected.");
			}
			
			//calculate shift; each (button, state) combination should take one bit in _handlers.
			switch(button)
			{
			case EMouseButton::X2:
				shift += 3;
			case EMouseButton::X1:
				shift += 3;
			case EMouseButton::Middle:
				shift += 3;
			case EMouseButton::Right:
				shift += 3;
			case EMouseButton::Left:
				shift += 1; //use LSB for mousemove
				break;
			default:
				shift = 0;
			}
			switch(state)
			{
			case EMouseButtonState::DoubleClick:
				shift++;
			case EMouseButtonState::Up:
				shift++;
			case EMouseButtonState::Down:
				break;
			default:
				shift = 0;
			}
			
			_handlers |= (1LL << shift);
		}
		void KeyHandler(EKey key, EKeyState state) override
		{
			//only checking state here, so two bits are needed.
			if(state == EKeyState::Down) _handlers |= (1 << 16);
			else if(state == EKeyState::Up) _handlers |= (1 << 17);
		}
		void ScrollHandler(EMouseScrollDirection dir, u16 delta) override
		{
			//only checking dir, so two bits needed.
			if(dir == EMouseScrollDirection::Up) _handlers |= (1 << 18);
			else if(dir == EMouseScrollDirection::Down) _handlers |= (1 << 19);
		}
		void MoveHandler(s16 x, s16 y) override
		{
			//set move bit
			_handlers |= (1 << 20);
		}
		void ResizeHandler(u16 width, u16 height) override
		{
			//set resize bit
			_handlers |= (1 << 21);
		}
		void ShowHandler(bool show) override
		{
			//two bits; show and hide.
			if(show) _handlers |= (1 << 22);
			else _handlers |= (1 << 23);
		}
		void CloseHandler() override
		{
			//set bit and end test.
			_handlers |= (1 << 24);
			
			IApplication::GetInstance()->End();
		}
		
		u64 GetHandlerState() const
		{
			return _handlers;
		}
	};
protected:
	bool DoTests() override
	{
		//only test GetInstance and Update here. Do Thread methods at SubThread.
		Ptr<IApplication> app = IApplication::GetInstance();
		if(!app) return Fail("IApplication::GetInstance() returned nullptr.");
		
		{
			Ptr<IApplication> app2 = IApplication::GetInstance();
			if(app != app2) return Fail("IApplication::GetInstance() returned different values.");
		}
		
		Ptr<IConfigFile> cfg = IConfigFile::GetInstance(PREFIX"ctest.cfg");
		if(!cfg) return Fail("IConfigFile::GetInstance() returned nullptr.");
		if(!cfg->IsValid()) return Fail("Config file is invalid.");
		
		Ptr<WECTWindow> win = new WECTWindow(cfg->GetObject("wectWin"), this);
		//at this point, all ConfigFile methods have been tested.
		
		if(!win) return Fail("WECTWindow creation failed.");
		if(!win->GetExtended()) return Fail("WECTWindow::GetExtended() returned nullptr.");
		
		{
			//Rectangle testing not done here; need to test setters, but GetRect returns a const*.
			Ptr<const TRectangle<s16,u16>> winrect = win->GetRect();
			if(!winrect) return Fail("win->GetRect() returned nullptr.");
		}
		
		win->Move(30,30);
		win->Resize(640,480);
		win->Show(false);
		win->Show(true);
		
		//synthesize the many combinations of Mouse
		win->Mouse(EMouseButton::Left, EMouseButtonState::Down, 0, 0);
		win->Mouse(EMouseButton::Left, EMouseButtonState::Up, 0, 0);
		win->Mouse(EMouseButton::Left, EMouseButtonState::DoubleClick, 0, 0);
		win->Mouse(EMouseButton::Right, EMouseButtonState::Down, 0, 0);
		win->Mouse(EMouseButton::Right, EMouseButtonState::Up, 0, 0);
		win->Mouse(EMouseButton::Right, EMouseButtonState::DoubleClick, 0, 0);
		win->Mouse(EMouseButton::Middle, EMouseButtonState::Down, 0, 0);
		win->Mouse(EMouseButton::Middle, EMouseButtonState::Up, 0, 0);
		win->Mouse(EMouseButton::Middle, EMouseButtonState::DoubleClick, 0, 0);
		win->Mouse(EMouseButton::X1, EMouseButtonState::Down, 0, 0);
		win->Mouse(EMouseButton::X1, EMouseButtonState::Up, 0, 0);
		win->Mouse(EMouseButton::X1, EMouseButtonState::DoubleClick, 0, 0);
		win->Mouse(EMouseButton::X2, EMouseButtonState::Down, 0, 0);
		win->Mouse(EMouseButton::X2, EMouseButtonState::Up, 0, 0);
		win->Mouse(EMouseButton::X2, EMouseButtonState::DoubleClick, 0, 0);
		win->Mouse(EMouseButton::Null, EMouseButtonState::Null, 30, 30);
		
		win->Key(EKeyMap::A, EKeyState::Down);
		win->Key(EKeyMap::A, EKeyState::Up);
		
		win->Scroll(EMouseScrollDirection::Down, 1);
		win->Scroll(EMouseScrollDirection::Up, 1);
		
		win->Close();
		
		//if no equivalent to SendMessage (Win32) / NSApplication -sendEvent: (Cocoa) on X11,
		//	event synthesizers will always go to event queue
		//	using PostMessage (Win32) / NSApplication -postEvent:atStart: (Cocoa) / XSendEvent (X11)
		//	In that case, GetHandlerState should report 0 before the application loop.
		if(win->GetHandlerState() != 0) return Fail("Handlers called before mainloop. (Event queue short-circuit?)");
		
		//should process all events in order, and immediately break.
		while(app->Update())
		{
			//app->Update should return false, and not enter this block.
			return Fail("app->Update() did not return false.");
		}
		
		if(win->GetHandlerState() != 0x1ffffff) return Fail("Not all handlers called on WECTWindow.");
		
		return Success();
	}
public:
	WindowedEnvironmentConformanceTest() : ConformanceTest("Windowed Environment Conformance Test")
	{	
		//Cannot call this from ConformanceTest, relies on inheritor's implementation of DoTests.
		RunTests();
	}
	~WindowedEnvironmentConformanceTest()
	{
	}
	
	void Warning(char const * reason)
	{
		Warn(reason);
	}
} wect;

class CommunicationsConformanceTest final : public ConformanceTest
{
/*
Abstract:
	Tests objects commonly used in server-side communications applications.
	
Todo:
	Write test.
	
Tests the following objects:
	SubThread (done)
	ServerSocket (done)
	StreamSocket (done)
	ByteArray (done)
	Mutex(?)
	Task(?)
*/
	class ConnectingThread : public Default::Thread
	{
	public:
		ConnectingThread()
		{
			Start();
		}
		void Main()
		{
			Ptr<IStreamSocket> sck{ IStreamSocket::Create("localhost", 50000) };

			Ptr<IByteArray> ba{ IByteArray::Create() };
			ba->Write(u64{ 0xdeadbeeffacec0de });
			sck->Send(ba);

			sck->Close();

			End();
		}
	};
protected:
	bool DoTests() override
	{
		Ptr<IServerSocket> srv{ IServerSocket::Create(50000) };
		Ptr<ConnectingThread> cn{ new ConnectingThread() };

		Ptr<IStreamSocket> strm{};
		while (!(strm = srv->Accept()));

		Ptr<IByteArray> ba{ IByteArray::Create() };
		strm->Receive(ba);
		if (ba->Size() != sizeof(u64)) return Fail("Received wrong amount of data.");

		u64 rcvd{};
		ba->Read(rcvd);
		if (rcvd != 0xdeadbeeffacec0de) return Fail("Received wrong value.");

		return Success();
	}
public:
	CommunicationsConformanceTest() : ConformanceTest("Communications Conformance Test")
	{
		RunTests();
	}
	~CommunicationsConformanceTest()
	{
	}
} cct;

#include "ConformanceTestMod.hpp"

class ModuleInteractionConformanceTest final : public ConformanceTest
{
/*
Abstract:
	Tests Module loading and interaction through a public base class.
	Also handles tests for objects not done in previous tests.
	
Todo:
	Write test.
	
Tests the following objects:
	Mod (really should rename it to Module)
	ConfigObject
*/
protected:
	bool DoTests() override
	{
		Ptr<IMod> imod{ IMod::GetInstance(MODPREFIX"ConformanceTestModule") };
		if (!imod) return Fail("Module not loaded.");

		Ptr<ConformanceTestMod> mod{ imod->As<ConformanceTestMod>() };
		if (!mod) Fail("Module has wrong type.");

		String str = mod->GetValue();
		if (str != "Deathmole") return Fail("Received wrong value.");

		return Success();
	}
public:
	ModuleInteractionConformanceTest() : ConformanceTest("Module Interaction Conformance Test")
	{
		RunTests();
	}
	~ModuleInteractionConformanceTest()
	{
	}
} mict;

int main()
{
	Ptr<IApplication> app = IApplication::GetInstance();

	return 0;
}
