cmake_minimum_required (VERSION 3.18)

# Enable Hot Reload for MSVC
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("ProjectSM" LANGUAGES CXX)

add_executable(ProjectSM "src/ProjectSM.cpp")

set_target_properties(ProjectSM PROPERTIES OUTPUT_NAME "crossword")

target_compile_features(ProjectSM PUBLIC cxx_std_17)