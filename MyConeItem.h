
#include <QQuickVTKItem.h>
#include <vtkActor.h>

#pragma once

class MyConeItem
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

    void onEndEvent(vtkObject* caller, unsigned long, void*);

    vtkUserData initializeVTK(vtkRenderWindow* renderWindow) override;
signals:

private:
    unsigned long endEventTag;
};
