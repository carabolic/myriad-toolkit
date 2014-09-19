set(LIBNAME "MyriadCommunication")

set(BASE_SRCS src/CommunicationSubsystem.cpp)

set(
    BASE_HEADERS
    include/myriad/communication/CommunicationSubsystem.h
    include/myriad/communication/Notifications.h
)

add_library(${LIBNAME} ${BASE_SRCS} ${BASE_HEADERS})