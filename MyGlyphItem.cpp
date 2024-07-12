#include "MyGlyphItem.h"
#include <vtkBuffer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSphereSource.h>
#include <vtkGlyph3DMapper.h>
#include <vtkConeSource.h>
#include <vtkProperty.h>

vtkStandardNewMacro(MyGlyphItem::Data);

QQuickVTKItem::vtkUserData MyGlyphItem::initializeVTK(vtkRenderWindow *renderWindow)
{
    auto vtk = vtkNew<Data>();

    vtkNew<vtkRenderer> renderer;
    renderWindow->AddRenderer(renderer);

    // Create the glyph pipeline
    vtkNew<vtkSphereSource> sphere;
    vtkNew<vtkGlyph3DMapper> glyphMapper;
    vtkNew<vtkConeSource> squad;
    glyphMapper->SetInputConnection(sphere->GetOutputPort());
    glyphMapper->SetSourceConnection(squad->GetOutputPort());
    glyphMapper->SetOrientationArray("Normals");
    vtkNew<vtkActor> glyphActor;
    glyphActor->SetMapper(glyphMapper);
    glyphActor->GetProperty()->SetDiffuseColor(0.5, 1.0, 0.8);
    renderer->AddActor(glyphActor);
    renderer->ResetCamera();

    return vtk;
}
