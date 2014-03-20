#ifndef INSANITY_ENUMERATION_DRAW_MODE
#define INSANITY_ENUMERATION_DRAW_MODE

namespace Insanity
{
	enum class EDrawMode
	{
		Points,
		LineStrip,
		LineLoop,
		Lines,
		LineStripAdjacency,
		LinesAdjacency,
		TriangleStrip,
		TriangleFan,
		Triangles,
		TriangleStripAdjacency,
		TrianglesAdjacency,
		Patches
	};
}

#endif
