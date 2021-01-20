
if(WIN32)
    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../third_party/winpcap/Lib/wpcap.lib")
        set(BUILD_SV_GOOSE_EXAMPLES ON)
        message("Found winpcap -> compile examples for GOOSE and SV")
    endif()
else()
    set(BUILD_SV_GOOSE_EXAMPLES ON)
endif()

if(${BUILD_SV_GOOSE_EXAMPLES})
    add_subdirectory(goose_subscriber)
    add_subdirectory(goose_publisher)
endif()
