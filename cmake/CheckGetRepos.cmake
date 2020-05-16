include(FetchContent)

function(check_get_repos REPOS_NAME REPOS_ADDR REPOS_TAG)
  FetchContent_Declare(
    ${REPOS_NAME}
    GIT_REPOSITORY ${REPOS_ADDR}
    GIT_TAG ${REPOS_TAG})
  FetchContent_GetProperties(${REPOS_NAME})
  if(NOT ${REPOS_NAME}_POPULATED)
    FetchContent_Populate(${REPOS_NAME})
    add_subdirectory(${${REPOS_NAME}_SOURCE_DIR} ${${REPOS_NAME}_BINARY_DIR}
                     EXCLUDE_FROM_ALL)
  endif()
endfunction()
