include(FetchContent)

function(check_get_repos REPOS_NAME REPOS_ADDR REPOS_TAG)
  FetchContent_Declare(
    ${REPOS_NAME}
    GIT_REPOSITORY ${REPOS_ADDR}
    GIT_TAG ${REPOS_TAG}
  )
  string(TOLOWER "${REPOS_NAME}" lcName)
  FetchContent_GetProperties(${REPOS_NAME})
  if(NOT ${lcName}_POPULATED)
    message("Loading " ${REPOS_NAME})
    FetchContent_Populate(${REPOS_NAME})
    add_subdirectory(${${lcName}_SOURCE_DIR} ${${lcName}_BINARY_DIR}
                     EXCLUDE_FROM_ALL)
  endif()
endfunction()
