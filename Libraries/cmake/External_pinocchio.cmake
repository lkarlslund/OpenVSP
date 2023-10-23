ExternalProject_Add( PINOCCHIO
	URL ${CMAKE_CURRENT_SOURCE_DIR}/Pinocchio-4c2c9ab185b3.zip
	DOWNLOAD_EXTRACT_TIMESTAMP TRUE
	CMAKE_ARGS -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
		-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
		-DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
		-DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
		-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
		-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
		-DBUILD_SHARED_LIBS=OFF
		-DPINOCCHIO_CONSOLE_APP=OFF
		-DPINOCCHIO_GUI_APP=OFF
		-DPINOCCHIO_INSTALL=TRUE
		-DPINOCCHIO_SHARED_LIBS=OFF
)
ExternalProject_Get_Property( PINOCCHIO INSTALL_DIR )
SET( PINOCCHIO_INSTALL_DIR ${INSTALL_DIR} )
