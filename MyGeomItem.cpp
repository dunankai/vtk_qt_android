#include "MyGeomItem.h"
#include <vtkBuffer.h>
#include <vtkRenderer.h>
#include <vtkPolyDataMapper.h>
#include <vtkConeSource.h>
#include <vtkRenderWindow.h>

vtkStandardNewMacro(MyGeomItem::Data);

QQuickVTKItem::vtkUserData MyGeomItem::initializeVTK(vtkRenderWindow *renderWindow)
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

    return vtk;
}
