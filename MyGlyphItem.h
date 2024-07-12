
#include <QQuickVTKItem.h>
#include <vtkObject.h>

#pragma once

class MyGlyphItem : public QQuickVTKItem
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
};

