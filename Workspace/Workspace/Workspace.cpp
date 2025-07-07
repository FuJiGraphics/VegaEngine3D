#include <VegaEngine.h>

using namespace std;

class Workspace : public vega::System
{
public:
	Workspace()
		: System(1024, 768, "VegaEngine2")
	{
	}
	virtual ~Workspace()
	{
		// Empty
	}

private:

};

vega::System* vega::CreateSystem()
{
	return new Workspace();
}
