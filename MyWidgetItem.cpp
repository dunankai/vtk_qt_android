#include "MyWidgetItem.h"
#include <vtkCommand.h>
#include <vtkAbstractMapper.h>
#include <vtkActor.h>
#include <vtkGlyph3D.h>
#include <vtkImplicitPlaneRepresentation.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkConeSource.h>
#include <vtkAppendPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkClipPolyData.h>
#include <vtkNew.h>
#include <vtkImplicitFunction.h>
#include <vtkProperty.h>
#include <vtkPlane.h>

void MyWidgetItem::Callback::Execute(vtkObject *, unsigned long evt, void *)
{
    if (evt == vtkCommand::InteractionEvent)
    {
        this->Rep->GetPlane(this->Plane);
        this->Actor->VisibilityOn();
    }

    if (evt == vtkCommand::EndEvent)
    {
        // Once the application is up, adjust the camera, widget reps, etc.
        this->Renderer->ResetCamera();
        this->Rep->SetPlaceFactor(1.25);
        this->Rep->PlaceWidget(this->Glyph->GetOutput()->GetBounds());
        this->Renderer->GetActiveCamera()->Azimuth(20);
        this->Renderer->GetRenderWindow()->RemoveObserver(this->EndEventTag);
        this->pThis->scheduleRender();
    }
}

MyWidgetItem::Callback::Callback()
    : Plane(nullptr)
    , Actor(nullptr)
{
}

vtkStandardNewMacro(MyWidgetItem::Data);

QQuickVTKItem::vtkUserData MyWidgetItem::initializeVTK(vtkRenderWindow *renderWindow)
{
    auto vtk = vtkNew<Data>();

    vtkNew<vtkRenderer> renderer;
    renderWindow->AddRenderer(renderer);

    // Create a mace out of filters.
    //
    vtkNew<vtkSphereSource> sphere;
    vtkNew<vtkGlyph3D> glyph;
    vtkNew<vtkConeSource> cone;
    glyph->SetInputConnection(sphere->GetOutputPort());
    glyph->SetSourceConnection(cone->GetOutputPort());
    glyph->SetVectorModeToUseNormal();
    glyph->SetScaleModeToScaleByVector();
    glyph->SetScaleFactor(0.25);

    // The sphere and spikes are appended into a single polydata.
    // This just makes things simpler to manage.
    vtkNew<vtkAppendPolyData> apd;
    apd->AddInputConnection(glyph->GetOutputPort());
    apd->AddInputConnection(sphere->GetOutputPort());

    vtkNew<vtkPolyDataMapper> maceMapper;
    maceMapper->SetInputConnection(apd->GetOutputPort());

    vtkNew<vtkActor> maceActor;
    maceActor->SetMapper(maceMapper);
    maceActor->VisibilityOn();

    // This portion of the code clips the mace with the vtkPlanes
    // implicit function. The clipped region is colored green.
    vtkNew<vtkPlane> plane;
    vtkNew<vtkClipPolyData> clipper;
    clipper->SetInputConnection(apd->GetOutputPort());
    clipper->SetClipFunction(plane);
    clipper->InsideOutOn();

    vtkNew<vtkPolyDataMapper> selectMapper;
    selectMapper->SetInputConnection(clipper->GetOutputPort());

    vtkNew<vtkActor> selectActor;
    selectActor->SetMapper(selectMapper);
    selectActor->GetProperty()->SetColor(0, 1, 0);
    selectActor->VisibilityOff();
    selectActor->SetScale(1.01, 1.01, 1.01);

    vtkNew<vtkImplicitPlaneRepresentation> rep;

    // The SetInteractor method is how 3D widgets are associated with the render
    // window interactor. Internally, SetInteractor sets up a bunch of callbacks
    // using the Command/Observer mechanism (AddObserver()).
    myCallback.Plane = plane;
    myCallback.Actor = selectActor;
    myCallback.Glyph = glyph;
    myCallback.Rep = rep;
    myCallback.Renderer = renderer;
    myCallback.pThis = this;

    vtk->planeWidget->SetRepresentation(rep);
    vtk->planeWidget->AddObserver(vtkCommand::InteractionEvent, &myCallback, &Callback::Execute);
    myCallback.EndEventTag = renderer->GetRenderWindow()->AddObserver(
        vtkCommand::EndEvent, &myCallback, &Callback::Execute);
    auto iren = renderWindow->GetInteractor();
    vtk->planeWidget->SetInteractor(iren);
    vtk->planeWidget->SetCurrentRenderer(renderer);
    vtk->planeWidget->SetEnabled(1);
    vtk->planeWidget->SetProcessEvents(1);

    renderer->AddActor(maceActor);
    renderer->AddActor(selectActor);

    return vtk;
}
