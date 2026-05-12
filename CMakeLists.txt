cmake_minimum_required(VERSION 3.20)
project(TrtInference CXX)

set(CMAKE_CXX_STANDARD 17)

set(DEPS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")

set(ORT_ROOT    "C:/Users/FSOS/.nuget/packages/microsoft.ml.onnxruntime.gpu.windows/1.25.1")
set(ORT_INCLUDE "${ORT_ROOT}/buildTransitive/native/include")

add_library(trt_inference SHARED TrtInference.cpp TrtInference.h)

target_compile_definitions(TrtInference PRIVATE TRTDLL_EXPORTS)

target_compile_options(TrtInference PRIVATE
    $<$<CONFIG:Release>:/O2 /Oi /Ot /GL /GS- /arch:AVX2>
)

target_link_options(TrtInference PRIVATE
    $<$<CONFIG:Release>:/LTCG /OPT:REF /OPT:ICF>
)

target_include_directories(TrtInference PRIVATE
    ${ORT_INCLUDE}
    ${DEPS_DIR}
)

target_link_directories(TrtInference PRIVATE ${DEPS_DIR})

target_link_libraries(TrtInference PRIVATE
    onnxruntime.lib
    cudart.lib
)

set_target_properties(TrtInference PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG   "${CMAKE_BINARY_DIR}/bin"
)
