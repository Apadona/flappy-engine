#include <Engine.h>

class Sandbox : public Engine::Application
{
	public:
		SandBox( std::string name ) : Application(name) {}
		
		void OnInit( int argc, char** argv, char** env ) override
		{
			return true;
		}

		void OnCreate() override
		{
			
		}

		void OnUpdate( float dt )
		{
		}

		void OnClose()
		{
		}

	private:
};

void RegisterApplication()
{
	// new SandBox();
	// app = new SandBox();
}