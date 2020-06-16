# CMakeList.txt : CMake project for IBKR-Adapter, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
project ("IBKR-Adapter")
set(EXECUTABLE 0)
set(LIBRARY 1)
set(THIS_BUILD LIBRARY)

#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

if (WIN32)
    #do something
endif (WIN32)

if (UNIX)
    #do something
endif (UNIX)

if (MSVC)
    #do something
endif (MSVC)

include_directories(inc)

set(SOURCE_FILES
    src/main.cpp                                     /
    src/IBKRClient.cpp                               /

    src/ib_api_v9.76/ContractCondition.cpp           /
    src/ib_api_v9.76/DefaultEWrapper.cpp             /
    src/ib_api_v9.76/EClient.cpp                     /
    src/ib_api_v9.76/EClientSocket.cpp               /
    src/ib_api_v9.76/EDecoder.cpp                    /
    src/ib_api_v9.76/EMessage.cpp                    /
    src/ib_api_v9.76/EMutex.cpp                      /
    src/ib_api_v9.76/EOrderDecoder.cpp               /
    src/ib_api_v9.76/EReader.cpp                     /
    src/ib_api_v9.76/EReaderOSSignal.cpp             /
    src/ib_api_v9.76/ESocket.cpp                     /
    src/ib_api_v9.76/MarginCondition.cpp             /
    src/ib_api_v9.76/OperatorCondition.cpp           /
    src/ib_api_v9.76/OrderCondition.cpp              /
    src/ib_api_v9.76/PercentChangeCondition.cpp      /
    src/ib_api_v9.76/PriceCondition.cpp              /
    src/ib_api_v9.76/SoftDollarTier.cpp              /
    src/ib_api_v9.76/StdAfx.cpp                      /
    src/ib_api_v9.76/TimeCondition.cpp               /
    src/ib_api_v9.76/VolumeCondition.cpp             /
    src/ib_api_v9.76/executioncondition.cpp
)

set(HEADER_FILES 
    src/IBKRClient.h                                 /

    src/ib_api_v9.76/CommissionReport.h              /
    src/ib_api_v9.76/CommonDefs.h                    /
    src/ib_api_v9.76/Contract.h                      /
    src/ib_api_v9.76/ContractCondition.h             /
    src/ib_api_v9.76/DefaultEWrapper.h               /
    src/ib_api_v9.76/DepthMktDataDescription.h       /
    src/ib_api_v9.76/EClient.h                       /
    src/ib_api_v9.76/EClientMsgSink.h                /
    src/ib_api_v9.76/EClientSocket.h                 /
    src/ib_api_v9.76/EDecoder.h                      /
    src/ib_api_v9.76/EMessage.h                      /
    src/ib_api_v9.76/EMutex.h                        /
    src/ib_api_v9.76/EOrderDecoder.h                 /
    src/ib_api_v9.76/EPosixClientSocketPlatform.h    /
    src/ib_api_v9.76/EReader.h                       /
    src/ib_api_v9.76/EReaderOSSignal.h               /
    src/ib_api_v9.76/EReaderSignal.h                 /
    src/ib_api_v9.76/ESocket.h                       /
    src/ib_api_v9.76/ETransport.h                    /
    src/ib_api_v9.76/EWrapper.h                      /
    src/ib_api_v9.76/EWrapper_prototypes.h           /
    src/ib_api_v9.76/Execution.h                     /
    src/ib_api_v9.76/FamilyCode.h                    /
    src/ib_api_v9.76/HistogramEntry.h                /
    src/ib_api_v9.76/HistoricalTick.h                /
    src/ib_api_v9.76/HistoricalTickBidAsk.h          /
    src/ib_api_v9.76/HistoricalTickLast.h            /
    src/ib_api_v9.76/IExternalizable.h               /
    src/ib_api_v9.76/MarginCondition.h               /
    src/ib_api_v9.76/NewsProvider.h                  /
    src/ib_api_v9.76/OperatorCondition.h             /
    src/ib_api_v9.76/Order.h                         /
    src/ib_api_v9.76/OrderCondition.h                /
    src/ib_api_v9.76/OrderState.h                    /
    src/ib_api_v9.76/PercentChangeCondition.h        /
    src/ib_api_v9.76/PriceCondition.h                /
    src/ib_api_v9.76/PriceIncrement.h                /
    src/ib_api_v9.76/ScannerSubscription.h           /
    src/ib_api_v9.76/SoftDollarTier.h                /
    src/ib_api_v9.76/StdAfx.h                        /
    src/ib_api_v9.76/TagValue.h                      /
    src/ib_api_v9.76/TickAttrib.h                    /
    src/ib_api_v9.76/TickAttribBidAsk.h              /
    src/ib_api_v9.76/TickAttribLast.h                /
    src/ib_api_v9.76/TimeCondition.h                 /
    src/ib_api_v9.76/TwsSocketClientErrors.h         /
    src/ib_api_v9.76/VolumeCondition.h               /
    src/ib_api_v9.76/bar.h                           /
    src/ib_api_v9.76/executioncondition.h            /
    src/ib_api_v9.76/platformspecific.h
)

# Add source to this project's binaries.
if (${THIS_BUILD} EQUAL ${EXECUTABLE})
    add_compile_definitions(BUILD_TYPE_EXECUTABLE)
    add_executable (${PROJECT_NAME} ${SOURCE_FILES})
endif (${THIS_BUILD} EQUAL ${EXECUTABLE})

if (${THIS_BUILD} EQUAL ${LIBRARY})
    add_compile_definitions(BUILD_TYPE_LIBRARY)
    add_library (${PROJECT_NAME} MODULE ${SOURCE_FILES})
endif (${THIS_BUILD} EQUAL ${LIBRARY})

# TODO: Add tests and install targets if needed.
