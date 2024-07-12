
#include <QQuickVTKItem.h>
#include <vtkActor.h>

#pragma once

class MyVtkItem
    : public QQuickVTKItem
{
    Q_OBJECT
    QML_ELEMENT
public:
    struct Data : vtkObject
    {
        static Data* New();
        vtkTypeMacro(Data, vtkObject);
    };

    vtkUserData initializeVTK(vtkRenderWindow* renderWindow) override;

signals:
};
