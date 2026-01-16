#include "SnowUI/Core/Dialog.h"
#include "SnowUI/Widgets/Label.h"
#include "SnowUI/Widgets/Button.h"
#include "SnowUI/Layout/Layout.h"
#include "SnowUI/Render/SkiaBackend.h"
#include <iostream>
#include <memory>

using namespace SnowUI;

class SoilParameterDialog : public Dialog
{
  public:
	void OnInitDialog() override
	{
		std::cout << "Initializing Soil Parameter Dialog..." << std::endl;

		// Create labels and input fields for soil parameters
		auto labelDensity = std::make_shared<Label>();
		labelDensity->SetText("Soil Density (kg/m³):");
		labelDensity->SetBounds(Rect(20, 20, 200, 25));
		AddChild(labelDensity);

		auto labelMoisture = std::make_shared<Label>();
		labelMoisture->SetText("Moisture Content (%):");
		labelMoisture->SetBounds(Rect(20, 55, 200, 25));
		AddChild(labelMoisture);

		auto labelCohesion = std::make_shared<Label>();
		labelCohesion->SetText("Cohesion (kPa):");
		labelCohesion->SetBounds(Rect(20, 90, 200, 25));
		AddChild(labelCohesion);

		auto labelFriction = std::make_shared<Label>();
		labelFriction->SetText("Friction Angle (°):");
		labelFriction->SetBounds(Rect(20, 125, 200, 25));
		AddChild(labelFriction);

		// Create buttons
		auto btnOK = std::make_shared<Button>();
		btnOK->SetText("OK");
		btnOK->SetBounds(Rect(220, 160, 80, 30));
		AddChild(btnOK);

		auto btnCancel = std::make_shared<Button>();
		btnCancel->SetText("Cancel");
		btnCancel->SetBounds(Rect(310, 160, 80, 30));
		AddChild(btnCancel);
	}
};

int main()
{
	std::cout << "SnowUI Soil Parameter Dialog Demo" << std::endl;

	// Create Skia backend (uses OpenGL fallback when Skia is not available)
	SkiaBackend backend;

	// Create dialog
	auto dialog = std::make_shared<SoilParameterDialog>();
	if (!dialog->Create("Soil Parameters", 420, 220, &backend))
	{
		std::cerr << "Failed to create dialog" << std::endl;
		return 1;
	}

	dialog->OnInitDialog();

	// Run the main dialog loop (blocks until window is closed)
	std::cout << "Running soil parameter dialog (close window to exit)..." << std::endl;
	dialog->Run();

	std::cout << "Demo completed successfully!" << std::endl;

	return 0;
}
