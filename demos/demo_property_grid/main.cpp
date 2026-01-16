#include "SnowUI/Core/Window.h"
#include "SnowUI/Widgets/PropertyGrid.h"
#include "SnowUI/Render/OpenGLBackend.h"
#include <iostream>
#include <memory>

using namespace SnowUI;

int main()
{
	std::cout << "SnowUI Property Grid Demo" << std::endl;

	// Create OpenGL backend
	OpenGLBackend backend;

	// Create window
	auto window = std::make_shared<Window>();
	if (!window->Create("Property Grid Demo", 800, 600, &backend))
	{
		std::cerr << "Failed to create window" << std::endl;
		return 1;
	}

	// Create property grid
	auto propertyGrid = std::make_shared<PropertyGrid>();
	propertyGrid->SetBounds(Rect(10, 10, 780, 580));

	// Add sample properties
	propertyGrid->AddProperty("Name", "Demo Project", "string");
	propertyGrid->AddProperty("Version", "1.0.0", "string");
	propertyGrid->AddProperty("Width", "800", "int");
	propertyGrid->AddProperty("Height", "600", "int");
	propertyGrid->AddProperty("Enabled", "true", "bool");
	propertyGrid->AddProperty("BackColor", "#202020", "color");

	window->AddChild(propertyGrid);

	// Run the main window loop (blocks until window is closed)
	std::cout << "Running property grid window (close window to exit)..." << std::endl;
	window->Run();

	std::cout << "Demo completed successfully!" << std::endl;

	return 0;
}
