ECHO OFF
:: Batch file: icg.bat
:: Author: Parminder Singh
:: Date: April 26, 2024
:: Revision: 1.0                                                              

REM Set the source directory to "projects".
SET "projects-dir=projects"

REM Set the test directory to "test-submissions".
SET "test-submission-dir=test-submissions"

REM Set the resource directory meshes.
SET "meshes-resource-dir=meshes"

REM Set the resource directory meshes.
SET "scene-resource-dir=scenes"

REM Set the resource directories for the script to include scenes, meshes, images, and logs.
SET "resource-dirs=%scene-resource-dir% %meshes-resource-dir% images"

REM Set the library directory.
SET "lib-dir=lib"

REM Set start code directory for icg.
SET "icg-starter-kit=%lib-dir%\icg"

REM Setting Git directory path
SET "GitDir=%~dp0.git"

REM Setting build directory path
SET "BuildDir=%~dp0build"

REM Setting Git modules path
SET "GitModules=%~dp0.gitmodules"

REM Setting CMake file path
SET "CMakeFile=%~dp0CMakeLists.txt"

CLS
:MENU
	ECHO.
	ECHO .....................................................
	ECHO Select your task, or Esc to EXIT.
	ECHO .....................................................
	ECHO   S   - Setup OpenGL 4.5
	ECHO   D   - Delete OpenGL 4.5 Setup
	ECHO   B   - Build All
	ECHO   C   - Clean and Build All
	ECHO   R   - Refresh Solution
	ECHO   E   - EXIT
	ECHO   0   - Create Tutorial 0 
	ECHO.
	SET /P M=Type option then press ENTER:

	IF /I %M%==S GOTO CMAKE_BUILD
	IF /I %M%==D GOTO CLEAN
	IF /I %M%==B GOTO BUILD_ALL
	IF /I %M%==C GOTO CLEAN_BUILD_ALL
	IF /I %M%==R GOTO BUILDCMAKELISTS
	IF /I %M%==E GOTO :EOF
	IF %M%==0 GOTO CREATE_PROJECT_TUTORIAL_0
	IF %M%==100 (
		GOTO PLAYLOGS
	) ELSE (
	    ECHO Invalid choice. Please enter valid option from menu.
	    PAUSE
	    GOTO MENU
	)

:CREATE_PROJECT_TUTORIAL_0
	CALL :CHECK_OPENGL_LIBS "%lib-dir%"
	CALL :COPY_FROM_REMOTE_URL https://giraphics.github.io/csd-2101/tutorial-0.zip projects
	GOTO BUILDCMAKELISTS

:COPY_FROM_REMOTE_URL
	setlocal
		SET "remote_url=%~1"
		SET "destination_folder=%~2"
		FOR /f "delims=/ tokens=*" %%a in ("%remote_url%") do (
			SET "filename_ext=%%~nxa"
		    SET "filename=%%~na"
		)

		curl -L -o "%filename_ext%" "%remote_url%"
		IF %errorlevel% neq 0 (ECHO Failed to download the file.)

		tar -xf "%filename_ext%" -C .
		IF %errorlevel% neq 0 (ECHO Failed to unzip the file.)
		
		IF EXIST "%filename_ext%" ECHO y|del "%filename_ext%"
		xcopy "%filename%" "%destination_folder%/%filename%" /s /i /-y

		IF EXIST "%filename%" ECHO y|rmdir /s "%filename%"
	endlocal
	goto :eof

:: Check OpenGL dependencies
:CHECK_OPENGL_LIBS
	SET "folder=%~1"
	IF not EXIST "%folder%" (
	    ECHO [WARNING!] OpenGL 4.5 is not configured.
	    ECHO Choose the menu option: Press S to set up OpenGL 4.5.
	    REM You can add further instructions or actions here.
	    PAUSE
	    GOTO MENU
	)
	goto :eof

