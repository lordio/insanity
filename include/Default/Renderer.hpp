#ifndef INSANITY_DEFAULT_RENDERER
#define INSANITY_DEFAULT_RENDERER

#include "../Constants.hpp"

#include "../IRenderer.hpp"
#include "Object.hpp"

namespace Insanity
{
	class IWindow;
	class IConfigObject;
	
	namespace Default
	{
		class INSANITY_API Renderer : public IRenderer, public Object
		{
		protected:
			IRenderer * _base;
		public:
			Renderer(IWindow * win, IConfigObject const * cfg);
			virtual ~Renderer();
			
			//=============================================
			//Interface: IRenderer
			//=============================================
			virtual void Render() override;
			virtual void Present() override;

			virtual void ClearColorBuffer(float color[4]) override;
			virtual void Resize(u16 width, u16 height) override;

			TRectangle<s16, u16> const * GetRenderRect() const override;
		};
	}
}

#endif
