#include "MyVtkItem.h"
#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>

QQuickVTKItem::vtkUserData MyVtkItem::initializeVTK(vtkRenderWindow *renderWindow)
{
    auto vtk = vtkNew<Data>();

    // Create a cone pipeline and add it to the view
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkActor> actor;
    vtkNew<vtkPolyDataMapper> mapper;
    vtkNew<vtkConeSource> cone;
    renderWindow->AddRenderer(renderer);
    mapper->SetInputConnection(cone->GetOutputPort());
    actor->SetMapper(mapper);
    renderer->AddActor(actor);
    renderer->ResetCamera();
    renderer->SetBackground2(0.7, 0.7, 0.7);
    renderer->SetGradientBackground(true);

    return vtk;
}

vtkStandardNewMacro(MyVtkItem::Data);
