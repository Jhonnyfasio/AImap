#pragma once
using namespace System;
using namespace System::Collections::Generic;
//using System::Linq;
using namespace System::Text;

using namespace System::Drawing;

__interface IDrawable
{
public:
	// Return the object's needed size.
	SizeF GetSize(Graphics gr, Font font);

	// Return true if the node is above this point.
	bool IsAtPoint(Graphics ^gr, Font ^font, PointF center_pt, PointF target_pt); 

	// Draw the object centered at (x, y).
	virtual void Draw(float x, float y, Graphics ^gr, Pen ^pen,
		Brush ^bg_brush, Brush ^text_brush, Font ^font);
};