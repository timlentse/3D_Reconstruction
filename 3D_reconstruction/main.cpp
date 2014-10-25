
	/**
	@ a little software of 3D reconstruction
	@author: timlentse
	@email: tinglenxan@gmail.com
	*/

	#include <vtkRenderer.h>
	#include <vtkRenderWindow.h>
	#include <vtkRenderWindowInteractor.h>
	#include <vtkDICOMImageReader.h>
	#include <vtkPolyDataMapper.h>
	#include <vtkActor.h>
	#include <vtkOutlineFilter.h>
	#include <vtkCamera.h>
	#include <vtkProperty.h>
	#include <vtkPolyDataNormals.h>
	#include <vtkContourFilter.h>
	#include <vtkInteractorStyleTrackballCamera.h>

	 int main(int argc, char *argv[])
	{
       if (argc!=2) {
	   std::cout << "usage: ./your_executable_fle   /path/to/slices"<<std::endl; }
	// Create the renderer, the render window, and the interactor. The renderer
	  // draws into the render window, the interactor enables mouse- and
	  // keyboard-based interaction with the data within the render window.
	  vtkRenderer *Render = vtkRenderer::New();
	  vtkRenderWindow *renWin = vtkRenderWindow::New();
		renWin->AddRenderer(Render);
	  vtkInteractorStyleTrackballCamera *style=vtkInteractorStyleTrackballCamera::New();
	  vtkRenderWindowInteractor *ireninter = vtkRenderWindowInteractor::New();
		ireninter->SetInteractorStyle(style);
		ireninter->SetRenderWindow(renWin);


	  // The following reader is used to read a series of 2D slices (images) that compose the volume.
		vtkDICOMImageReader *imageseries = vtkDICOMImageReader::New();
		imageseries->SetDirectoryName(argv[1]);
		imageseries->SetDataSpacing (3.2, 3.2, 1.5);

	  // An isosurface, or contour value of 500 is known to correspond to the
	  // skin of the patient. Once generated, a vtkPolyDataNormals filter is
	  // is used to create normals for smooth surface shading during rendering.
	  vtkContourFilter *skinExtractor = vtkContourFilter::New();
		skinExtractor->SetInputConnection(imageseries->GetOutputPort());
		skinExtractor->SetValue(0, 300);
	  vtkPolyDataNormals *skinNormals = vtkPolyDataNormals::New();
		skinNormals->SetInputConnection(skinExtractor->GetOutputPort());
		skinNormals->SetFeatureAngle(60.0);
	  vtkPolyDataMapper *skinMapper = vtkPolyDataMapper::New();
		skinMapper->SetInputConnection(skinNormals->GetOutputPort());
		skinMapper->ScalarVisibilityOff();
	  vtkActor *skin = vtkActor::New();
		skin->SetMapper(skinMapper);

	  // An outline provides context around the data.
	  vtkOutlineFilter *outlineData = vtkOutlineFilter::New();
		outlineData->SetInputConnection(imageseries->GetOutputPort());
	  vtkPolyDataMapper *mapOutline = vtkPolyDataMapper::New();
		mapOutline->SetInputConnection(outlineData->GetOutputPort());
	  vtkActor *outline = vtkActor::New();
		outline->SetMapper(mapOutline);
		outline->GetProperty()->SetColor(1,0,0);

	  // It is convenient to create an initial view of the data. The FocalPoint
	  // and Position form a vector direction. Later on (ResetCamera() method)
	  // this vector is used to position the camera to look at the data in
	  // this direction.
		vtkCamera *aCamera = vtkCamera::New();
		aCamera->SetViewUp (0, 0, -1);
		aCamera->SetPosition (0, 1, 0);
		aCamera->SetFocalPoint (0, 0, 0);
		aCamera->ComputeViewPlaneNormal();

	  // Actors are added to the renderer. An initial camera view is created.
	  // The Dolly() method moves the camera towards the FocalPoint,
	  // thereby enlarging the image.
	  Render->AddActor(outline);
	  Render->AddActor(skin);
	  Render->SetActiveCamera(aCamera);
	  Render->ResetCamera ();
	  aCamera->Dolly(2);

	  // Set a background color for the renderer and set the size of the
	  // render window (expressed in pixels).
	  Render->SetBackground(0.0,0.0,0.0);
	  renWin->SetSize(640, 480);

	  // Note that when camera movement occurs (as it does in the Dolly()
	  // method), the clipping planes often need adjusting. Clipping planes
	  // consist of two planes: near and far along the view direction. The
	  // near plane clips out objects in front of the plane; the far plane
	  // clips out objects behind the plane. This way only what is drawn
	  // between the planes is actually rendered.
	  Render->ResetCameraClippingRange ();
	  // Initialize the event loop and then start it.
	  ireninter->Initialize();
	  ireninter->Start();
	  
	  // It is important to delete all objects created previously to prevent
	  // memory leaks. In this case, since the program is on its way to
	  // exiting, it is not so important. But in applications it is
	  // essential.
	  imageseries->Delete();
	  skinExtractor->Delete();
	  skinNormals->Delete();
	  skinMapper->Delete();
	  skin->Delete();
	  outlineData->Delete();
	  mapOutline->Delete();
	  outline->Delete();
	  aCamera->Delete();
	  ireninter->Delete();
	  renWin->Delete();
	  Render->Delete();
	  return 0;
	}