:CMAKE_BUILD
	SET "GitFolder=%~dp0.git"
	SET "GitModules=%~dp0.gitmodules"

	IF EXIST "%GitFolder%" ECHO y|rmdir /s "%GitFolder%"
    CALL git init
    CALL git config core.autocrlf false
	CALL git submodule add https://github.com/glfw/glfw ./lib/glfw
	CALL git submodule add https://github.com/omniavinco/glew-cmake ./lib/glew
	CALL git submodule add https://github.com/glfw/gleq ./lib/gleq
	CALL git submodule add https://github.com/giraphics/glfw-event-recorder ./lib/glfw-event-recorder	
	CALL git submodule add https://github.com/lvandeve/lodepng ./lib/lodepng
	CALL git submodule add https://github.com/g-truc/glm ./lib/glm	
	CALL git submodule add https://github.com/tinyobjloader/tinyobjloader ./lib/tinyobjloader	

	IF EXIST "%GitFolder%" ECHO y|rmdir /s "%GitFolder%"
	IF EXIST "%GitModules%" ECHO y|del "%GitModules%"

	SET "folders=build %test-submission-dir% %projects-dir%"

	REM Loop through each folder name and create it
	FOR %%i in (%folders%) do (
	    mkdir "%%i"
	)
	GOTO BUILDCMAKELISTS
	GOTO MENU

:BUILD_ALL
	cmake --build build --config Release
	GOTO MENU

:CLEAN_BUILD_ALL
	cmake --build build --clean-first --config Release
	GOTO MENU

:CLEAN
	IF EXIST "%GitDir%" ECHO y|rmdir /s "%GitDir%"
	IF EXIST "%BuildDir%" ECHO y|rmdir /s "%BuildDir%"
	IF EXIST "%lib-dir%" ECHO y|rmdir /s "%lib-dir%"
	IF EXIST "%GitModules%" ECHO y|del "%GitModules%"
	IF EXIST "%CMakeFile%" ECHO y|del "%CMakeFile%"  
	GOTO MENU

:PLAYLOGS
	:: Below Playback log are har
	SET curDir=%~dp0
	PUSHD %curDir%build
	Release\tutorial-0.exe -p -f ..\logs\tutorial-0-playback.log
	POPD
	GOTO MENU

