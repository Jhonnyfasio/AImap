#include <list>

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Text;
using namespace System::Drawing;


namespace Howtoo {
	class AristaNode;

	class VerticeNode {
	public:
		VerticeNode *sigVertice;
		AristaNode *listaAdy;
		Cell elemento;
		int nivel = -1;
		friend class TreeNodes;

		
	};

	class AristaNode {
	public:
		AristaNode *sigArista;
		VerticeNode *verticePertenece;
		float peso;

		friend class TreeNodes;
	};

class TreeNodes {

};

}