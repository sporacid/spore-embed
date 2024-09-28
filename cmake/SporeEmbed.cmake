function(spore_embed SPORE_EMBED_FILE SPORE_EMBED_RESULT)
  cmake_parse_arguments(
    "SPORE_EMBED"
    "DEBUG;"
    "BITS;WIDTH;FORMAT;INDENT;"
    ""
    ${ARGN}
  )

  find_program(
    SPORE_EMBED_EXECUTABLE
    NAMES "spore-embed"
  )

  if (NOT SPORE_EMBED_EXECUTABLE)
    message(FATAL_ERROR "spore-embed executable not found")
  endif ()

  if (SPORE_EMBED_BITS)
    list(
      APPEND SPORE_EMBED_COMMAND_ARGS
      --bits
      ${SPORE_EMBED_BITS}
    )
  endif ()

  if (SPORE_EMBED_WIDTH)
    list(
      APPEND SPORE_EMBED_COMMAND_ARGS
      --width
      ${SPORE_EMBED_WIDTH}
    )
  endif ()

  if (SPORE_EMBED_FORMAT)
    list(
      APPEND SPORE_EMBED_COMMAND_ARGS
      --format
      ${SPORE_EMBED_FORMAT}
    )
  endif ()

  if (SPORE_EMBED_INDENT)
    list(
      APPEND SPORE_EMBED_COMMAND_ARGS
      --indent
      ${SPORE_EMBED_INDENT}
    )
  endif ()

  if (SPORE_EMBED_DEBUG)
    list(
      APPEND SPORE_EMBED_COMMAND_ARGS
      --debug
    )
  endif ()

  list(
    APPEND SPORE_EMBED_COMMAND_ARGS
    ${SPORE_EMBED_FILE}
  )

  list(
    JOIN SPORE_EMBED_COMMAND_ARGS
    " "
    SPORE_EMBED_COMMAND
  )

  execute_process(
    COMMAND ${SPORE_EMBED_EXECUTABLE} ${SPORE_EMBED_COMMAND}
    OUTPUT_VARIABLE SPORE_EMBED_OUTPUT
    COMMAND_ERROR_IS_FATAL ANY
  )

  set(${SPORE_EMBED_RESULT} ${SPORE_EMBED_OUTPUT} PARENT_SCOPE)
endfunction()
