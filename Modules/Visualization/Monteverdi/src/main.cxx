/*
 * Copyright (C) 2005-2016 Centre National d'Etudes Spatiales (CNES)
 *
 * This file is part of Orfeo Toolbox
 *
 *     https://www.orfeo-toolbox.org/
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


//
// Configuration include.
//// Included at first position before any other ones.
#include "ConfigureMonteverdi.h"


/*****************************************************************************/
/* INCLUDE SECTION                                                           */

//
// Qt includes (sorted by alphabetic order)
//// Must be included before system/custom includes.
#include <QPixmap>
#include <QSplashScreen>

#define USE_SPLASH_SCREEN ( ( !defined( OTB_DEBUG ) && 0 ) || 0 )

//
// System includes (sorted by alphabetic order)

//
// ITK includes (sorted by alphabetic order)
// #include "itksys/SystemTools.hxx"

//
// OTB includes (sorted by alphabetic order)

//
// Monteverdi includes (sorted by alphabetic order)
#include "mvdApplication.h"
#include "mvdMainWindow.h"

enum ERROR_CODE
{
  ERROR_CODE_I18N = -1,
  ERROR_CODE_CACHE_DIR = -2,
  ERROR_CODE_DATABASE = -3,
  ERROR_CODE_GL_VERSION = -4,
  ERROR_CODE_USAGE = -5,
};


struct Flags
{
  Flags() :
    loadOTBApplications( false ),
    forceNoGLSL( false )
  {
  }

  bool loadOTBApplications: 1;
  bool forceNoGLSL: 1;
};


/*****************************************************************************/
/* FUNCTIONS DECLARATION                                                     */
/*****************************************************************************/


/*****************************************************************************/
/* MAIN                                                                      */
/*****************************************************************************/
int
main( int argc, char* argv[] )
{
  QApplication qtApp( argc, argv );
  Flags flags;

  //
  // 0. Splash-screen.
#if USE_SPLASH_SCREEN
  QPixmap pixmap(QLatin1String( ":/images/application_splash" ));
  QSplashScreen splash(pixmap);
  splash.show();
  qtApp.processEvents();//This is used to accept a click on the screen so that user can cancel the screen
#endif

  //
  // 0bis. Parse pre-initialization command-line arguments.
  QStringList args( qtApp.arguments() );
  {
  for( QStringList::iterator it( args.begin() );
       it!=args.end(); )
    if( it->compare( "-h" )==0 ||
	it->compare( "--help" )==0 )
      {
      std::cout
	<< mvd::ToLocalStdString(
	  QCoreApplication::translate(
	    PROJECT_NAME,
	    "Usage: %1 [-h|--help] [-a|--applications] [<filename>...]\n"
	    "  -1, --no-glsl      force OpenGL 1.x compatible rendering."
	    "  -a, --applications load OTB-applications from OTB_APPLICATIONS_PATH."
	    "  -h, --help         display this help message.\n"
	  )
	  .arg( QFileInfo( argv[ 0 ] ).baseName() )
	)
	<< std::endl;

      return ERROR_CODE_USAGE;
      }

    else if( it->compare( "-a" )==0 ||
	     it->compare( "--applications" )==0 )
      {
      flags.loadOTBApplications = true;

      it = args.erase( it );
      }

    else if(it->compare( "-1" )==0 ||
	    it->compare( "--no-glsl" )==0 )
      {
      flags.forceNoGLSL = true;

      it = args.erase( it );
      }
    else
      ++ it;
  }

  //
  // 1. Initialize application and sync settings.
  //
  // Coverity-14835
  // {
  mvd::Application * application = NULL;

  try
    {
    application = new mvd::Application( &qtApp );
    assert( application!=NULL );

    application->Initialize();
    }
  catch( std::exception & exc )
    {
    QMessageBox::StandardButton button =
      QMessageBox::question(
	NULL,
	QCoreApplication::translate(
	  PROJECT_NAME,
	  "Question!"
	),
	QCoreApplication::translate(
	  PROJECT_NAME,
	  "The following exception has been caught while initializing the software:\n\n"
	  "%1\n\n"
	  "The application may not function as expected. Do you want to continue?"
	)
	.arg( exc.what() ),
	QMessageBox::Yes | QMessageBox::No,
	QMessageBox::Yes
      );

    if( button==QMessageBox::No )
      return ERROR_CODE_I18N;
    }
  // }
  // Coverity-14835

  //
  // 2. Initialize main-window (UI).
  mvd::MainWindow mainWindow;
  mainWindow.Initialize();

  //
  // 3. Show window.
  mainWindow.show();

#if USE_SPLASH_SCREEN
  splash.finish( &mainWindow );
#endif // USE_SPLASH_SCREEN

  //
  // 4. Check OpenGL capabilities
  if( !mainWindow.CheckGLCapabilities( flags.forceNoGLSL ) )
    return ERROR_CODE_GL_VERSION;

  //
  // 5. Load OTB-applications.
  if( flags.loadOTBApplications )
#if USE_OTB_APPS
    mainWindow.SetupOTBApplications();
#else // USE_OTB_APPS
    qWarning() << "OTB-applications support is not included in this build.";
#endif // USE_OTB_APPS

  //
  // 6. Load command-line filenames.
  args.pop_front();

  mainWindow.ImportImages( args );

  //
  // 6. Let's go: run the application and return exit code.
  int result = QCoreApplication::instance()->exec();

  // Coverity-14835
  // {
  delete application;
  application = NULL;
  // }
  // Coverity-14835

  return result;
}


/*****************************************************************************/
/* FUNCTIONS IMPLEMENTATION                                                  */
/*****************************************************************************/
