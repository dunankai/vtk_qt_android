#include "MyVolumeItem.h"
#include <QTemporaryFile>
#include <vtkBuffer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkSmartVolumeMapper.h>
#include <vtkXMLImageDataReader.h>
#include <vtkTestUtilities.h>
#include <vtkDataSet.h>
#include <vtkPiecewiseFunction.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkOpenGLGPUVolumeRayCastMapper.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkOpenGLRenderer.h>

vtkStandardNewMacro(MyVolumeItem::Data);

QQuickVTKItem::vtkUserData MyVolumeItem::initializeVTK(vtkRenderWindow *renderWindow)
{
    QFile file(":/vase_1comp.vti");
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "xxx open qrc file failed";
        return nullptr;
    }

    auto vtk = vtkNew<Data>();

    vtkNew<vtkOpenGLRenderer> renderer;
    renderWindow->AddRenderer(renderer);

    // Create a volume pipeline and add it to the view
    vtkNew<vtkSmartVolumeMapper> volumeMapper;
    vtkNew<vtkXMLImageDataReader> reader;
    reader->SetInputString(file.readAll().toStdString());
    reader->ReadFromInputStringOn();

    volumeMapper->SetInputConnection(reader->GetOutputPort());
    double scalarRange[2];
    volumeMapper->GetInput()->GetScalarRange(scalarRange);
    volumeMapper->SetAutoAdjustSampleDistances(1);
    volumeMapper->SetBlendModeToComposite();
    vtkNew<vtkPiecewiseFunction> scalarOpacity;
    scalarOpacity->AddPoint(scalarRange[0], 0.0);
    scalarOpacity->AddPoint(scalarRange[1], 0.09);
    vtkNew<vtkVolumeProperty> volumeProperty;
    volumeProperty->ShadeOff();
    volumeProperty->SetInterpolationType(VTK_LINEAR_INTERPOLATION);
    volumeProperty->SetScalarOpacity(scalarOpacity);
    vtkSmartPointer<vtkColorTransferFunction> colorTransferFunction =
        volumeProperty->GetRGBTransferFunction(0);
    colorTransferFunction->RemoveAllPoints();
    colorTransferFunction->AddRGBPoint(scalarRange[0], 0.6, 0.4, 0.1);
    // colorTransferFunction->AddRGBPoint(scalarRange[1], 0.2, 0.1, 0.3);
    vtkSmartPointer<vtkVolume> volume = vtkSmartPointer<vtkVolume>::New();
    volume->SetMapper(volumeMapper);
    volume->SetProperty(volumeProperty);
    renderer->AddVolume(volume);
    renderer->ResetCamera();

    return vtk;
}
