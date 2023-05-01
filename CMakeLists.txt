cmake_minimum_required(VERSION 3.22)

if(UNIX)
    project(qsort CXX)
    set(CMAKE_CXX_STANDARD 20)
    add_executable(qsort main.cpp)
    install(
        PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/qsort
        DESTINATION /usr/local/bin
    )
    install(
        FILES ${CMAKE_SOURCE_DIR}/conf/extensions.json conf/qsort.conf
        DESTINATION /etc/qsort
    )
    install(
        FILES ${CMAKE_SOURCE_DIR}/conf/qsort-completion.bash
        DESTINATION /etc/bash_completion.d
    )
    add_custom_target(deb
        DEPENDS qsort
        COMMAND mkdir -p qsort-debian/usr/local/bin
	    COMMAND cp -fr DEBIAN qsort-debian/
	    COMMAND cp -f ${CMAKE_CURRENT_BINARY_DIR}/qsort qsort-debian/usr/local/bin/
	    COMMAND mkdir -p qsort-debian/etc/qsort qsort-debian/etc/bash_completion.d
	    COMMAND cp -f conf/* qsort-debian/etc/qsort/
	    COMMAND mv qsort-debian/etc/qsort/qsort-completion.bash qsort-debian/etc/bash_completion.d
	    COMMAND dpkg-deb --build qsort-debian
	    COMMAND rm -drf qsort-debian
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()
