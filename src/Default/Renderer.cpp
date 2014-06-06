#define INSANITY_BUILDING_LIBRARY

#include <default/Renderer.hpp>

namespace Insanity
{
	namespace Default
	{
		Renderer::Renderer(IWindow * win, IConfigObject const * cfg) : _base{ IRenderer::Create(this, win, cfg) }, Object{}
		{
			_base->Retain();
		}
		Renderer::~Renderer()
		{
			_base->Release();
		}
		
		//=================================================
		//Interface: IRenderer
		//=================================================
		void Renderer::Render()
		{
			_base->Render();
		}
		void Renderer::Present()
		{
			_base->Present();
		}

		void Renderer::ClearColorBuffer(float color[4])
		{
			_base->ClearColorBuffer(color);
		}
		void Renderer::Resize(u16 width, u16 height)
		{
			_base->Resize(width, height);
		}
		
		IShaderProgram * Renderer::CreateShaderProgram()
		{
			return _base->CreateShaderProgram();
		}
		bool Renderer::UseShaderProgram(IShaderProgram * program)
		{
			return _base->UseShaderProgram(program);
		}
		TRectangle<s16, u16> const * Renderer::GetRenderRect() const
		{
			return _base->GetRenderRect();
		}
	}
}
