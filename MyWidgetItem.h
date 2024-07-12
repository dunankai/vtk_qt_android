
#include <QQuickVTKItem.h>
#include <vtkObject.h>
#include <vtkImplicitPlaneWidget2.h>

class vtkPlane;
class vtkActor;
class vtkGlyph3D;
class vtkRenderer;
class vtkImplicitPlaneRepresentation;

class MyWidgetItem
    : public QQuickVTKItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    struct Data : vtkObject
    {
        static Data* New();
        vtkTypeMacro(Data, vtkObject);

        vtkNew<vtkImplicitPlaneWidget2> planeWidget;
    };

    struct Callback
    {
        void Execute(vtkObject*, unsigned long evt, void*);
        Callback();
        vtkPlane* Plane;
        vtkActor* Actor;
        vtkGlyph3D* Glyph;
        vtkRenderer* Renderer;
        vtkImplicitPlaneRepresentation* Rep;
        MyWidgetItem* pThis;
        unsigned long EndEventTag;
    };

    vtkUserData initializeVTK(vtkRenderWindow* renderWindow) override;

    Callback myCallback;
};