:BUILDCMAKELISTS
	IF EXIST "%CMakeFile%" ECHO y|del "%CMakeFile%"  

	(
		ECHO # Projects Settings
		ECHO.
		ECHO cmake_minimum_required(VERSION 2.8...3.13^)
		ECHO.
		ECHO project (opengl-dev^)
		ECHO.
		ECHO add_definitions(-DGLEW_STATIC^)
		ECHO add_subdirectory(lib/glfw EXCLUDE_FROM_ALL^) 
		ECHO add_subdirectory(lib/glew EXCLUDE_FROM_ALL^) 
		ECHO.

		ECHO set(EXTERNAL_LIBRARY_SOURCES
	    ECHO     ${CMAKE_CURRENT_LIST_DIR}/lib/lodepng/lodepng.h
	    ECHO     ${CMAKE_CURRENT_LIST_DIR}/lib/lodepng/lodepng.cpp
	    ECHO     ${CMAKE_CURRENT_LIST_DIR}/lib/glfw-event-recorder/recorder.h
	    ECHO     ${CMAKE_CURRENT_LIST_DIR}/lib/glfw-event-recorder/recorder.cpp
		ECHO ^)
		ECHO.

		ECHO # All libraries - GLFW, glew
		ECHO set(ALL_LIBS
		ECHO   PRIVATE glfw
		ECHO   PRIVATE libglew_static
		ECHO ^)

		ECHO ADD_LIBRARY(icg STATIC
	    ECHO     ${EXTERNAL_LIBRARY_SOURCES}
	    ECHO ^)
		ECHO target_link_libraries(icg
		ECHO     ${ALL_LIBS}
		ECHO ^) 

		ECHO include_directories(${CMAKE_CURRENT_LIST_DIR}/lib/imgui^)
		ECHO include_directories(${CMAKE_CURRENT_LIST_DIR}/lib/imgui/backends^)
		ECHO include_directories(${CMAKE_CURRENT_LIST_DIR}/lib/gleq^)
		ECHO include_directories(${CMAKE_CURRENT_LIST_DIR}/lib/lodepng^)
		ECHO include_directories(${CMAKE_CURRENT_LIST_DIR}/lib/glfw-event-recorder^)
		ECHO include_directories(${CMAKE_CURRENT_LIST_DIR}/lib/glm^)
		ECHO include_directories(${CMAKE_CURRENT_LIST_DIR}/lib/tinyobjloader^)	
		ECHO.
		
		REM Please gather the target folder first before the project is build otherwise it will capture build folder as well
		REM ECHO set(DisableWarnings "/wd5045" "/wd4365" "/wd4242" "/wd4365" "/wd4820" "/wd4514" "/wd5039" "/wd4668" "/wd5219" "/wd4061" "/wd4091" "/wd4464" "/wd4100" "/wd4458" "/wd4267" "/wd4244" "/wd4305" "/wd4189" "/wd4710" "/wd4711" "/wd4201" "/wd4626" ^)
		ECHO.

		IF EXIST "%projects-dir%" (
			FOR /d %%i in ("%projects-dir%\*") do (
			    REM ECHO %%~nxi

			ECHO file(GLOB_RECURSE %%~nxi_source_files 
			ECHO     ${CMAKE_CURRENT_LIST_DIR}/%projects-dir%/%%~nxi/src/*.[ch]pp
			ECHO     ${CMAKE_CURRENT_LIST_DIR}/%projects-dir%/%%~nxi/include/*.h
			ECHO ^)
			ECHO.
		    ECHO add_executable(%%~nxi 
		    ECHO     ${%%~nxi_source_files} 
		    ECHO ^)
			ECHO.
			ECHO target_link_libraries(%%~nxi
			ECHO     ${ALL_LIBS}
			ECHO     icg
			ECHO ^) 
			ECHO.
			ECHO set_property(TARGET %%~nxi PROPERTY CXX_STANDARD 20^) 
			ECHO IF (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang"^)
			ECHO     target_compile_options(%%~nxi PRIVATE -Wall ${DisableWarnings}^)
			ECHO elseif (MSVC^)
			ECHO     target_compile_options(%%~nxi PRIVATE /W3 /WX-^)
			ECHO endif(^)
			ECHO target_include_directories(%%~nxi PRIVATE ${CMAKE_CURRENT_LIST_DIR}/%projects-dir%/%%~nxi/include^)
			ECHO.
			)
		)

		IF EXIST "%test-submission-dir%" (
			FOR /d %%i in ("%test-submission-dir%\*") do (
			    REM ECHO %%~nxi
		    
			ECHO ############## %%~nxi ###############
			ECHO file(GLOB_RECURSE %%~nxi_source_files 
			ECHO     ${CMAKE_CURRENT_LIST_DIR}/%test-submission-dir%/%%~nxi/*.[ch]pp
			ECHO     ${CMAKE_CURRENT_LIST_DIR}/%test-submission-dir%/%%~nxi/*.h
			ECHO ^)
			ECHO.
		    ECHO add_executable(%%~nxi 
		    ECHO     ${%%~nxi_source_files} 
		    ECHO ^)
			ECHO.
			ECHO target_link_libraries(%%~nxi
			ECHO     ${ALL_LIBS}
			ECHO     icg
			ECHO ^) 
			ECHO.
			ECHO set_property(TARGET %%~nxi PROPERTY CXX_STANDARD 20^) 
			ECHO IF (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang"^)
			ECHO     target_compile_options(%%~nxi PRIVATE -Wall ${DisableWarnings}^)
			ECHO elseif (MSVC^)
			ECHO     target_compile_options(%%~nxi PRIVATE /W3 /WX-^)
			ECHO endif(^)
			ECHO target_include_directories(%%~nxi PRIVATE ${CMAKE_CURRENT_LIST_DIR}/%test-submission-dir%/%%~nxi/include^)
			ECHO.
			)
		)
	) >> "CMakeLists.txt"

	:: Create CMake project
	SET curDir=%~dp0
	PUSHD %curDir%build
	cmake -G "Visual Studio 17 2022" ..
	POPD
	GOTO MENU

:EXIT
	exit /b 2
