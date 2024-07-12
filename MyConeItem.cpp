#include "MyConeItem.h"

#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>

vtkStandardNewMacro(MyConeItem::Data);

void MyConeItem::onEndEvent(vtkObject *caller, unsigned long, void *)
{
    vtkRenderWindow* renderWindow = vtkRenderWindow::SafeDownCast(caller);
    renderWindow->GetRenderers()->GetFirstRenderer()->ResetCamera();
    renderWindow->RemoveObserver(this->endEventTag);
    this->scheduleRender();
}

QQuickVTKItem::vtkUserData MyConeItem::initializeVTK(vtkRenderWindow *renderWindow)
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

    endEventTag = renderWindow->AddObserver(vtkCommand::EndEvent, this, &MyConeItem::onEndEvent);

    return vtk;
}
